#ifndef ImageProcessor_ImageProcessor_HPP
#define ImageProcessor_ImageProcessor_HPP

#include "FlightComputer/Components/ImageProcessor/ImageProcessor/ImageProcessorComponentAc.hpp"

namespace ImageProcessor {

class ImageProcessor final : public ImageProcessorComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ImageProcessor object
    ImageProcessor(const char* const compName  //!< The component name
    );

    //! Destroy ImageProcessor object
    ~ImageProcessor();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for processImageIn
    void processImageIn_handler(FwIndexType portNum,             //!< The port number
                                const Fw::StringBase& imagePath  //!< The path to the image file in storage
                                ) override;

    //! Handler implementation for RunFoundTest command
    void RunFoundTest_cmdHandler(FwOpcodeType opCode, //!< The opcode
                                 U32 cmdSeq,          //!< The command sequence number
                                 const Fw::CmdStringArg& imagePath //!< The image path
                                 ) override;
};

}  // namespace ImageProcessor

#endif