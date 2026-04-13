/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTester.cpp
 * @author mahiremran
 * @brief cpp file for ImageDecompressor test harness implementation class
 */

#include "ImageDecompressorTester.hpp"

#include <Fw/Test/UnitTest.hpp>

#define INSTANCE 0

namespace ImageProcessor {

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
    this->sendDecompressCommand(input.toChar(), "output", 1);
    this->assertFailure(ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling for an empty output directory path.
 */
void ImageDecompressorTester::testEmptyOutputDir() {
    Fw::CmdStringArg input("input.bin");
    this->sendDecompressCommand(input.toChar(), "", 1);
    this->assertFailure(ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, input, -1);
}

/**
 * @brief Verify command handling when bitstream length exceeds allowed limits.
 */
void ImageDecompressorTester::testImageSampleLenTooLarge() {
    Fw::CmdStringArg input("input.bin");
    this->sendDecompressCommand(input.toChar(), "output", 2097153U);
    this->assertFailure(ImageDecompressor::OPCODE_DECOMPRESS_IMAGE, input, -1);
}

/**
 * @brief Send a DECOMPRESS_IMAGE command with provided arguments.
 * @param[in] input_path Path to the input bitstream file.
 * @param[in] output_dir Path to the output directory.
 * @param[in] image_sample_len Number of bytes to provide to the command.
 */
void ImageDecompressorTester::sendDecompressCommand(const char* input_path,
                                                    const char* output_dir,
                                                    U64 image_sample_len) {
    Fw::CmdStringArg cmdInput(input_path);
    Fw::CmdStringArg cmdOutput(output_dir);

    this->sendCmd_DECOMPRESS_IMAGE(INSTANCE, CMD_SEQ, cmdInput, cmdOutput, image_sample_len);
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
