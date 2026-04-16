/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressor.cpp
 * @author mahiremran
 * @brief cpp file for ImageDecompressor component implementation class
 */

#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressor.hpp"

#include <cstdio>
#include <string>

std::uint8_t ImageProcessor::ImageDecompressor::s_bitstreamBuf[
    ImageProcessor::ImageDecompressor::kBitstreamBufBytes] = {};

#include "Fw/Time/Time.hpp"
#include "Os/FileSystem.hpp"

extern "C" {
#include "ccsds123_internal.h"  // NOLINT(build/include_subdir)
#include "ccsds123_io.h"        // NOLINT(build/include_subdir)
}

namespace ImageProcessor {

namespace {

bool loadBitstreamIntoBuffer(const char* bitstream_path,
                             std::uint8_t* bitstream_buf,
                             const std::size_t buffer_capacity,
                             std::size_t& bytes_loaded) {
    bytes_loaded = 0U;
    FILE* file = std::fopen(bitstream_path, "rb");
    if (!file) {
        return false;
    }

    const std::size_t bytes_read = std::fread(bitstream_buf, 1U, buffer_capacity, file);
    const bool file_truncated = (bytes_read == buffer_capacity) && (std::fgetc(file) != EOF);
    std::fclose(file);

    if (file_truncated || !bytes_read ) {
        return false;
    }

    bytes_loaded = bytes_read;
    return true;
}

std::string buildOutputFilePath(const Fw::CmdStringArg& input_file, const Fw::CmdStringArg& output_dir) {
    if (!input_file.toChar() || !output_dir.toChar() ) {
        return std::string();
    }

    std::string dir(output_dir.toChar());
    if (!dir.empty() && dir.back() != '/') {
        dir.push_back('/');
    }

    std::string file(input_file.toChar());
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

/**
 * @brief Component construction and destruction.
 */

/**
 * @brief Construct an ImageDecompressor component instance.
 */
ImageDecompressor::ImageDecompressor(const char* const compName)
    : ImageDecompressorComponentBase(compName) {}

/**
 * @brief Handler implementations for ports.
 */

/**
 * @brief Handle a request for the current time.
 */
void ImageDecompressor::timeGetPort_handler(FwIndexType portNum, Fw::Time& time) {
    // nothing to do
}

/**
 * @brief Handler implementations for commands.
 */

/**
 * @brief Decompress an image bitstream into raw image data.
 */
void ImageDecompressor::DECOMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,
                                                    U32 cmdSeq,
                                                    const Fw::CmdStringArg& input_file,
                                                    const Fw::CmdStringArg& output_dir,
                                                    U64 image_sample_len) {
    if ((input_file.toChar()[0] == '\0') || (output_dir.toChar()[0] == '\0')) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    if (image_sample_len > kBitstreamBufBytes) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const Os::FileSystem::Status mkdir_status = Os::FileSystem::createDirectory(output_dir.toChar(), true);
    if ((mkdir_status != Os::FileSystem::OP_OK) && (mkdir_status != Os::FileSystem::ALREADY_EXISTS)) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    U64 input_size = 0;
    const Os::FileSystem::Status input_size_status = Os::FileSystem::getFileSize(input_file.toChar(), input_size);
    if (input_size_status == Os::FileSystem::OP_OK) {
        this->tlmWrite_InputBitstreamSize(input_size);
    }

    this->log_ACTIVITY_HI_DecompressionStarted(input_file, output_dir);

    const Fw::Time start_time = this->getTime();
    const U64 start_ms =
        static_cast<U64>(start_time.getSeconds() * MSEC_PER_SEC + start_time.getUSeconds() / USEC_PER_MSEC);

    std::size_t bitstream_len = 0U;
    const bool loaded = loadBitstreamIntoBuffer(input_file.toChar(),
                                                s_bitstreamBuf,
                                                static_cast<std::size_t>(image_sample_len),
                                                bitstream_len);
    if (!loaded) {
        this->log_WARNING_HI_DecompressionFailed(input_file, -1);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const int result =
        ccsds123_decompress_with_buffer(input_file.toChar(), output_dir.toChar(), s_bitstreamBuf, bitstream_len);

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
    const std::string output_file_path = buildOutputFilePath(input_file, output_dir);
    const Os::FileSystem::Status output_size_status =
        Os::FileSystem::getFileSize(output_file_path.c_str(), output_size);
    if (output_size_status == Os::FileSystem::OP_OK) {
        this->tlmWrite_OutputImageSize(output_size);
        F64 ratio = 0.0;
        if (input_size > 0) {
            ratio = static_cast<F64>(output_size) / static_cast<F64>(input_size);
            this->tlmWrite_ExpansionRatio(ratio);
        }
        this->log_ACTIVITY_HI_DecompressionSucceeded(input_file, output_size, ratio);
    } else {
        this->log_ACTIVITY_HI_DecompressionSucceeded(input_file, output_size, 0.0);
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace ImageProcessor
