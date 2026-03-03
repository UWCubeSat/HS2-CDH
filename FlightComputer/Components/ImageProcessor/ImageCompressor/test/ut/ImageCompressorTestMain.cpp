// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "ImageCompressorTester.hpp"

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
