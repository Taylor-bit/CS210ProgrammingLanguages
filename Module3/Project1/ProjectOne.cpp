// Name: Taylor Colton
// Date: July 18, 2024

#include <iostream>
#include <format>
using namespace std;

void DisplayClockAndMenu(int hour, int minute, int second) {
    // Function for displaying both 12-Hour Clock and 24-Hour Clock simultaneously
    int twelveHour = hour;
    string period = "";
    string hour12Prefix = "";
    string hour24Prefix = "";
    string minutePrefix = "";
    string secondPrefix = "";

    // Calculate hour for 12-Hour Clock
    if (hour > 12)
        twelveHour = hour - 12;
    else if (hour == 0)
        twelveHour = 12;
    
    // Add "0" prefix to: hour, minute and second if needed (ex: 05:03:01)
    hour24Prefix = hour < 10 
        ? "0" 
        : "";
    hour12Prefix = twelveHour < 10
        ? "0"
        : "";
    minutePrefix = minute < 10
        ? "0"
        : "";
    secondPrefix = second < 10 
        ? "0" 
        : "";
    
    // Calculate whether it's AM or PM for 12-Hour Clock
    period = hour >= 12 
        ? " P M" 
        : " A M";

    // Clear console
    cout << "\033[2J\033[1;1H";
    //Display formatted clocks simultaeously
    cout << "***************************     ***************************" << endl;
    cout << "*      12-Hour Clock      *     *      24-Hour Clock      *" << endl;
    cout << "*      " << hour12Prefix << twelveHour << ":" << minutePrefix << minute << ":" << secondPrefix << second << period << "       *     ";
    cout << "*        " << hour24Prefix << hour << ":" << minutePrefix << minute << ":" << secondPrefix << second << "         *" << endl;
    cout << "***************************     ***************************" << endl;

    // Display menu options for user to update the time
    cout << "\t\t***************************" << endl;
    cout << "\t\t* 1-Add One Hour          *" << endl;
    cout << "\t\t* 2-Add One Minute        *" << endl;
    cout << "\t\t* 3-Add One Second        *" << endl;
    cout << "\t\t* 4-Exit Program          *" << endl;
    cout << "\t\t***************************" << endl;
}

void GetInputAndUpdateTime() {
    // Update time based on user input
    int userInput = 1;
    int currentHour = 22;
    int currentMinute = 57;
    int currentSecond = 57;

    while (userInput != 4) {
        // Handle user input
        if (userInput == 1) {
            // Increment hour
            currentHour++;
        }
        else if (userInput == 2) {
            // Increment minute
            currentMinute++;
        }
        else if (userInput == 3) {
            // Increment second
            currentSecond++;
        }

        // Update minute based on second if needed
        if (currentSecond == 60) {
            currentSecond = 0;
            currentMinute++;
        }
        // Update hour based on minute if needed
        if (currentMinute == 60) {
            currentMinute = 0;
            currentHour++;
        }
        // Update 24 hour based on hour if needed
        if (currentHour == 24) {
            currentHour = 0;
        }
        
        DisplayClockAndMenu(currentHour, currentMinute, currentSecond);
        // Handle invalid input from user after refreshing screen
        if (userInput < 1 || userInput > 4) {
            cout << "Please enter a valid option" << endl;
        }
        cin >> userInput;
    }
}

int main()
{
    GetInputAndUpdateTime();
}
