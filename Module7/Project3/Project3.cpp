// Name: Taylor Colton
// Date: 10 August, 2024

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

// Method for formatting user input
string ConvertToTitleCase(const string& str)
{
	string formattedString = "";

	// Convert entire string to lowercase
	for (char ch : str) {
		formattedString += tolower(ch);
	}

	// Replace first char with capital
	formattedString[0] = toupper(formattedString[0]);

	return formattedString;
}

void DisplayMenu() {
	cout << "***********************************" << endl;
	cout << "********** Sales Tracker **********" << endl;
	cout << "Select an item from the following: " << endl;
	cout << "  1. Find sales of one item " << endl;
	cout << "  2. Display all sales " << endl;
	cout << "  3. Display sales histogram " << endl;
	cout << "  4. Exit program " << endl;
	cout << ">";
}

// Method for getting a validated user input
int GetValidMenuOptionInput(const string& errorMessage)
{
	int userInput;
	bool validInput = false;

	// Loop until valid input is received
	while (!validInput) {
		string input;
		cin >> input;

		// Attempt to convert input to an int
		try {
			size_t pos;
			userInput = stoi(input, &pos);

			// Ensure input is 1-4
			if (pos == input.length() && userInput > 0 && userInput < 5) {
				validInput = true;
			}
			else {
				throw invalid_argument("Argument invalid!");
			}
		}
		// Catch possible errors and print error message
		// Catching by reference vice value avoids unnecessary memory allocation
		catch (invalid_argument&) {
			cout << errorMessage;
		}
		catch (out_of_range&) {
			cout << errorMessage;
		}
	}

	return userInput;
}

// Method for awaiting user input and clearing screen
void PauseAndClear() {
	cout << "Press Enter to continue . . ." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	cout << "\033[2J\033[1;1H";
}

// Base class SalesTracker
class SalesTracker {
	private: 
		// Map with string key, int value, using transparent comparator
		map<string, int, less<>> items;
		void BackupItems();
		map<string, int, less<>> ReadFile(string const& fileName) const;

	public:
		// SalesTracker constructor
		explicit SalesTracker(string const& fileName) {
			items = ReadFile(fileName);
			BackupItems();
		}
		void PrintItemTotals();
		void PrintHistogram();
		void PrintFrequency(string const& item);
};

// Method for adding items and their count to a file
void SalesTracker::BackupItems() {
	ofstream outFS;
	outFS.open("frequency.dat");

	// Iterate through key value pairs in map
	for (auto it = items.begin(); it != items.end(); ++it) {
		outFS << it->first << " " << it->second << endl;
	}
	outFS.close();
}

// Method for printing the frequency of a specific item
void SalesTracker::PrintFrequency(string const& item) {
	cout << "\n";
	string formattedString = ConvertToTitleCase(item);

	// If the key exists, print its value
	if (items.count(formattedString) != 0) {
		cout << items.at(formattedString) << endl;
	}
	else {
		cout << 0 << endl;
	}
	cout << "\n";
}

// Method for print items and their count as a histogram
void SalesTracker::PrintHistogram() {
	cout << "\n";

	for (auto it = items.begin(); it != items.end(); ++it) {
		cout << it->first << " ";
		for (int i = 0; i < it->second; i++) {
			cout << "*";
		}
		cout << endl;
	}
	cout << "\n";
}

// Method for printing all items and their count
void SalesTracker::PrintItemTotals() {
	cout << "\n";
	for (auto it = items.begin(); it != items.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}
	cout << "\n";
}

// Method for reading a file into the Sales Tracker's items map
map<string, int, less<>> SalesTracker::ReadFile(string const& fileName) const {
	map<string, int, less<>> itemMap;
	string item;
	// Read file
	ifstream inFS;

	inFS.open(fileName);

	while (inFS >> item) {
		if (itemMap.count(item) != 0) {
			itemMap.at(item)++;
		}
		else {
			itemMap.emplace(item, 1);
		}
	}

	// Return items
	return itemMap;
}

// Method for running the program
void RunSalesTracker() {
	// Use make_unique to automate memory management
	auto tracker = make_unique<SalesTracker>("CS210_Project_Three_Input_File.txt");
	int userInput = 0;

	while (userInput != 4) {
		DisplayMenu();
		userInput = GetValidMenuOptionInput("Please enter a valid number between 1 and 4!\r\n>");

		if (userInput == 1) {
			string item;
			cout << "Enter an item name: ";
			cin >> item;
			tracker->PrintFrequency(item);
			PauseAndClear();
		}
		else if (userInput == 2) {
			tracker->PrintItemTotals();
			PauseAndClear();
		}
		else if (userInput == 3) {
			tracker->PrintHistogram();
			PauseAndClear();
		}
	}
}

int main()
{
	RunSalesTracker();
}
