# S57_Extractor
S57_Extractor is a Qt-based tool for parsing and visualizing data from S-57 nautical chart files (.000). It extracts polygons, lines, symbols, and text, enabling intuitive visualization and analysis. Built with C++ and GDAL, it supports secure access, a user-friendly interface, and efficient geospatial data handling.

## Features
- Extracts and visualizes geospatial features from S-57 files:
  - **Polygons**: Includes coordinates, colors, and associated values.
  - **Lines**: Displays linear features with relevant attributes.
  - **Symbols and Text**: Annotates chart data for intuitive analysis.
- User-friendly interface with file browser and real-time status indicators.
- Built with GDAL for robust and efficient geospatial processing.

## Technology Stack
- **Language**: C++
- **Framework**: Qt (qmake build system)
- **Libraries**: GDAL
- **Platform**: Linux (tested on Ubuntu)

## Installation
### Prerequisites
- Qt and qmake installed on your system.
- GDAL library:
  ```bash
  sudo apt-get install gdal-bin libgdal-dev
