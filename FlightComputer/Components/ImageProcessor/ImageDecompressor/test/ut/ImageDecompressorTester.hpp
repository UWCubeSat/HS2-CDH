/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/test/ut/ImageDecompressorTester.hpp
 * @author mahiremran
 * @brief hpp file for ImageDecompressor test harness implementation class
 */

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

    /**
     * @brief Construct the ImageDecompressor test harness.
     * @post Test harness and test component instances are constructed.
     */
    ImageDecompressorTester();

    /**
     * @brief Destroy the ImageDecompressor test harness.
     * @post Resources owned by the test harness are released.
     */
    ~ImageDecompressorTester();

  public:
    /**
     * @brief Verify command handling for an empty input path.
     * @post Expected command rejection behavior is validated.
     */
    void testEmptyInputPath();

    /**
     * @brief Verify command handling for an empty output directory path.
     * @post Expected command rejection behavior is validated.
     */
    void testEmptyOutputDir();

    /**
     * @brief Verify command handling when bitstream length exceeds allowed limits.
     * @post Expected command rejection behavior is validated.
     */
    void testImageSampleLenTooLarge();

  private:
    /**
     * @brief Connect component ports for the test harness.
     * @pre Test harness and component instances are constructed.
     * @post Required input and output ports are connected.
     */
    void connectPorts();

    /**
     * @brief Initialize components used by the test harness.
     * @pre Port connections are complete.
     * @post Components are initialized and ready for test execution.
     */
    void initComponents();

    /**
     * @brief Send a DECOMPRESS_IMAGE command with provided arguments.
     * @param[in] input_path Path to the input bitstream file.
     * @param[in] output_dir Path to the output directory.
     * @param[in] image_sample_len Number of bytes to provide to the command.
     * @pre input_path and output_dir point to valid C strings.
     * @post The command is dispatched to the component under test.
     */
    void sendDecompressCommand(const char* input_path, const char* output_dir, U64 image_sample_len);

    /**
     * @brief Assert that the latest command response indicates failure.
     * @param[in] opcode Command opcode expected in the response.
     * @param[in] input_path Input path associated with the command under test.
     * @param[in] error_code Expected error code reported by the component.
     * @pre A command response has been produced by the component under test.
     * @post Test assertions validate expected failure metadata.
     */
    void assertFailure(FwOpcodeType opcode, const Fw::CmdStringArg& input_path, I32 error_code);

  private:
    ImageDecompressor component;
};

}  // namespace ImageProcessor

#endif
