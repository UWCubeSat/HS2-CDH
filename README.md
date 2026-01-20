# HS2-CDH

Husky Satellite Lab Command and Data Handling (CDH) flight software for the HS2 CubeSat mission.  
This repository uses NASA’s F Prime (F´) framework for flight software development.

## Overview

This repository contains the CDH subsystem flight software. CDH is responsible for handling commands, routing telemetry, 
and coordinating interactions between subsystems. Development follows the component-based architecture provided by F Prime.

## Prerequisites

Supported platforms:

- Linux
- macOS
- Windows using WSL

Required tools:

- CMake 3.16 or newer
- GCC or Clang with C++11 support
- Python 3.9 or newer

F Prime tools:

pip install fprime-tools fprime-gds

## Getting Started

Clone the repository:

git clone https://github.com/UWCubeSat/HS2-CDH.git
cd HS2-CDH

Initialize the F Prime submodule:

git submodule update --init --recursive

(Optional) Create and activate a Python virtual environment:

python3 -m venv fprime-venv
source fprime-venv/bin/activate
pip install -r lib/fprime/requirements.txt
pip install fprime-tools fprime-gds

Generate build files:

fprime-util generate

Build the project:

fprime-util build

## Development

Software development follows standard F Prime practices:

- Functionality is implemented as components
- Components communicate through typed ports
- Commands, telemetry, and events are used for control and observability

The F Prime commands and workflow used in this repository are based on the HS2-Software repository and the official F Prime documentation:

- https://nasa.github.io/fprime/
- https://fprime.jpl.nasa.gov/docs/

## Adding Components

New components can be created using:

fprime-util new --component <ComponentName>

## Testing

Tests can be run with:
```bash
fprime-util check```

## Contributing

Do not push directly to the main branch.  
Create a feature branch, commit your changes, and open a pull request for review.
