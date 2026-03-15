// ======================================================================
// \title  ImageCompressor/test/ut/Tester.hpp
// \author mahiremran
// \brief  hpp file for ImageCompressor test harness implementation class
// ======================================================================

#ifndef ImageProcessor_ImageCompressor_Tester_HPP
#define ImageProcessor_ImageCompressor_Tester_HPP

#include "ImageCompressorGTestBase.hpp"
#include "FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressor.hpp"

namespace ImageProcessor {

class ImageCompressorTester : public ImageCompressorGTestBase {
  public:
    static const U32 MAX_HISTORY_SIZE = 10;
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;
    static const U32 CMD_SEQ = 0;

    ImageCompressorTester();
    ~ImageCompressorTester();

  public:
    void testEmptyInputPath();
    void testEmptyOutputDir();
    void testInvalidAel();
    void testSampleLenTooLarge();

  private:
    void connectPorts();
    void initComponents();
    void sendCompressCommand(const char* input_path, const char* output_dir, I32 ael, U64 sample_len);
    void assertFailure(FwOpcodeType opcode, const Fw::CmdStringArg& input_path, I32 error_code);

  private:
    ImageCompressor component;
};

}  // namespace ImageProcessor

#endif
