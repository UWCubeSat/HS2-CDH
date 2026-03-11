// ======================================================================
// \title  ImageCompressor.hpp
// \author mahiremran
// \brief  hpp file for ImageCompressor component implementation class
// ======================================================================

#ifndef ImageProcessor_ImageCompressor_HPP
#define ImageProcessor_ImageCompressor_HPP

#include <cstddef>
#include <cstdint>

#include "FlightComputer/Components/ImageProcessor/ImageCompressor/ImageCompressorComponentAc.hpp"

namespace ImageProcessor {

class ImageCompressor final : public ImageCompressorComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ImageCompressor object
    ImageCompressor(const char* const compName  //!< The component name
    );

    //! Destroy ImageCompressor object
    ~ImageCompressor();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for ports
    // ----------------------------------------------------------------------

    //! Handler for the timeCaller port
    void timeGetPort_handler(FwIndexType portNum, Fw::Time& time) override;

    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command COMPRESS_IMAGE
    //!
    //! Command to compress a specific raw image file
    void COMPRESS_IMAGE_cmdHandler(FwOpcodeType opCode,                  //!< The opcode
                                   U32 cmdSeq,                           //!< The command sequence number
                                   const Fw::CmdStringArg& input_file,   //!< Path to input .raw file
                                   const Fw::CmdStringArg& output_dir,   //!< Output directory for .bin file
                                   I32 ael,                              //!< AEL value (>= 0)
                                   I32 override_x,                       //!< Override image X dimension
                                   I32 override_y,                       //!< Override image Y dimension
                                   I32 override_z,                       //!< Override image Z dimension
                                   const Fw::CmdStringArg& override_dtype,  //!< Override data type (e.g., u16)
                                   U64 image_sample_len                  //!< Number of samples available in the buffer
                                   ) override;

  private:
    static constexpr std::size_t kImageSampleBufBytes = 2U * 1024U * 1024U;
    static constexpr std::size_t kImageSampleBufElems = kImageSampleBufBytes / sizeof(std::int64_t);
    /** @def Number of milliseconds (ms) per second (s) */
    static constexpr U64 MSEC_PER_SEC = 1000U;
    /** @def Number of microseconds (μs) per millisecond (ms) */
    static constexpr U64 USEC_PER_MSEC = 1000U;
    static std::int64_t s_imageSampleBuf[kImageSampleBufElems];
};

}  // namespace ImageProcessor

#endif
