/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTestMain.cpp
 * @brief Test main for ImageDecompressor unit tests.
 */

#include "ImageDecompressorTester.hpp"

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
