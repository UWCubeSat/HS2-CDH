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

    /**
     * @brief Verify command failure when provided bitstream length is zero.
     * @post Loader failure path is validated after command prechecks.
     */
    void testImageSampleLenZero();

    /**
     * @brief Verify command failure when provided bitstream length is smaller than file size.
     * @post Loader truncation failure path is validated.
     */
    void testImageSampleLenTooSmall();

    /**
     * @brief Verify command failure when input file cannot be opened after validation.
     * @post Loader file-open failure branch is validated.
     */
    void testMissingInputFileAfterValidation();

    /**
     * @brief Verify command failure when input file exists but is empty.
     * @post Loader zero-byte branch is validated without truncation short-circuit.
     */
    void testEmptyInputFileAfterValidation();

    /**
     * @brief Verify failure path after validation with an existing bitstream file.
     * @post Start event and timing/size telemetry are validated before failure.
     */
    void testDecompressionFailureAfterValidation();

    /**
     * @brief Verify successful decompression using the checked-in bitstream asset.
     * @post Command success and success event behavior are validated.
     */
    void testDecompressionAssetSuccess();

    /**
     * @brief Verify successful decompression using a generated valid bitstream.
     * @post Command success, success event, and output telemetry are validated.
     */
    void testDecompressionSuccessWithGeneratedBitstream();

    /**
     * @brief Verify successful decompression when derived output file size lookup fails.
     * @post Command success with zero-ratio success event path is validated.
     */
    void testDecompressionSuccessWithoutOutputSizeTlm();

    /**
     * @brief Verify success with no-slash/no-dot input name, trailing-slash output dir, and oversized sample length.
     * @post Path-shape and loader size-relationship branches are validated.
     */
    void testDecompressionSuccessWithSimpleInputName();

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
