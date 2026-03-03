# ImageProcessor::ImageCompressor

Compresses image (.raw) into .bin using CCSDS123 algo

## Usage Examples
Example command usage:

- Compress a raw image with explicit dimensions and data type.
- Provide an output directory (the output file is created under that directory).

Command:

`COMPRESS_IMAGE /data/cam/frame001.raw /data/cam/compressed 1 1024 1024 1 u16 1048576`

### Diagrams
No diagrams provided yet.

### Typical Usage
The component receives `COMPRESS_IMAGE`, validates inputs, compresses the image using CCSDS123, emits events, and publishes telemetry for runtime and sizes.

## Class Diagram
No class diagram provided yet.

## Port Descriptions
| Name | Description |
|---|---|
| timeCaller | Time get port used for compression timing telemetry. |
| prmGetOut | Parameter get port. |
| prmSetOut | Parameter set port. |
| cmdIn/cmdOut | Standard command receive/response ports from `Fw.Command`. |
| eventOut | Standard event output port from `Fw.Event`. |
| tlmOut | Standard telemetry output port from `Fw.Channel`. |

## Component States
Add component states in the chart below
| Name | Description |
|---|---|
| Idle | No compression in progress. |
| Compressing | Active while `COMPRESS_IMAGE` is executing. |

## Sequence Diagrams
Typical command flow:

1. Ground sends `COMPRESS_IMAGE`.
2. Component validates inputs, logs `CompressionStarted`.
3. Component invokes CCSDS123 compression routine.
4. Component publishes telemetry and logs `CompressionSucceeded` or `CompressionFailed`.
5. Component returns command response.

## Parameters
| Name | Description |
|---|---|
| None | No parameters are defined. |

## Commands
| Name | Description |
|---|---|
| COMPRESS_IMAGE | Compresses a `.raw` image into a `.bin` file using CCSDS123. Inputs include file path, output directory, AEL, overrides for X/Y/Z, data type, and sample buffer length. |

## Events
| Name | Description |
|---|---|
| CompressionStarted | Emitted when compression begins. |
| CompressionFailed | Emitted when validation or compression fails. Includes error code. |
| CompressionSucceeded | Emitted when compression succeeds. Includes output size and ratio. |

## Telemetry
| Name | Description |
|---|---|
| CompressionTimeMs | Total compression runtime in milliseconds. |
| InputImageSize | Input image size in bytes. |
| OutputImageSize | Output image size in bytes. |
| CompressionRatio | $\text{InputImageSize} / \text{OutputImageSize}$. |

## Unit Tests
Add unit test descriptions in the chart below
| Name | Description | Output | Coverage |
|---|---|---|---|
| None | No unit tests defined. | N/A | N/A |

## Requirements
Add requirements in the chart below
| Name | Description | Validation |
|---|---|---|
| IMG-COMP-001 | The component shall compress a raw image file using CCSDS123 given a valid input path and output directory. | Analysis/Test |
| IMG-COMP-002 | The component shall reject commands with missing paths or invalid AEL. | Analysis/Test |
| IMG-COMP-003 | The component shall emit telemetry for compression time and input/output sizes. | Analysis/Test |
| IMG-COMP-004 | The component shall emit a success or failure event for each command invocation. | Analysis/Test |

## Change Log
| Date | Description |
|---|---|
| 2026-02-17 | Filled out SDD with command, events, telemetry, and behavior. |