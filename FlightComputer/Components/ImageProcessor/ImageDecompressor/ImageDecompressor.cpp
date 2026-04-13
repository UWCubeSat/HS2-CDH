// ======================================================================
// \title  ImageDecompressor.cpp
// \author mahiremran
// \brief  cpp file for ImageDecompressor component implementation class
// ======================================================================

#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressor.hpp"

#include <string>

std::uint8_t ImageProcessor::ImageDecompressor::s_bitstreamBuf[ImageProcessor::ImageDecompressor::kBitstreamBufBytes] = {};

#include "Fw/Time/Time.hpp"
#include "Os/FileSystem.hpp"

extern "C" {
#include "ccsds123_internal.h"  // NOLINT(build/include_subdir)
#include "ccsds123_io.h"        // NOLINT(build/include_subdir)
}

namespace ImageProcessor {

namespace {

std::string buildOutputFilePath(const char* input_path, const char* output_dir) {
    if (!input_path || !output_dir) {
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

    file += ".raw";
    return dir + file;
}

}  // namespace

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ImageDecompressor::ImageDecompressor(const char* const compName) : ImageDecompressorComponentBase(compName) {}

ImageDecompressor::~ImageDecompressor() {}

// ----------------------------------------------------------------------
// Handler implementations for ports
// ----------------------------------------------------------------------

void ImageDecompressor::timeGetPort_handler(FwIndexType portNum, Fw::Time& time) {
    // nothing to do
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ImageDecompressor::DECOMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,
                                                    U32 cmdSeq,
                                                    const Fw::CmdStringArg& input_file,
                                                    const Fw::CmdStringArg& output_dir,
                                                    U64 image_sample_len) {
    const char* input_path = input_file.toChar();
    const char* output_path = output_dir.toChar();

    if (!input_path || !output_path) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    if ((input_path[0] == '\0') || (output_path[0] == '\0')) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    if (image_sample_len > kBitstreamBufBytes) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const Os::FileSystem::Status mkdir_status = Os::FileSystem::createDirectory(output_path, true);
    if ((mkdir_status != Os::FileSystem::OP_OK) && (mkdir_status != Os::FileSystem::ALREADY_EXISTS)) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U64 input_size = 0;
    const Os::FileSystem::Status input_size_status = Os::FileSystem::getFileSize(input_path, input_size);
    if (input_size_status == Os::FileSystem::OP_OK) {
        this->tlmWrite_InputBitstreamSize(input_size);
    }

    this->log_ACTIVITY_HI_DecompressionStarted(input_file, output_dir);

    const Fw::Time start_time = this->getTime();
    const U64 start_ms =
        static_cast<U64>(start_time.getSeconds() * MSEC_PER_SEC + start_time.getUSeconds() / USEC_PER_MSEC);

    const int result = ccsds123_decompress_with_buffer(input_path,
                                                       output_path,
                                                       s_bitstreamBuf,
                                                       static_cast<size_t>(image_sample_len));

    const Fw::Time end_time = this->getTime();
    const U64 end_ms = static_cast<U64>(end_time.getSeconds() * MSEC_PER_SEC + end_time.getUSeconds() / USEC_PER_MSEC);

    if (end_ms >= start_ms) {
        this->tlmWrite_DecompressionTimeMs(static_cast<U32>(end_ms - start_ms));
    }

    if (result) {
        this->log_WARNING_HI_DecompressionFailed(input_file, result);
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
        if (input_size > 0) {
            const F64 ratio = static_cast<F64>(output_size) / static_cast<F64>(input_size);
            this->tlmWrite_ExpansionRatio(ratio);
            this->log_ACTIVITY_HI_DecompressionSucceeded(input_file, output_size, ratio);
        } else {
            this->log_ACTIVITY_HI_DecompressionSucceeded(input_file, output_size, 0.0);
        }
    } else {
        this->log_ACTIVITY_HI_DecompressionSucceeded(input_file, output_size, 0.0);
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace ImageProcessor