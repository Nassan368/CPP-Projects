Disk Usage Utility
Overview
This project, developed by Adnan Nassan, is a C++ console application that emulates the functionality of the UNIX du (disk usage) command. It estimates file space usage on a file system, providing insights into how storage is allocated across directories and files.

The application processes files and directories from a given root directory, offering flexible options for output customization using command-line switches.

Features
Display allocation space (not absolute file space) for each file and directory.
Summarize cluster usage for the given root directory.
Flexible output formats:
Bytes, Kilobytes, or Human-Readable sizes.
Sorting by size or name.
Reverse ordering of results.
Support for additional functionality using switches:
--help: Display usage information.
--version: Display the application version.
--block-size=dddd: Set custom cluster size.

Usage
Command-Line Syntax
du [-skhznrb] [--help] [--version] [--block-size=dddd] [folder]


Project Structure
CPP-Projects/
├── du_main.cpp       # Entry point of the program
├── du_functions.cpp  # Implementation of core functionality
├── du_functions2.CPP # Additional helper functions
├── du_header.hpp     # Header file defining the Options class and function prototypes
