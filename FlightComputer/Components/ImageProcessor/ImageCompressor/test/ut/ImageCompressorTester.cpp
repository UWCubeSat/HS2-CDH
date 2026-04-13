/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/test/ut/ImageCompressorTester.cpp
 * @author mahiremran
 * @brief cpp file for ImageCompressor test harness implementation class
 */

#include "ImageCompressorTester.hpp"

#include <Fw/Test/UnitTest.hpp>

#define INSTANCE 0

namespace ImageProcessor {

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
    this->sendCompressCommand(input.toChar(), "output", 0, 262145U);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

/**
 * @brief Send a COMPRESS_IMAGE command with provided arguments.
 * @param[in] input_path Path to the input image file.
 * @param[in] output_dir Path to the output directory.
 * @param[in] ael Absolute error limit for compression.
 * @param[in] sample_len Number of samples to provide to the command.
 */
void ImageCompressorTester ::sendCompressCommand(const char* input_path,
                                                 const char* output_dir,
                                                 I32 ael,
                                                 U64 sample_len) {
    Fw::CmdStringArg cmdInput(input_path);
    Fw::CmdStringArg cmdOutput(output_dir);
    Fw::CmdStringArg cmdDtype("u16");

    this->sendCmd_COMPRESS_IMAGE(INSTANCE, CMD_SEQ, cmdInput, cmdOutput, ael, 0, 0, 0, cmdDtype, sample_len);
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
