// ======================================================================
// \title  ImageCompressor/test/ut/Tester.cpp
// \author mahiremran
// \brief  cpp file for ImageCompressor test harness implementation class
// ======================================================================

#include "ImageCompressorTester.hpp"

#include <Fw/Test/UnitTest.hpp>

#define INSTANCE 0

namespace ImageProcessor {

ImageCompressorTester ::ImageCompressorTester()
    : ImageCompressorGTestBase("Tester", MAX_HISTORY_SIZE), component("ImageCompressor") {
    this->connectPorts();
    this->initComponents();
}

ImageCompressorTester ::~ImageCompressorTester() {
    this->component.deinit();
}

void ImageCompressorTester ::testEmptyInputPath() {
    Fw::CmdStringArg input("");
    this->sendCompressCommand(input.toChar(), "output", 0, 1);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

void ImageCompressorTester ::testEmptyOutputDir() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "", 0, 1);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

void ImageCompressorTester ::testInvalidAel() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "output", -1, 1);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

void ImageCompressorTester ::testSampleLenTooLarge() {
    Fw::CmdStringArg input("input.raw");
    this->sendCompressCommand(input.toChar(), "output", 0, 262145U);
    this->assertFailure(ImageCompressor::OPCODE_COMPRESS_IMAGE, input, -1);
}

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

void ImageCompressorTester ::assertFailure(FwOpcodeType opcode, const Fw::CmdStringArg& input_path, I32 error_code) {
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, opcode, CMD_SEQ, Fw::CmdResponse::EXECUTION_ERROR);

    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_CompressionFailed(0, input_path.toChar(), error_code);
}

}  // namespace ImageProcessor
