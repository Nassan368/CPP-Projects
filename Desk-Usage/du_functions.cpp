/*
Adnan Nassan
August 12, 2024
To hold all implementatios.

*/


#include"du_header.hpp"
using namespace std;


Options parseInput(int argc, char* argv[]) {

	Options option{};
	deque<string> args{};
	string switches{};
	set<char> encounteredSwitches; // Set to keep track of switches already seen
	set<char> validSwitches{ 'b', 'z', 'n', 'r', 'h', 's', 'k' };
	

	// Store all command-line arguments into the deque
	for (int i = 1; i < argc; ++i) {
		args.push_back(argv[i]);
	}


	// Process each argument
	while (!args.empty())
	{
		// If the argument is a switch (starts with '-') but not a long switch ('--')
		if (args.front().at(0) == '-' && args.front().at(1) != '-')
		{
			// Extract switches after the '-'
			switches = args.front().substr(1);



			//check for duplicate switches
			for (char switchChar : switches) {
				if (encounteredSwitches.find(switchChar) != encounteredSwitches.end()) {
					cout << "Error: duplicate switches: <" << switchChar <<">" << endl;
					exit(1); // Terminate execution
				}
				// Record the switch as encountered
				encounteredSwitches.insert(switchChar);
			}

			//check for a valid switch
			for (char switchChar : switches) 
			{
				if (validSwitches.find(switchChar) == validSwitches.end()) 
				{
					cout << "Error: unknown switches: <" << switchChar <<">" << endl;
					exit(1); // Terminate execution
				}
			}

			// Specific check for '-hb' or '-bh'
			// it has to be checked on the top to have the same output 
			//in the tester du.exe provided
			size_t hPos = switches.find('h');
			size_t bPos = switches.find('b');

			if (hPos != string::npos && bPos != string::npos) {
				
				cout << "Error: cannot use both -b and -h" << endl;
				exit(1); // Terminate execution
			}
			
			// Remove the processed switch argument from the deque	
			args.pop_front();

			// Process each valid switch in the current argument
			
				//b switch
				size_t index = switches.find('b');
				if (index != string::npos)
				{
					option.bytes = true;
					option.humanReadable = false;  // Disable human-readable if -b is set last
					switches.erase(index, 1);

				}

				//z switches
				index = switches.find('z');
				if (index != string::npos)
				{
					option.sortBySize = true;
					switches.erase(index, 1);

					if (option.sortByName && option.sortBySize)
					{
						cout << "Error: -z and -n switches are incompatible." << endl;
						exit(1); // Terminate execution
					}

				}
				
				// n switch

				index = switches.find('n');
				if (index != string::npos)
				{
					option.sortByName = true;
					switches.erase(index, 1);

					if (option.sortByName && option.sortBySize)
					{
						cout << "Error: -n and -z switches are incompatible." << endl;
						exit(1); // Terminate execution
					}

				}

				//r switch

				index = switches.find('r');
				if (index != string::npos)
				{
					option.reverse = true;
					switches.erase(index, 1);

				}

				// h switch 

				index = switches.find('h');
				if (index != string::npos)
				{
					option.humanReadable = true;
					option.bytes = false;  // Disable bytes if -h is set last
					switches.erase(index, 1);

				}

				//s switch

				index = switches.find('s');
				if (index != string::npos)
				{
					option.summary = true;
					switches.erase(index, 1);

				}

				// k switch

				index = switches.find('k');
				if (index != string::npos)
				{
					option.kilobyte = true;
					option.clusterSize = 1024;
					switches.erase(index, 1);

					if (option.kilobyte && option.block_size)
					{
						cout << "Error: -k and --block-size are incompatible." << endl;
						exit(1); // Terminate execution

					}

				}
			//}
	
		}
		// If the argument is a long switch (starts with '--')
		else if (args.front().at(0) == '-' && args.front().at(1) == '-')
		{
			// Extract
			switches = args.front().substr(2);

			// Remove processed argument from the deque
			args.pop_front();

			// Handle the '--help' switch
			if (switches.find("help") != string::npos)
			{
				option.help = true;
				if (option.version) 
				{
					option.version = false;//don't print version if comes after
				}
				if (option.block_size) 
				{
					option.block_size = false;//dpn't print block-size if comes after
				}

				// Print help information
				printHelp();
			}
			
			
			// Handle the '--version' switch
			else if (switches.find("version") != string::npos)
			{

				if (!option.help) //help is the dominante
				{
					option.version = true;
					cout << "2.0.0" << endl;
				}
				
				if (option.block_size)
				{
					option.block_size = false;//version switch should have the control
				}
					
				
				
				
			}

			// Handle the '--block-size=dddd' switch
			else if (switches.find("block-size=") != string::npos)
			{
				//set blockSize flag to zero if one of these switches or both of them
				//was called
				if (option.help && option.version)
				{
					option.block_size = false;
					
				}
				else{
					string blockSizeStr = switches.substr(11);
					option.block_size = true;
					

					// Check if the blockSizeStr is a valid positive integer
					bool isValid = true;
					for (char c : blockSizeStr) {
						if (!isdigit(c)) {
							isValid = false;
							break;
						}
					}

					//print an error if is not numeric
					if (!isValid || blockSizeStr.empty()) {
						cout << "Error: block-size value is invalid <" << blockSizeStr << ">" << endl;
						exit(1); // Terminate execution 
					}

					//convert to integet if the number is numeric
					int temp = stoi(blockSizeStr);


					//print error if the number less than 1
					if (temp < 1)
					{
						cout << "Error: block-size value too small <" << temp << ">" << endl;
						exit(1); // Terminate execution
					}

					//when clusterSize variable is greater than 1, means that block size is true 
					// because the clustersize will hold the block-size= switch vlaue, and k is true
					//so print error
					else if (option.kilobyte && option.clusterSize > 1)
					{
						cout << "Error: -k and --block-size are incompatible." << endl;
						exit(1); // Terminate execution
					}
					else
					{
						option.clusterSize = temp;//temp stisfy all conditions
					}
				}
				
			}
			//if not any of the switches print error
			else 
			{
				cout << "Error: Bad switch <--" << switches << ">" << endl;
				exit(1);
			}

		//if isn't any of the cases , then it is the folder
		}
		else 
		{
			if (!args.empty()) 
			{
				//the folder the last element of the deque
				option.folder.push_back(args.front());
				// Check if the file/folder exists
				if (!exists(option.folder.back())) {
					cout << "Error: folder <" << option.folder.front().string() << "> doesn't exist." << endl;
					exit(1);
				}

				args.pop_front();//remove the taken argument
			}
			
			
			
		}
	}

	//if no argument passed to the vector option.folder, then pass the current directory
	if (option.folder.empty()) 
	{
		option.folder.push_back(".");
	}
	return option;
}

//Collect function
void collect_info(Options& option, std::vector<std::pair<path, size_t>>& directorySizes) {
	
	rscan(option.folder, directorySizes, option);
	
}

//reprot function
void report(const Options& options,  vector<pair<path, size_t>>& directorySizes) {
	vector<pair<string, size_t>> data;

	// Populate the vector with paths as strings
	for (const auto& entry : directorySizes) {
		data.push_back({ entry.first.string(), entry.second });
	}

	
	//call the calculateMaxNumberWidth function
	size_t maxNumberWidth = calculateMaxNumberWidth(data);

	//when help && version switches is false, will have the access to test other switches
	if (!options.help && !options.version)
	{
		//when summary switch is false, will have the access to test other switches
		if (!options.summary)
		{
			//when reverse switch is true, will have the access to test other switches
			if (options.reverse)
			{
				if (options.sortBySize)
				{
					sort(data.begin(), data.end(), compareBySize);
					reverse(data.begin(), data.end());

					//Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else if (options.bytes)
				{
					reverse(data.begin(), data.end());
					for (auto& entry : data)
					{
						entry.second = entry.second * options.clusterSize;
					}

					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);

				}
				else if (options.humanReadable) {
					reverse(data.begin(), data.end());
					for (const auto& entry : data) {
						size_t sizeInBytes = entry.second * options.clusterSize;
						double size = static_cast<double>(sizeInBytes);
						std::string suffix = "B";

						if (size >= 1024) {
							size /= 1024;
							suffix = "K";
						}
						if (size >= 1024) {
							size /= 1024;
							suffix = "M";
						}
						if (size >= 1024) {
							size /= 1024;
							suffix = "G";
						}
						if (size >= 1024) {
							size /= 1024;
							suffix = "T";
						}

						// Round the size and format it
						ostringstream ss;
						if (size >= 10 || suffix == "B") {
							ss << fixed << setprecision(0) << size;
						}
						else {
							ss << fixed << setprecision(1) << size;
						}
						ss << suffix;

						// Handle the case of 0 size
						if (size == 0) {
							ss.str("0");
						}

						// Print the formatted output
						string humanReadable = ss.str();
						cout << humanReadable << "\t" << entry.first << endl;
					}
					exit(0);
				}
				//kilobytes 
				else if (options.kilobyte)
				{
					reverse(data.begin(), data.end());
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else if (options.sortByName) {

					sort(data.begin(), data.end(), compareByName);
					reverse(data.begin(), data.end());
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else if (options.block_size)
				{
					reverse(data.begin(), data.end());
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else {
					reverse(data.begin(), data.end());
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
			}//end the selection when the reverse is true
			else// start the selection when reverse is false
			{
				if (options.sortBySize)
				{

					reverse(data.begin(), data.end());
					sort(data.begin(), data.end(), compareBySize);

					//Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else if (options.bytes)
				{

					for (auto& entry : data)
					{
						entry.second = entry.second * options.clusterSize;
					}

					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);

				}
				else if (options.humanReadable) {

					for (const auto& entry : data) {
						size_t sizeInBytes = entry.second * options.clusterSize;
						double size = static_cast<double>(sizeInBytes);
						std::string suffix = "B";

						if (size >= 1024) {
							size /= 1024;
							suffix = "K";
						}
						if (size >= 1024) {
							size /= 1024;
							suffix = "M";
						}
						if (size >= 1024) {
							size /= 1024;
							suffix = "G";
						}
						if (size >= 1024) {
							size /= 1024;
							suffix = "T";
						}

						// Round the size and format it
						ostringstream ss;
						if (size >= 10 || suffix == "B") {
							ss << fixed << setprecision(0) << size;
						}
						else {
							ss << fixed << setprecision(1) << size;
						}
						ss << suffix;

						// Handle the case of 0 size
						if (size == 0) {
							ss.str("0");
						}

						// Print the formatted output
						string humanReadable = ss.str();
						cout << humanReadable << "\t" << entry.first << endl;
					}
					exit(0);
				}
				//kilobytes 
				else if (options.kilobyte)
				{
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else if (options.sortByName) {
					sort(data.begin(), data.end(), compareByName);
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
				else if (options.block_size)
				{
					// Print the data
					printswi(data, maxNumberWidth);
					exit(0);
				}
			}
		}//end the selection when summary is false
		else//start the other part when summary is true
		{
			//print the summary.
			set<std::string> printedPaths;  // Set to track printed paths globally within the function
			for (const auto& entry : options.folder)
			{

				for (const auto& entry1 : data)
				{
					if (entry.string() == entry1.first && printedPaths.find(entry1.first) == printedPaths.end())
					{
						cout << setw(maxNumberWidth) << left << entry1.second;
						cout << setw(3) << " ";
						cout << right << entry1.first << endl;
						printedPaths.insert(entry1.first);  // Mark the path as printed
					}
				}

				
			}
			exit(0);
		}//end summary
	}//end help && version
	
	
	//default print when no switches were provided
	if (!options.help && !options.version) 
	{
		if (options.folder.size() == 1) //print when the option.folder vector 
          	                           //only has the current folder
		{
			for (const auto& entry : data) {
				
				cout << setw(maxNumberWidth) << left << entry.second;
				cout << setw(3) << " ";
				cout << right << entry.first << endl;
			}
		}
		//print when folders are provided but no swithces
		else 
		{
			printswi(data, maxNumberWidth);
		}
		
		exit(0);
	
	}
	
}//end this pain finally!!!!




