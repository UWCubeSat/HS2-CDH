/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTester.cpp
 * @author mahiremran
 * @brief cpp file for ImageDecompressor test harness implementation class
 */

#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTester.hpp"

#include <unistd.h>

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

#include <Fw/Test/UnitTest.hpp>

#include "Os/FileSystem.hpp"

extern "C" {
#include "ccsds123_internal.h"  // NOLINT(build/include_subdir)
#include "ccsds123_io.h"        // NOLINT(build/include_subdir)
}

#define INSTANCE 0

namespace ImageProcessor {

namespace {

std::string makeTempDir() {
    char pathTemplate[] = "/tmp/hs2-imgdecomp-ut-XXXXXX";
    char* dirPath = mkdtemp(pathTemplate);
    return (!dirPath) ? std::string() : std::string(dirPath);
}

bool writeBytes(const std::string& path, const std::uint8_t* data, const std::size_t size) {
    FILE* file = std::fopen(path.c_str(), "wb");
    if (!file) {
        return false;
    }

    const std::size_t written = std::fwrite(data, 1U, size, file);
    const int closeStatus = std::fclose(file);
    return (written == size) && (closeStatus == 0);
}

bool renamePath(const std::string& sourcePath, const std::string& destPath) {
    return std::rename(sourcePath.c_str(), destPath.c_str()) == 0;
}

bool copyFile(const std::string& sourcePath, const std::string& destPath) {
    FILE* source = std::fopen(sourcePath.c_str(), "rb");
    if (!source) {
        return false;
    }

    FILE* dest = std::fopen(destPath.c_str(), "wb");
    if (!dest) {
        std::fclose(source);
        return false;
    }

    std::uint8_t buf[4096];
    std::size_t read = 0U;
    while ((read = std::fread(buf, 1U, sizeof(buf), source)) > 0U) {
        if (std::fwrite(buf, 1U, read, dest) != read) {
            std::fclose(source);
            std::fclose(dest);
            return false;
        }
    }

    const bool ok = (std::ferror(source) == 0) && (std::ferror(dest) == 0) && (std::fclose(source) == 0) &&
                    (std::fclose(dest) == 0);
    return ok;
}

std::size_t getFileSizeBytes(const std::string& path) {
    FILE* file = std::fopen(path.c_str(), "rb");
    if (!file) {
        return 0U;
    }

    if (std::fseek(file, 0, SEEK_END) != 0) {
        std::fclose(file);
        return 0U;
    }

    const auto size = std::ftell(file);
    std::fclose(file);
    return (size < 0) ? 0U : static_cast<std::size_t>(size);
}

}  // namespace

/**
 * @brief Construct the ImageDecompressor test harness.
 */
ImageDecompressorTester::ImageDecompressorTester()
    : ImageDecompressorGTestBase("Tester", MAX_HISTORY_SIZE), component("ImageDecompressor") {
    this->connectPorts();
    this->initComponents();
}

/**
 * @brief Destroy the ImageDecompressor test harness.
 */
ImageDecompressorTester::~ImageDecompressorTester() {
    this->component.deinit();
}

/**
 * @brief Verify command handling for an empty input path.
 */
void ImageDecompressorTester::testEmptyInputPath() {
    Fw::CmdStringArg input("");
    Fw::CmdStringArg output("output");
    this->sendDecompressCommand(input, output, 1);
    this->assertFailure(ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling for an empty output directory path.
 */
void ImageDecompressorTester::testEmptyOutputDir() {
    Fw::CmdStringArg input("input.bin");
    Fw::CmdStringArg output("");
    this->sendDecompressCommand(input, output, 1);
    this->assertFailure(ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling when bitstream length exceeds allowed limits.
 */
void ImageDecompressorTester::testImageSampleLenTooLarge() {
    Fw::CmdStringArg input("input.bin");
    Fw::CmdStringArg output("output");
    this->sendDecompressCommand(input, output, 2097153U);
    this->assertFailure(ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, input, -1);
}

void ImageDecompressorTester::testImageSampleLenZero() {
    const std::string inputPath("test/ut/assets/test_image.bin");
    const std::size_t inputSize = getFileSizeBytes(inputPath);
    ASSERT_GT(inputSize, 0U);

    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());
    const std::string outputDir = tempDir + "/out";

    Fw::CmdStringArg input(inputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, 0U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_InputBitstreamSize(0, inputSize);
}

void ImageDecompressorTester::testImageSampleLenTooSmall() {
    const std::string inputPath("test/ut/assets/test_image.bin");
    const std::size_t inputSize = getFileSizeBytes(inputPath);
    ASSERT_GT(inputSize, 1U);

    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());
    const std::string outputDir = tempDir + "/out";

    Fw::CmdStringArg input(inputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, 1U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_InputBitstreamSize(0, inputSize);
}

void ImageDecompressorTester::testMissingInputFileAfterValidation() {
    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());

    const std::string missingInputPath = tempDir + "/missing.bin";
    const std::string outputDir = tempDir + "/out";
    Fw::CmdStringArg input(missingInputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, 1U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(0);
}

void ImageDecompressorTester::testEmptyInputFileAfterValidation() {
    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());

    const std::string emptyInputPath = tempDir + "/empty.bin";
    FILE* file = std::fopen(emptyInputPath.c_str(), "wb");
    ASSERT_NE(file, nullptr);
    ASSERT_EQ(std::fclose(file), 0);

    const std::string outputDir = tempDir + "/out";
    Fw::CmdStringArg input(emptyInputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, 1U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_InputBitstreamSize(0, 0U);
}

void ImageDecompressorTester::testDecompressionFailureAfterValidation() {
    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());

    const std::string inputPath = tempDir + "/tiny.bin";
    const std::uint8_t payload[1] = {0x00};
    ASSERT_TRUE(writeBytes(inputPath, payload, sizeof(payload)));

    const std::string outputDir = tempDir + "/out";
    Fw::CmdStringArg input(inputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, sizeof(payload));

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_SIZE(2);
    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionStarted(0, inputPath.c_str(), outputDir.c_str());
    ASSERT_EVENTS_DecompressionFailed_SIZE(1);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_InputBitstreamSize(0, sizeof(payload));
    ASSERT_TLM_DecompressionTimeMs_SIZE(1);
}

void ImageDecompressorTester::testDecompressionAssetSuccess() {
    const std::string inputPath("test/ut/assets/test_image.bin");
    const std::size_t inputSize = getFileSizeBytes(inputPath);
    ASSERT_GT(inputSize, 0U);

    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());
    const std::string outputDir = tempDir + "/out";

    Fw::CmdStringArg input(inputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, inputSize);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_InputBitstreamSize(0, inputSize);
    ASSERT_TLM_DecompressionTimeMs_SIZE(1);
}

void ImageDecompressorTester::testDecompressionSuccessWithGeneratedBitstream() {
    char shortTemplate[] = "/tmp/h2d-XXXXXX";
    char* shortDirPath = mkdtemp(shortTemplate);
    const std::string tempDir = (!shortDirPath) ? std::string() : std::string(shortDirPath);
    ASSERT_FALSE(tempDir.empty());

    const std::string rawInputPath = tempDir + "/a.raw";
    const std::uint8_t rawPayload[4] = {0x00, 0x01, 0x02, 0x03};
    ASSERT_TRUE(writeBytes(rawInputPath, rawPayload, sizeof(rawPayload)));

    const std::string compressedDir = tempDir + "/c";
    const Os::FileSystem::Status mkdirStatus = Os::FileSystem::createDirectory(compressedDir.c_str(), true);
    ASSERT_TRUE((mkdirStatus == Os::FileSystem::OP_OK) || (mkdirStatus == Os::FileSystem::ALREADY_EXISTS));

    const int compressStatus =
        ccsds123_compress_one_image(rawInputPath.c_str(), compressedDir.c_str(), 0, 2, 2, 1, "u8be");
    ASSERT_EQ(compressStatus, 0);

    const std::string compressedNoExtPath = compressedDir + "/a";
    const std::string compressedInputPath = compressedDir + "/a.bin";
    ASSERT_TRUE(renamePath(compressedNoExtPath, compressedInputPath));

    const std::size_t inputSize = getFileSizeBytes(compressedInputPath);
    ASSERT_GT(inputSize, 0U);

    const std::string outputDir = tempDir + "/d";
    const Os::FileSystem::Status outputMkdirStatus = Os::FileSystem::createDirectory(outputDir.c_str(), true);
    ASSERT_TRUE((outputMkdirStatus == Os::FileSystem::OP_OK) || (outputMkdirStatus == Os::FileSystem::ALREADY_EXISTS));

    const std::string expectedOutputPath = outputDir + "/a.raw";
    const std::uint8_t expectedOut[4] = {0x11, 0x22, 0x33, 0x44};
    ASSERT_TRUE(writeBytes(expectedOutputPath, expectedOut, sizeof(expectedOut)));

    Fw::CmdStringArg input(compressedInputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, inputSize);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_InputBitstreamSize(0, inputSize);
    ASSERT_TLM_OutputImageSize_SIZE(1);
    ASSERT_TLM_ExpansionRatio_SIZE(1);
    ASSERT_TLM_DecompressionTimeMs_SIZE(1);

    const std::size_t outputSize = getFileSizeBytes(expectedOutputPath);
    ASSERT_GT(outputSize, 0U);
    ASSERT_TLM_OutputImageSize(0, outputSize);
}

void ImageDecompressorTester::testDecompressionSuccessWithoutOutputSizeTlm() {
    char shortTemplate[] = "/tmp/h2d-XXXXXX";
    char* shortDirPath = mkdtemp(shortTemplate);
    const std::string tempDir = (!shortDirPath) ? std::string() : std::string(shortDirPath);
    ASSERT_FALSE(tempDir.empty());

    const std::string rawInputPath = tempDir + "/a.raw";
    const std::uint8_t rawPayload[4] = {0x10, 0x20, 0x30, 0x40};
    ASSERT_TRUE(writeBytes(rawInputPath, rawPayload, sizeof(rawPayload)));

    const std::string compressedDir = tempDir + "/c";
    const Os::FileSystem::Status mkdirStatus = Os::FileSystem::createDirectory(compressedDir.c_str(), true);
    ASSERT_TRUE((mkdirStatus == Os::FileSystem::OP_OK) || (mkdirStatus == Os::FileSystem::ALREADY_EXISTS));

    const int compressStatus =
        ccsds123_compress_one_image(rawInputPath.c_str(), compressedDir.c_str(), 0, 2, 2, 1, "u8be");
    ASSERT_EQ(compressStatus, 0);

    const std::string compressedNoExtPath = compressedDir + "/a";
    const std::string compressedInputPath = compressedDir + "/a.bin";
    ASSERT_TRUE(renamePath(compressedNoExtPath, compressedInputPath));

    const std::size_t inputSize = getFileSizeBytes(compressedInputPath);
    ASSERT_GT(inputSize, 0U);

    const std::string outputDir = tempDir + "/d";
    Fw::CmdStringArg input(compressedInputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, inputSize);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_DecompressionTimeMs_SIZE(1);
    ASSERT_TLM_OutputImageSize_SIZE(0);
    ASSERT_TLM_ExpansionRatio_SIZE(0);
}

void ImageDecompressorTester::testDecompressionSuccessWithSimpleInputName() {
    const std::string sourceBitstreamPath("test/ut/assets/test_image.bin");
    const std::string simpleInputPath = "h2dinput" + std::to_string(static_cast<U64>(::getpid()));
    ASSERT_TRUE(copyFile(sourceBitstreamPath, simpleInputPath));

    const std::size_t inputSize = getFileSizeBytes(simpleInputPath);
    ASSERT_GT(inputSize, 0U);

    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());
    const std::string outputDir = tempDir + "/o/";
    const Os::FileSystem::Status mkdirStatus = Os::FileSystem::createDirectory(outputDir.c_str(), true);
    ASSERT_TRUE((mkdirStatus == Os::FileSystem::OP_OK) || (mkdirStatus == Os::FileSystem::ALREADY_EXISTS));

    Fw::CmdStringArg input(simpleInputPath.c_str());
    Fw::CmdStringArg output(outputDir.c_str());
    this->sendDecompressCommand(input, output, inputSize + 1U);
    (void)std::remove(simpleInputPath.c_str());

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_DecompressionStarted_SIZE(1);
    ASSERT_EVENTS_DecompressionSucceeded_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed_SIZE(0);

    ASSERT_TLM_InputBitstreamSize_SIZE(1);
    ASSERT_TLM_OutputImageSize_SIZE(0);
    ASSERT_TLM_ExpansionRatio_SIZE(0);
    ASSERT_TLM_DecompressionTimeMs_SIZE(1);
}

void ImageDecompressorTester::testTimeGetPortNoOp() {
    Fw::Time time;
    this->invoke_to_timeGetPort(0, time);

    ASSERT_CMD_RESPONSE_SIZE(0);
    ASSERT_EVENTS_SIZE(0);
    ASSERT_TLM_SIZE(0);
}

void ImageDecompressorTester::testOutputDirCreateFailure() {
    Fw::CmdStringArg input("input.bin");
    Fw::CmdStringArg output("/dev/null/hs2-cdh-decompress");
    this->sendDecompressCommand(input, output, 1U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);
    ASSERT_EVENTS_DecompressionStarted_SIZE(0);
    ASSERT_EVENTS_DecompressionFailed_SIZE(1);
}

/**
 * @brief Send a DECOMPRESS_IMAGE command with provided arguments.
 * @param[in] input_path Path to the input bitstream file.
 * @param[in] output_dir Path to the output directory.
 * @param[in] image_sample_len Number of bytes to provide to the command.
 */
void ImageDecompressorTester::sendDecompressCommand(const Fw::CmdStringArg& input_path,
                                                    const Fw::CmdStringArg& output_dir,
                                                    U64 image_sample_len) {
    this->sendCmd_DECOMPRESS_IMAGE(INSTANCE, CMD_SEQ, input_path, output_dir, image_sample_len);
    this->component.doDispatch();
}

/**
 * @brief Assert that the latest command response indicates failure.
 * @param[in] opcode Command opcode expected in the response.
 * @param[in] input_path Input path associated with the command under test.
 * @param[in] error_code Expected error code reported by the component.
 */
void ImageDecompressorTester::assertFailure(FwOpcodeType opcode,
                                            const Fw::CmdStringArg& input_path,
                                            I32 error_code) {
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, opcode, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_DecompressionFailed(0, input_path.toChar(), error_code);
}

}  // namespace ImageProcessor
