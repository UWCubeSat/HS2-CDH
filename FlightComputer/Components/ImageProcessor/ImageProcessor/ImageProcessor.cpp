#include "ImageProcessor.hpp"
#include <string>
#include <cstdlib> // Required for std::system()

namespace ImageProcessor {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  ImageProcessor ::
    ImageProcessor(
        const char *const compName
    ) : ImageProcessorComponentBase(compName)
  {

  }

  ImageProcessor ::
    ~ImageProcessor()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ImageProcessor ::
    processImageIn_handler(
        const FwIndexType portNum,
        const Fw::StringBase& imagePath
    )
  {
      // 1. Build the terminal command. 
      // We point to the binary we just built, and pass it the image path.
      std::string command = "/workspace/found/build/bin/found distance --image " + std::string(imagePath.toChar());
      // 2. F' executes the binary in the Linux OS
      int result = std::system(command.c_str());

      // 3. Check if FOUND crashed or succeeded
      if (result == 0) {
          // SUCCESS! Read the output file FOUND generated here
      } else {
          // FAILED! Send a warning telemetry packet
      }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void ImageProcessor ::
    RunFoundTest_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CmdStringArg& imagePath
    )
  {
      // Pass the string to our processing function
      this->processImageIn_handler(0, imagePath);
      
      // Tell the Ground Station the command finished successfully!
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

} // end namespace ImageProcessor