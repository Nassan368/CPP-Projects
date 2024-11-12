/*
Adnan Nassan
August 12, 2024
Overall purpose of the project:

*/
#include"du_header.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    // 1. Initialize options
    Options option;
    option = parseInput(argc, argv);
    
	vector<std::pair<path, size_t>> directorySizes;

	//2. Run a scan on a given folder based on some switch options

	collect_info(option, directorySizes);

	// Report the disk usage data based on switch options
	report(option, directorySizes);

	return 0;
}