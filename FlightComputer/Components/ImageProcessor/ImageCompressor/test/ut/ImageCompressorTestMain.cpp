/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/test/ut/ImageCompressorTestMain.cpp
 * @brief Test main for ImageCompressor unit tests.
 */

#include "FlightComputer/Components/ImageProcessor/ImageCompressor/test/ut/ImageCompressorTester.hpp"

TEST(Validation, EmptyInputPath) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testEmptyInputPath();
}

TEST(Validation, EmptyOutputDir) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testEmptyOutputDir();
}

TEST(Validation, InvalidAel) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testInvalidAel();
}

TEST(Validation, SampleLenTooLarge) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testSampleLenTooLarge();
}

TEST(Validation, OutputDirIsFile) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testOutputDirIsFile();
}

TEST(Validation, CompressionFailureAfterValidation) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testCompressionFailureAfterValidation();
}

TEST(Validation, CompressionSuccessWithAsset) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testCompressionSuccessWithAsset();
}

TEST(Validation, CompressionSuccessWithoutOutputSizeTlm) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testCompressionSuccessWithoutOutputSizeTlm();
}

TEST(Validation, CompressionSuccessWithSimpleInputName) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testCompressionSuccessWithSimpleInputName();
}

TEST(Validation, TimeGetPortNoOp) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testTimeGetPortNoOp();
}

TEST(Validation, OutputDirCreateFailure) {
    ImageProcessor::ImageCompressorTester tester;
    tester.testOutputDirCreateFailure();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
