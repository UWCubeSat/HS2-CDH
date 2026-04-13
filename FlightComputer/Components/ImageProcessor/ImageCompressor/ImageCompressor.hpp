/**
 * @file FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressor.hpp
 * @author mahiremran
 * @brief hpp file for ImageCompressor component implementation class
 */

#ifndef ImageProcessor_ImageCompressor_HPP
#define ImageProcessor_ImageCompressor_HPP

#include <cstddef>
#include <cstdint>

#include "FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressorComponentAc.hpp"

namespace ImageProcessor {

class ImageCompressor final : public ImageCompressorComponentBase {
  public:
    /**
     * @brief Component construction and destruction.
     */

    /**
     * @brief Construct an ImageCompressor component instance.
     * @param[in] compName Component instance name.
     * @pre compName is not null.
     * @post Component instance is constructed and ready for initialization.
     */
    ImageCompressor(const char* const compName);

    /**
     * @brief Destroy the ImageCompressor component instance.
     * @post Resources owned by this instance are released.
     */
    ~ImageCompressor();

  private:
    /**
     * @brief Handler implementations for ports.
     */

    /**
     * @brief Handle a request for the current time.
     * @param[in] portNum Port index that invoked the handler.
     * @param[out] time Time object to populate with the current value.
     * @pre time references a valid object.
     * @post time contains the current time value from the configured source.
     */
    void timeGetPort_handler(FwIndexType portNum, Fw::Time& time) override;

    /**
     * @brief Handler implementations for commands.
     */

    /**
     * @brief Compress a raw image into a bitstream.
     * @param[in] opCode Opcode associated with this command invocation.
     * @param[in] cmdSeq Command sequence number for this invocation.
     * @param[in] input_file Path to the input .raw image file.
     * @param[in] output_dir Directory where the output .bin file is written.
     * @param[in] ael Absolute error limit used for compression.
     * @param[in] override_x Override image X dimension, or implementation-defined default when unused.
     * @param[in] override_y Override image Y dimension, or implementation-defined default when unused.
     * @param[in] override_z Override image Z dimension, or implementation-defined default when unused.
     * @param[in] override_dtype Override sample data type string (for example, u16).
     * @param[in] image_sample_len Number of image samples available in the component input buffer.
     * @pre input_file and output_dir are valid command arguments.
     * @pre image_sample_len is less than or equal to kImageSampleBufElems.
     * @post A command response is emitted indicating success or failure.
     */
    void COMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,
                     U32 cmdSeq,
                     const Fw::CmdStringArg& input_file,
                     const Fw::CmdStringArg& output_dir,
                     I32 ael,
                     I32 override_x,
                     I32 override_y,
                     I32 override_z,
                     const Fw::CmdStringArg& override_dtype,
                     U64 image_sample_len) override;

  private:
    static constexpr std::size_t kImageSampleBufBytes = 2U * 1024U * 1024U;
    static constexpr std::size_t kImageSampleBufElems = kImageSampleBufBytes / sizeof(std::int64_t);
    /**
     * @brief Number of milliseconds (ms) per second (s).
     */
    static constexpr U64 MSEC_PER_SEC = 1000U;
    /**
     * @brief Number of microseconds (us) per millisecond (ms).
     */
    static constexpr U64 USEC_PER_MSEC = 1000U;
    static std::int64_t s_imageSampleBuf[kImageSampleBufElems];
};

}  // namespace ImageProcessor

#endif
