// Name: Taylor Colton
// Date: 31 July, 2024

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static double CalculateCelsiusTemp(int fTemp) {
	// Used 32.0 to force cTemp to be calculated as a double instead of an int
	double cTemp = (fTemp - 32.0) * 5 / 9;
	return cTemp;
}

static int ReadAndWriteToFile() {
	ifstream inFS; // Input file stream
	ofstream outFS; // Output file stream
	string city;
	int fTemp;

	// Open file streams
	inFS.open("FahrenheitTemperature.txt");
	outFS.open("CelsiusTemperature.txt");

	// Verify file is opened uccessfully
	if (!inFS.is_open() || !outFS.is_open()) {
		cout << "Could not open one of the files" << endl;
		return 1;
	}

	// Loop to read all cities and temps
	while (!inFS.eof()) {
		inFS >> city >> fTemp;

		if (!inFS.fail()) {
			// Write city and temp in Celsius to CelsiusTemperature.txt
			outFS << city << " " << CalculateCelsiusTemp(fTemp) << endl;
		}
	}

	// Close files
	inFS.close();
	outFS.close();
}

int main()
{
	ReadAndWriteToFile();
}
