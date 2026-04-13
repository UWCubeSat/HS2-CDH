/**
 * @file FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressor.hpp
 * @author mahiremran
 * @brief hpp file for ImageDecompressor component implementation class
 */

#ifndef ImageProcessor_ImageDecompressor_HPP
#define ImageProcessor_ImageDecompressor_HPP

#include <cstddef>
#include <cstdint>

#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressorComponentAc.hpp"

namespace ImageProcessor {

class ImageDecompressor final : public ImageDecompressorComponentBase {
  public:
    /**
     * @brief Component construction and destruction.
     */

    /**
     * @brief Construct an ImageDecompressor component instance.
     * @param[in] compName Component instance name.
     * @pre compName is not null.
     * @post Component instance is constructed and ready for initialization.
     */
    ImageDecompressor(const char* const compName);

    /**
     * @brief Destroy the ImageDecompressor component instance.
     * @post Resources owned by this instance are released.
     */
    ~ImageDecompressor();

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
     * @brief Decompress an image bitstream into raw image data.
     * @param[in] opCode Opcode associated with this command invocation.
     * @param[in] cmdSeq Command sequence number for this invocation.
     * @param[in] input_file Path to the input .bin bitstream file.
     * @param[in] output_dir Directory where the output .raw file is written.
     * @param[in] image_sample_len Number of bytes available in the component input buffer.
     * @pre input_file and output_dir are valid command arguments.
     * @pre image_sample_len is less than or equal to kBitstreamBufBytes.
     * @post A command response is emitted indicating success or failure.
     */
    void DECOMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,
                     U32 cmdSeq,
                     const Fw::CmdStringArg& input_file,
                     const Fw::CmdStringArg& output_dir,
                     U64 image_sample_len) override;

  private:
    static constexpr std::size_t kBitstreamBufBytes = 2U * 1024U * 1024U;
    /**
     * @brief Number of milliseconds (ms) per second (s).
     */
    static constexpr U64 MSEC_PER_SEC = 1000U;
    /**
     * @brief Number of microseconds (us) per millisecond (ms).
     */
    static constexpr U64 USEC_PER_MSEC = 1000U;
    static std::uint8_t s_bitstreamBuf[kBitstreamBufBytes];
};

}  // namespace ImageProcessor

#endif
