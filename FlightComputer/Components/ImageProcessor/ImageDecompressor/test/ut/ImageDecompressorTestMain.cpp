/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTestMain.cpp
 * @brief Test main for ImageDecompressor unit tests.
 */

#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTester.hpp"

TEST(Validation, EmptyInputPath) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testEmptyInputPath();
}

TEST(Validation, EmptyOutputDir) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testEmptyOutputDir();
}

TEST(Validation, ImageSampleLenTooLarge) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testImageSampleLenTooLarge();
}

TEST(Validation, ImageSampleLenZero) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testImageSampleLenZero();
}

TEST(Validation, ImageSampleLenTooSmall) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testImageSampleLenTooSmall();
}

TEST(Validation, MissingInputFileAfterValidation) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testMissingInputFileAfterValidation();
}

TEST(Validation, EmptyInputFileAfterValidation) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testEmptyInputFileAfterValidation();
}

TEST(Validation, DecompressionFailureAfterValidation) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testDecompressionFailureAfterValidation();
}

TEST(Validation, DecompressionAssetSuccess) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testDecompressionAssetSuccess();
}

TEST(Validation, DecompressionSuccessWithGeneratedBitstream) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testDecompressionSuccessWithGeneratedBitstream();
}

TEST(Validation, DecompressionSuccessWithoutOutputSizeTlm) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testDecompressionSuccessWithoutOutputSizeTlm();
}

TEST(Validation, DecompressionSuccessWithSimpleInputName) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testDecompressionSuccessWithSimpleInputName();
}

TEST(Validation, TimeGetPortNoOp) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testTimeGetPortNoOp();
}

TEST(Validation, OutputDirCreateFailure) {
    ImageProcessor::ImageDecompressorTester tester;
    tester.testOutputDirCreateFailure();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
