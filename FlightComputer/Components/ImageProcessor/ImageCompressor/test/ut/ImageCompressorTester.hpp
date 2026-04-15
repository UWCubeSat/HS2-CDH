/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/test/ut/ImageCompressorTester.hpp
 * @author mahiremran
 * @brief hpp file for ImageCompressor test harness implementation class
 */

#ifndef FLIGHTCOMPUTER_COMPONENTS_IMAGEPROCESSOR_IMAGECOMPRESSOR_TEST_UT_IMAGECOMPRESSORTESTER_HPP_
#define FLIGHTCOMPUTER_COMPONENTS_IMAGEPROCESSOR_IMAGECOMPRESSOR_TEST_UT_IMAGECOMPRESSORTESTER_HPP_

#include "FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressorGTestBase.hpp"
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

    /**
     * @brief Verify command handling when output path points to a file.
     * @post Expected command rejection behavior is validated.
     */
    void testOutputDirIsFile();

    /**
     * @brief Verify failure path after validation with an existing input file.
     * @post Start event and timing/size telemetry are validated before failure.
     */
    void testCompressionFailureAfterValidation();

    /**
     * @brief Verify successful compression using the bundled raw asset.
     * @post Command success and success event behavior are validated.
     */
    void testCompressionSuccessWithAsset();

    /**
     * @brief Verify successful compression when derived output file size lookup fails.
     * @post Success event is emitted with zero-valued ratio path.
     */
    void testCompressionSuccessWithoutOutputSizeTlm();

    /**
     * @brief Verify successful compression with no-slash/no-dot input name and trailing-slash output dir.
     * @post Path-shape branches in output filename derivation are validated.
     */
    void testCompressionSuccessWithSimpleInputName();

    /**
     * @brief Verify time port handler can be invoked without side effects.
     */
    void testTimeGetPortNoOp();

    /**
     * @brief Verify command failure when output directory creation fails.
     */
    void testOutputDirCreateFailure();

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
       * @param[in] sample_len Number of bytes to provide to the command.
       * @pre input_path and output_dir contain valid command string arguments.
     * @post The command is dispatched to the component under test.
     */
    void sendCompressCommand(const Fw::CmdStringArg& input_path,
                                           const Fw::CmdStringArg& output_dir,
                                           I32 ael,
                                           U64 sample_len,
                                           I32 override_x = 0,
                                           I32 override_y = 0,
                                           I32 override_z = 0,
                                           const char* dtype = "u16");

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

#endif  // FLIGHTCOMPUTER_COMPONENTS_IMAGEPROCESSOR_IMAGECOMPRESSOR_TEST_UT_IMAGECOMPRESSORTESTER_HPP_
