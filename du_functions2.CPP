#include"du_header.hpp"

using namespace std;
void printHelp() 
{

	// Print help information
	cout << "du (c) 2018-21, Adnan Nassan" << endl;
    cout << "===========================================================" << endl;
	cout << "Version 2.0.0" << endl;
	cout << endl;
	cout << "A disk usage utility inspired by the UNIX du command." << endl;
	cout << endl;
	cout << "Usage: du [-skhb] [--help] [--version] [--block-size=dddd] [folder]" << endl;
	cout << endl;
	cout << "Examples:" << endl;

	cout << "  du" << endl;
	cout << "    > display the sum of the cluster sizes of each directory" << endl;
	cout << "      starting the cwd" << endl;
	cout << endl;

	cout << "  du folder" << endl;
	cout << "    > display the sum of the cluster sizes of each directory" << endl;
	cout << "      starting with 'folder'" << endl;
	cout << endl;

	cout << "  du -h" << endl;
	cout << "    > display the results in a human readable form" << endl;
	cout << endl;

	cout << "  du -s" << endl;
	cout << "    > display only the final summary" << endl;
	cout << endl;

	cout << "  du -b" << endl;
	cout << "    > display in bytes" << endl;
	cout << endl;

	cout << "  du -k" << endl;
	cout << "    > cluster size is 1024" << endl;
	cout << endl;

	cout << "  du -z" << endl;
	cout << "    > display the list sorted by size" << endl;
	cout << endl;

	cout << "  du -n" << endl;
	cout << "    > display the list sorted by name" << endl;
	cout << endl;

	cout << "  du -r" << endl;
	cout << "    > display the list in reverse order" << endl;
	cout << endl;

	cout << "  du --block-size=dddd" << endl;
	cout << "    > set the cluster size to the specified integer > 0" << endl;
	cout << endl;

	cout << "  du --help" << endl;
	cout << "    > displays the help" << endl;
	cout << endl;

	cout << "  du --version" << endl;
	cout << "    > displays version number in the format d.d.d" << endl;
}

//function to return the greates file size which will help in output formating
size_t calculateMaxNumberWidth(const vector<pair<string, size_t>>& data) {
	size_t maxNumberWidth = 0;

	for (const auto& entry : data) {
		size_t width = to_string(entry.second).length();
		if (width > maxNumberWidth) {
			maxNumberWidth = width;
		}
	}

	return maxNumberWidth;
}

//print function to print the formated output
void printswi(const vector<pair<string, size_t>>& data, size_t width)
{
	//Print the data
	for (const auto& entry : data) {
		cout << setw(width) << left << entry.second;
		cout << setw(3) << " ";
		cout << right << entry.first << endl;
	}
}

void rscan(const vector<path>& folder, std::vector<std::pair<path, size_t>>& directorySizes, Options& option) {
	// Get the root drive name to calculate cluster size
	auto drive = std::filesystem::absolute(option.folder.front()).root_name().string() + '\\';
	uintmax_t clusterSize = 0;
	DWORD sectorsPerCluster, bytesPerSector, numberFreeClusters, totalNumberOfClusters;

	// Get cluster size using the Windows API
	if (GetDiskFreeSpaceA(drive.c_str(), &sectorsPerCluster, &bytesPerSector, &numberFreeClusters, &totalNumberOfClusters)) {
		clusterSize = uintmax_t(sectorsPerCluster) * bytesPerSector;
	}

	//declaring some temporary variable to hold file sizes
	unsigned long long dirSize = 0;
	unsigned long long fileSize = 0;
	unsigned long long temp = 0;
	unsigned long long temp1 = 0;

	//check each direcotry in the vector folder
	for (const auto& currentFolder : folder) {

		// Iterate over each entry in the directory
		if (is_directory(currentFolder)) {
			for (const auto& entry : directory_iterator(currentFolder)) {
				if (is_directory(entry.path())) {

					// Recursively iterate over all subdirectories
					for (const auto& sub_entry : recursive_directory_iterator(entry.path())) {
						if (is_regular_file(sub_entry.path())) {

							// Get the size of the file
							temp = file_size(sub_entry.path());
							fileSize = file_size(sub_entry.path()) / option.clusterSize;

							// rounding to one one the file size less than the cluster size
							if (temp % option.clusterSize != 0) {
								fileSize += 1;
							}

							// Add the file size to the root directory size
							dirSize += fileSize;
						}
					}

					// Store the directory size and the path
					directorySizes.push_back({ entry.path(), dirSize });
					temp1 += dirSize;
					dirSize = 0;
				}

				//if is a regular file of the root folder hold in a different
				//temprory variable to be added only to the root folder size
				else if (is_regular_file(entry.path())) {
					temp = file_size(entry.path());
					fileSize = file_size(entry.path()) / option.clusterSize;
					if (temp % option.clusterSize != 0) {
						fileSize += 1;
					}
					temp1 += fileSize;
				}
			}
			directorySizes.push_back({ currentFolder, temp1 });
		}
		//reset the variables to recive the new folder
		temp = 0;
		dirSize = 0;
		temp1 = 0;
	}
}

