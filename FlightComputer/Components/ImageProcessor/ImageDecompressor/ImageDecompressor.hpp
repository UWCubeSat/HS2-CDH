// ======================================================================
// \title  ImageDecompressor.hpp
// \author mahiremran
// \brief  hpp file for ImageDecompressor component implementation class
// ======================================================================

#ifndef ImageProcessor_ImageDecompressor_HPP
#define ImageProcessor_ImageDecompressor_HPP

#include <cstddef>
#include <cstdint>

#include "FlightComputer/Components/ImageProcessor/ImageDecompressor/ImageDecompressorComponentAc.hpp"

namespace ImageProcessor {

class ImageDecompressor final : public ImageDecompressorComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ImageDecompressor object
    ImageDecompressor(const char* const compName  //!< The component name
    );

    //! Destroy ImageDecompressor object
    ~ImageDecompressor();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for ports
    // ----------------------------------------------------------------------

    //! Handler for the timeCaller port
    void timeGetPort_handler(FwIndexType portNum, Fw::Time& time) override;

    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command DECOMPRESS_IMAGE
    //!
    //! Command to decompress a specific bitstream file
    void DECOMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,                //!< The opcode
                                     U32 cmdSeq,                         //!< The command sequence number
                                     const Fw::CmdStringArg& input_file, //!< Path to input .bin file
                                     const Fw::CmdStringArg& output_dir, //!< Output directory for .raw file
                                     U64 image_sample_len                //!< Number of bytes available in the buffer
                                     ) override;

  private:
    static constexpr std::size_t kBitstreamBufBytes = 2U * 1024U * 1024U;
    /** @def Number of milliseconds (ms) per second (s) */
    static constexpr U64 MSEC_PER_SEC = 1000U;
    /** @def Number of microseconds (us) per millisecond (ms) */
    static constexpr U64 USEC_PER_MSEC = 1000U;
    static std::uint8_t s_bitstreamBuf[kBitstreamBufBytes];
};

}  // namespace ImageProcessor

#endif