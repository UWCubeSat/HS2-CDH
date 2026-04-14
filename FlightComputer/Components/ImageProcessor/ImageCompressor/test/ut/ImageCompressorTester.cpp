/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/test/ut/ImageCompressorTester.cpp
 * @author mahiremran
 * @brief cpp file for ImageCompressor test harness implementation class
 */

#include "ImageCompressorTester.hpp"

#include <Fw/Test/UnitTest.hpp>

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

#include <unistd.h>

#include "Os/FileSystem.hpp"

#define INSTANCE 0

namespace ImageProcessor {

namespace {

std::string makeTempDir() {
    char pathTemplate[] = "/tmp/hs2-imgcomp-ut-XXXXXX";
    char* dirPath = mkdtemp(pathTemplate);
    return (dirPath == nullptr) ? std::string() : std::string(dirPath);
}

bool writeBytes(const std::string& path, const std::uint8_t* data, const std::size_t size) {
    FILE* file = std::fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return false;
    }

    const std::size_t written = std::fwrite(data, 1U, size, file);
    const int closeStatus = std::fclose(file);
    return (written == size) && (closeStatus == 0);
}

std::vector<std::uint8_t> readBytes(const std::string& path) {
    std::vector<std::uint8_t> data;
    FILE* file = std::fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return data;
    }

    if (std::fseek(file, 0, SEEK_END) != 0) {
        std::fclose(file);
        return data;
    }

    const long size = std::ftell(file);
    if (size <= 0) {
        std::fclose(file);
        return data;
    }

    if (std::fseek(file, 0, SEEK_SET) != 0) {
        std::fclose(file);
        return data;
    }

    data.resize(static_cast<std::size_t>(size));
    const std::size_t read = std::fread(data.data(), 1U, data.size(), file);
    std::fclose(file);

    if (read != data.size()) {
        data.clear();
    }
    return data;
}

std::size_t getFileSizeBytes(const std::string& path) {
    FILE* file = std::fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return 0U;
    }

    if (std::fseek(file, 0, SEEK_END) != 0) {
        std::fclose(file);
        return 0U;
    }

    const long size = std::ftell(file);
    std::fclose(file);
    return (size < 0) ? 0U : static_cast<std::size_t>(size);
}

}  // namespace

/**
 * @brief Construct the ImageCompressor test harness.
 */
ImageCompressorTester ::ImageCompressorTester()
    : ImageCompressorGTestBase("Tester", MAX_HISTORY_SIZE), component("ImageCompressor") {
    this->connectPorts();
    this->initComponents();
}

/**
 * @brief Destroy the ImageCompressor test harness.
 */
ImageCompressorTester ::~ImageCompressorTester() {
    this->component.deinit();
}

/**
 * @brief Verify command handling for an empty input path.
 */
void ImageCompressorTester ::testEmptyInputPath() {
    Fw::CmdStringArg input("");
    this->sendCompressCommand(input.toChar(), "output", 0, 1);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling for an empty output directory path.
 */
void ImageCompressorTester ::testEmptyOutputDir() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "", 0, 1);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling for an invalid AEL value.
 */
void ImageCompressorTester ::testInvalidAel() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "output", -1, 1);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling when sample length exceeds allowed limits.
 */
void ImageCompressorTester ::testSampleLenTooLarge() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "output", 0, 2097153U);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

void ImageCompressorTester ::testOutputDirIsFile() {
    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());

    const std::string outputAsFile = tempDir + "/not_a_directory";
    const std::string invalidOutputDir = outputAsFile + "/child";
    const std::uint8_t byte = 0xAB;
    ASSERT_TRUE(writeBytes(outputAsFile, &byte, 1U));

    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), invalidOutputDir.c_str(), 0, 1U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageCompressor::OPCODE_COMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);
    ASSERT_EVENTS_CompressionFailed_SIZE(1);
}

void ImageCompressorTester ::testCompressionFailureAfterValidation() {
    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());

    const std::string inputPath = tempDir + "/tiny.raw";
    const std::uint8_t payload[4] = {0x00, 0x01, 0x02, 0x03};
    ASSERT_TRUE(writeBytes(inputPath, payload, sizeof(payload)));

    const std::string outputDir = tempDir + "/out";
    this->sendCompressCommand(inputPath.c_str(), outputDir.c_str(), 0, sizeof(payload));

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageCompressor::OPCODE_COMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_SIZE(2);
    ASSERT_EVENTS_CompressionStarted_SIZE(1);
    ASSERT_EVENTS_CompressionStarted(0, inputPath.c_str(), outputDir.c_str());
    ASSERT_EVENTS_CompressionFailed_SIZE(1);

    ASSERT_TLM_InputImageSize_SIZE(1);
    ASSERT_TLM_InputImageSize(0, sizeof(payload));
    ASSERT_TLM_CompressionTimeMs_SIZE(1);
}

void ImageCompressorTester ::testCompressionSuccessWithAsset() {
    const std::string inputAssetPath("test/ut/assets/test_image.raw");
    const std::size_t inputSize = getFileSizeBytes(inputAssetPath);
    ASSERT_GT(inputSize, 0U);

    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());
    const std::string outputDir = tempDir + "/out";

    this->sendCompressCommand(inputAssetPath.c_str(), outputDir.c_str(), 0, inputSize, 1024, 1024, 1, "u8be");

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageCompressor::OPCODE_COMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_CompressionStarted_SIZE(1);
    ASSERT_EVENTS_CompressionSucceeded_SIZE(1);
    ASSERT_TLM_InputImageSize_SIZE(1);
    ASSERT_TLM_InputImageSize(0, inputSize);
    ASSERT_TLM_OutputImageSize_SIZE(1);
    ASSERT_TLM_CompressionRatio_SIZE(1);
    ASSERT_TLM_CompressionTimeMs_SIZE(1);
}

void ImageCompressorTester ::testCompressionSuccessWithoutOutputSizeTlm() {
    const std::string inputAssetPath("test/ut/assets/test_image.raw");
    const std::vector<std::uint8_t> inputData = readBytes(inputAssetPath);
    ASSERT_FALSE(inputData.empty());

    char shortTemplate[] = "/tmp/h2c-XXXXXX";
    char* shortDirPath = mkdtemp(shortTemplate);
    const std::string tempDir = (shortDirPath == nullptr) ? std::string() : std::string(shortDirPath);
    ASSERT_FALSE(tempDir.empty());

    const std::string oddInputPath = tempDir + "/a.raw.bak";
    ASSERT_TRUE(writeBytes(oddInputPath, inputData.data(), inputData.size()));

    const std::string outputDir = tempDir + "/o";
    this->sendCompressCommand(oddInputPath.c_str(), outputDir.c_str(), 0, inputData.size(), 1024, 1024, 1, "u8be");

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageCompressor::OPCODE_COMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_CompressionStarted_SIZE(1);
    ASSERT_EVENTS_CompressionSucceeded_SIZE(1);
    ASSERT_EVENTS_CompressionFailed_SIZE(0);

    ASSERT_TLM_InputImageSize_SIZE(1);
    ASSERT_TLM_CompressionTimeMs_SIZE(1);
    ASSERT_TLM_OutputImageSize_SIZE(0);
    ASSERT_TLM_CompressionRatio_SIZE(0);
}

void ImageCompressorTester ::testCompressionSuccessWithSimpleInputName() {
    const std::string inputAssetPath("test/ut/assets/test_image.raw");
    const std::vector<std::uint8_t> inputData = readBytes(inputAssetPath);
    ASSERT_FALSE(inputData.empty());

    const std::string simpleInputPath = "h2cinput" + std::to_string(static_cast<unsigned long>(::getpid()));
    ASSERT_TRUE(writeBytes(simpleInputPath, inputData.data(), inputData.size()));

    const std::string tempDir = makeTempDir();
    ASSERT_FALSE(tempDir.empty());
    const std::string outputDir = tempDir + "/o/";
    const Os::FileSystem::Status mkdirStatus = Os::FileSystem::createDirectory(outputDir.c_str(), true);
    ASSERT_TRUE((mkdirStatus == Os::FileSystem::OP_OK) || (mkdirStatus == Os::FileSystem::ALREADY_EXISTS));

    this->sendCompressCommand(simpleInputPath.c_str(), outputDir.c_str(), 0, inputData.size(), 1024, 1024, 1, "u8be");
    (void)std::remove(simpleInputPath.c_str());

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageCompressor::OPCODE_COMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::OK);

    ASSERT_EVENTS_CompressionStarted_SIZE(1);
    ASSERT_EVENTS_CompressionSucceeded_SIZE(1);
    ASSERT_EVENTS_CompressionFailed_SIZE(0);

    ASSERT_TLM_InputImageSize_SIZE(1);
    ASSERT_TLM_OutputImageSize_SIZE(1);
    ASSERT_TLM_CompressionRatio_SIZE(1);
    ASSERT_TLM_CompressionTimeMs_SIZE(1);
}

void ImageCompressorTester ::testTimeGetPortNoOp() {
    Fw::Time time;
    this->invoke_to_timeGetPort(0, time);

    ASSERT_CMD_RESPONSE_SIZE(0);
    ASSERT_EVENTS_SIZE(0);
    ASSERT_TLM_SIZE(0);
}

void ImageCompressorTester ::testOutputDirCreateFailure() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "/dev/null/hs2-cdh-compress", 0, 1U);

    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, ImageCompressor::OPCODE_COMPRESS_IMAGE, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);
    ASSERT_EVENTS_CompressionStarted_SIZE(0);
    ASSERT_EVENTS_CompressionFailed_SIZE(1);
}

/**
 * @brief Send a COMPRESS_IMAGE command with provided arguments.
 * @param[in] input_path Path to the input image file.
 * @param[in] output_dir Path to the output directory.
 * @param[in] ael Absolute error limit for compression.
 * @param[in] sample_len Number of bytes to provide to the command.
 */
void ImageCompressorTester ::sendCompressCommand(const char* input_path,
                                                 const char* output_dir,
                                                 I32 ael,
                                                 U64 sample_len,
                                                 I32 override_x,
                                                 I32 override_y,
                                                 I32 override_z,
                                                 const char* dtype) {
    Fw::CmdStringArg cmdInput(input_path);
    Fw::CmdStringArg cmdOutput(output_dir);
    Fw::CmdStringArg cmdDtype(dtype);

    this->sendCmd_COMPRESS_IMAGE(INSTANCE,
                                 CMD_SEQ,
                                 cmdInput,
                                 cmdOutput,
                                 ael,
                                 override_x,
                                 override_y,
                                 override_z,
                                 cmdDtype,
                                 sample_len);
    this->component.doDispatch();
}

/**
 * @brief Assert that the latest command response indicates failure.
 * @param[in] opcode Command opcode expected in the response.
 * @param[in] input_path Input path associated with the command under test.
 * @param[in] error_code Expected error code reported by the component.
 */
void ImageCompressorTester ::assertFailure(FwOpcodeType opcode, const Fw::CmdStringArg& input_path, I32 error_code) {
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, opcode, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_CompressionFailed(0, input_path.toChar(), error_code);
}

}  // namespace ImageProcessor
