// ======================================================================
// \title  ImageDecompressor/test/ut/Tester.hpp
// \author mahiremran
// \brief  hpp file for ImageDecompressor test harness implementation class
// ======================================================================

#ifndef ImageProcessor_ImageDecompressor_Tester_HPP
#define ImageProcessor_ImageDecompressor_Tester_HPP

#include "ImageDecompressorGTestBase.hpp"
#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressor.hpp"

namespace ImageProcessor {

class ImageDecompressorTester : public ImageDecompressorGTestBase {
  public:
    static const U32 MAX_HISTORY_SIZE = 10;
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;
    static const U32 CMD_SEQ = 0;

    ImageDecompressorTester();
    ~ImageDecompressorTester();

  public:
    void testEmptyInputPath();
    void testEmptyOutputDir();
    void testImageSampleLenTooLarge();

  private:
    void connectPorts();
    void initComponents();
    void sendDecompressCommand(const char* input_path, const char* output_dir, U64 image_sample_len);
    void assertFailure(FwOpcodeType opcode, const Fw::CmdStringArg& input_path, I32 error_code);

  private:
    ImageDecompressor component;
};

}  // namespace ImageProcessor

#endif