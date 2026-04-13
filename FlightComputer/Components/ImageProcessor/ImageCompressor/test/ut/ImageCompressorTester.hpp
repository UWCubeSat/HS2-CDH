/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/test/ut/ImageCompressorTester.hpp
 * @author mahiremran
 * @brief hpp file for ImageCompressor test harness implementation class
 */

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

    /**
     * @brief Construct the ImageCompressor test harness.
     * @post Test harness and test component instances are constructed.
     */
    ImageCompressorTester();

    /**
     * @brief Destroy the ImageCompressor test harness.
     * @post Resources owned by the test harness are released.
     */
    ~ImageCompressorTester();

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
     * @brief Verify command handling for an invalid AEL value.
     * @post Expected command rejection behavior is validated.
     */
    void testInvalidAel();

    /**
     * @brief Verify command handling when sample length exceeds allowed limits.
     * @post Expected command rejection behavior is validated.
     */
    void testSampleLenTooLarge();

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
     * @brief Send a COMPRESS_IMAGE command with provided arguments.
     * @param[in] input_path Path to the input image file.
     * @param[in] output_dir Path to the output directory.
     * @param[in] ael Absolute error limit for compression.
     * @param[in] sample_len Number of samples to provide to the command.
     * @pre input_path and output_dir point to valid C strings.
     * @post The command is dispatched to the component under test.
     */
    void sendCompressCommand(const char* input_path, const char* output_dir, I32 ael, U64 sample_len);

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
    ImageCompressor component;
};

}  // namespace ImageProcessor

#endif
