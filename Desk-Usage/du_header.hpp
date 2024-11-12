#pragma once

#include<iostream>
#include<string>
#include<vector>
#include <sstream>
#include <algorithm>
#include<filesystem>
#include<Windows.h>
#include<deque>
#include <iomanip>
#include <filesystem>
#include<set>

// Using the std namespace for brevity
using namespace std::filesystem;

// Options class to handle command-line arguments
class Options {
public:
  
    // Constructor to initialize the options
    Options(std::vector<path>  f = {}, bool  bytes = false, bool humanReadable = false, bool summary = false
        ,bool kilobyte = false,bool sortBySize = false,bool sortByName = false,bool reverse= false, bool help = false, bool version = false, bool block_size = false, unsigned long long clusterSize = 4096) : folder(f), bytes(bytes), humanReadable(humanReadable), summary(summary)
    , kilobyte(kilobyte), sortBySize(sortBySize), sortByName(sortByName), reverse(reverse),help(help), version(version), block_size(block_size),  clusterSize(clusterSize){}
  

public:
   
    //declaring class member
    std::vector<path> folder;
    bool bytes ;
    bool humanReadable;
    bool summary;
    bool kilobyte;
    bool sortBySize;
    bool sortByName;
    bool reverse;
    bool help;
    bool version;
    bool block_size;
    unsigned long long clusterSize;


   
};




/*
 * \fn: Options parseInput(int argc, char* argv[])
 * \brief: Parses the command-line arguments and sets the appropriate options.
 * \param argc: The number of command-line arguments.
 * \param argv: An array of command-line argument strings.
 * \return: An Options object containing the parsed options.
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
Options parseInput(int argc, char* argv[]);

/*
 * \fn: void rscan(const path& folder, std::vector<std::pair<path, size_t>>& directorySizes, Options& option)
 * \brief: Recursively scans the specified folder and collects the sizes of directories.
 * \param folder: The path to the folder to scan.
 * \param directorySizes: A vector to store the sizes of directories.
 * \param option: The options object containing user preferences.
 * \return: void
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
void rscan(const std::vector<path>& folder, std::vector<std::pair<path, size_t>>& directorySizes,  Options& option);

/*
 * \fn: void collect_info(Options& option, std::vector<std::pair<path, size_t>>& directorySizes)
 * \brief: Collects and processes the directory sizes based on the provided options.
 * \param option: The options object containing user preferences.
 * \param directorySizes: A vector to store the sizes of directories.
 * \return: void
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
void collect_info(Options& option, std::vector<std::pair<path, size_t>>& directorySizes);

/*
 * \fn: void report(Options& options, const vector<pair<path, size_t>>& directorySizes)
 * \brief: Reports the collected directory sizes based on the provided options.
 * \param options: The options object containing user preferences.
 * \param directorySizes: A vector of directory paths and their sizes.
 * \return: void
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
void report(const Options& options,  std::vector<std::pair<path, size_t>>& directorySizes);

/*
 * \fn: bool compareBySize(const pair<path, size_t>& a, const pair<path, size_t>& b)
 * \brief: Comparison function for sorting directories by size.
 * \param a: The first directory-size pair to compare.
 * \param b: The second directory-size pair to compare.
 * \return: True if the size of the first directory is less than the size of the second, false otherwise.
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
inline bool compareBySize(const std::pair<path, size_t>& a, const std::pair<path, size_t>& b) {
    return a.second < b.second;
}


/*
 * \fn: bool compareByName(const pair<path, size_t>& a, const pair<path, size_t>& b)
 * \brief: Comparison function for sorting directories by name.
 * \param a: The first directory-size pair to compare.
 * \param b: The second directory-size pair to compare.
 * \return: True if the name of the first directory is less than the name of the second, false otherwise.
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
inline bool compareByName(const std::pair<path, size_t>& a, const std::pair<path, size_t>& b) {
    return a.first < b.first;
}

inline bool compareBySizeDesc(const std::pair<path, size_t>& a, const std::pair<path, size_t>& b) {
    return a.second > b.second;
}

/*
 * \fn: int calculateMaxNumberWidth(const vector<pair<string, size_t>>& data)
 * \brief: Calculates the maximum width required to display numbers in the output.
 * \param data: A vector of string-size pairs representing directories and their sizes.
 * \return: The maximum width required to display numbers.
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */
size_t calculateMaxNumberWidth(const std::vector<std::pair<std::string, size_t>>& data);

/*
 * \fn: void printswi(const vector<pair<string, size_t>>& data, size_t width)
 * \brief: Prints the directory sizes and paths formatted according to the specified width.
 * \param data: A vector of string-size pairs representing directories and their sizes.
 * \param width: The width to be used for formatting the output numbers.
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */

void printswi(const std::vector<std::pair<std::string, size_t>>& data, size_t width);

/*
 * \fn: void printswi(const std::vector<std::pair<std::string, size_t>>& data, size_t width)
 * \brief: Prints the help information
 * \param data: no paramaeters passed
 * \author: Adnan Nassan
 * \date: August 12, 2024
 */

void printHelp();
