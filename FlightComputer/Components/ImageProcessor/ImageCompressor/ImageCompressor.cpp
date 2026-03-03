// ======================================================================
// \title  ImageCompressor.cpp
// \author mahiremran
// \brief  cpp file for ImageCompressor component implementation class
// ======================================================================

#include "FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressor.hpp"

#include <string>

std::int64_t ImageProcessor::ImageCompressor::s_imageSampleBuf[ImageProcessor::ImageCompressor::kImageSampleBufElems] = {};

#include "Fw/Time/Time.hpp"
#include "Os/FileSystem.hpp"

extern "C" {
#include "ccsds123_internal.h"  // NOLINT(build/include_subdir)
#include "ccsds123_io.h"        // NOLINT(build/include_subdir)
}

namespace ImageProcessor {

namespace {

std::string buildOutputFilePath(const char* input_path, const char* output_dir) {
    if ((input_path == nullptr) || (output_dir == nullptr)) {
        return std::string();
    }

    std::string dir(output_dir);
    if (!dir.empty() && dir.back() != '/') {
        dir.push_back('/');
    }

    std::string file(input_path);
    const std::size_t slash = file.find_last_of('/');
    if (slash != std::string::npos) {
        file = file.substr(slash + 1U);
    }

    const std::size_t dot = file.find_last_of('.');
    if (dot != std::string::npos) {
        file = file.substr(0U, dot);
    }

    file += ".bin";
    return dir + file;
}
}  // namespace

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ImageCompressor ::ImageCompressor(const char* const compName) : ImageCompressorComponentBase(compName) {}

ImageCompressor ::~ImageCompressor() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ImageCompressor ::COMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,
                                                 U32 cmdSeq,
                                                 const Fw::CmdStringArg& input_file,
                                                 const Fw::CmdStringArg& output_dir,
                                                 I32 ael,
                                                 I32 override_x,
                                                 I32 override_y,
                                                 I32 override_z,
                                                 const Fw::CmdStringArg& override_dtype,
                                                 U64 image_sample_len) {
    const char* input_path = input_file.toChar();
    const char* output_path = output_dir.toChar();
    const char* dtype = override_dtype.toChar();

    if ((input_path == nullptr) || (output_path == nullptr)) {
        this->log_WARNING_HI_CompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    if ((input_path[0] == '\0') || (output_path[0] == '\0')) {
        this->log_WARNING_HI_CompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    if (ael < 0) {
        this->log_WARNING_HI_CompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    if (image_sample_len > kImageSampleBufElems) {
        this->log_WARNING_HI_CompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const Os::FileSystem::Status mkdir_status = Os::FileSystem::createDirectory(output_path, true);
    if ((mkdir_status != Os::FileSystem::OP_OK) && (mkdir_status != Os::FileSystem::ALREADY_EXISTS)) {
        this->log_WARNING_HI_CompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U64 input_size = 0;
    const Os::FileSystem::Status input_size_status = Os::FileSystem::getFileSize(input_path, input_size);
    if (input_size_status == Os::FileSystem::OP_OK) {
        this->tlmWrite_InputImageSize(input_size);
    }

    this->log_ACTIVITY_HI_CompressionStarted(input_file, output_dir);

    const Fw::Time start_time = this->getTime();
    const U64 start_ms =
        static_cast<U64>(start_time.getSeconds() * 1000U + start_time.getUSeconds() / 1000U);

    const int result = ccsds123_compress_with_buffer(input_path,
                                                     output_path,
                                                     ael,
                                                     override_x,
                                                     override_y,
                                                     override_z,
                                                     dtype,
                                                     s_imageSampleBuf,
                                                     static_cast<size_t>(image_sample_len));

    const Fw::Time end_time = this->getTime();
    const U64 end_ms =
        static_cast<U64>(end_time.getSeconds() * 1000U + end_time.getUSeconds() / 1000U);

    if (end_ms >= start_ms) {
        this->tlmWrite_CompressionTimeMs(static_cast<U32>(end_ms - start_ms));
    }

    if (result != 0) {
        this->log_WARNING_HI_CompressionFailed(input_file, result);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U64 output_size = 0;
    const std::string output_file_path = buildOutputFilePath(input_path, output_path);
    const Os::FileSystem::Status output_size_status = output_file_path.empty()
                                                        ? Os::FileSystem::OTHER_ERROR
                                                        : Os::FileSystem::getFileSize(output_file_path.c_str(), output_size);
    if (output_size_status == Os::FileSystem::OP_OK) {
        this->tlmWrite_OutputImageSize(output_size);
        if (output_size > 0) {
            const F64 ratio = static_cast<F64>(input_size) / static_cast<F64>(output_size);
            this->tlmWrite_CompressionRatio(ratio);
            this->log_ACTIVITY_HI_CompressionSucceeded(input_file, output_size, ratio);
        } else {
            this->log_ACTIVITY_HI_CompressionSucceeded(input_file, output_size, 0.0);
        }
    } else {
        this->log_ACTIVITY_HI_CompressionSucceeded(input_file, output_size, 0.0);
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace ImageProcessor
