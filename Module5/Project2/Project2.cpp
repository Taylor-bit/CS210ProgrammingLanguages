// Name: Taylor Colton
// Date: 04 August, 2024

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#pragma region HelperFunctions
// Helper functions for getting user input
double GetValidDoubleInput(const string& errorMessage)
{
    double userInput;
    bool validInput = false;

    while (!validInput) {
        cin >> userInput;

        // check that input was valid
        if (cin.fail()) {
            // clear the error, ignore bad input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Print error message
            cout << errorMessage << endl;
        }
        else {
            // Valid input
            validInput = true;
        }
    }

    return userInput;
}

int GetValidIntegerInput(const string& errorMessage)
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

            // Check for remaining chars after the int
            if (pos == input.length()) {
                validInput = true;
            }
            else {
                throw invalid_argument("Extra characters found");
            }
        }
        // Catch possible errors and print error message
        catch (invalid_argument) {
            cout << errorMessage << endl;
        }
        catch (out_of_range) {
            cout << errorMessage << endl;
        }
    }

    return userInput;
}
#pragma endregion

// Function for calculating and formatting
// balance and interest data for reports
void DisplayReportData(
    int numberOfYears,
    double currentBalance,
    double monthlyDeposit,
    double monthlyInterestRate)
{
    // Declare necessary variables
    double annualInterest = 0.0;
    double monthlyInterest = 0;
    int minInterestWidth = 30;
    int minTotalWidth = 25;
    vector<string> annualInterestStrings;
    vector<string> annualTotalStrings;

    // Calculate monthly values, print annual values
    for (int i = 1; i <= numberOfYears * 12; i++)
    {
        currentBalance += monthlyDeposit;
        monthlyInterest = currentBalance * monthlyInterestRate;
        currentBalance += monthlyInterest;

        annualInterest += monthlyInterest;

        // Prints only annual values with format
        if (i % 12 == 0) {
            // Convert annual balance to formatted string
            // 123.1234 => "$123.12"
            ostringstream oss;
            oss << fixed << setprecision(2) << currentBalance;
            string totalStr = "$" + oss.str();

            // Add str to vector of formatted strs
            annualTotalStrings.push_back(totalStr);

            // Determine min total width
            int width = totalStr.length();
            minTotalWidth = minTotalWidth > width
                ? minTotalWidth
                : width;

            // Reset oss for next string
            oss.clear();
            oss.str("");

            // Convert annual interest to formatted string
            oss << annualInterest;
            string annualInterestStr = "$" + oss.str();

            // Add str to vector of formatted interest strs
            annualInterestStrings.push_back(annualInterestStr);

            // Determine min interest width
            width = annualInterestStr.length();
            minInterestWidth = minInterestWidth > width
                ? minInterestWidth
                : width;

            // Reset annual interest for accuracy
            annualInterest = 0.0;
        }
    }
    // Loop through values based on number of years, format and print
    for (int i = 0; i < numberOfYears; i++) {
        cout << setw(4) << right << "     " << i + 1;
        cout << setw(minTotalWidth) << right << annualTotalStrings[i];
        cout << setw(minInterestWidth) << right << annualInterestStrings[i] << "\n\n";
    }
}

void DisplayMenuAndReports() 
{
    double initialInvestmentAmount;
    double monthlyDeposit;
    double monthlyInterestRate;
    double annualInterestRate;
    int numberOfYears;
    double currentBalance;

    // Display menu to user
    cout << "********************************" << endl;
    cout << "********** Data Input **********" << endl;
    cout << "Initial Investment Amount: " << endl;
    cout << "Monthly Deposit: " << endl;
    cout << "Annual Interest: " << endl;
    cout << "Number of years: " << endl;
    cout << "Press any key to continue . . ." << "\n" << endl;
    cin.get();

    // Clear console
    cout << "\033[2J\033[1;1H";

    // Get user investment data
    cout << "Initial Investment Amount: ";
    initialInvestmentAmount = GetValidDoubleInput("The investment amount must be a valid decimal!");
    cout << "Monthly Deposit: ";
    monthlyDeposit = GetValidDoubleInput("The monthly deposit must be a valid decimal!");
    cout << "Annual Interest: ";
    annualInterestRate = GetValidDoubleInput("The annual interest must be a valid decimal!");
    cout << "Number of years: ";
    numberOfYears = GetValidIntegerInput("The number of years must be a valid whole number!");

    // Clear the \n from buffer, clear the screen
    cin.ignore();
    cout << "\033[2J\033[1;1H";

    // Display menu with user investment data entered
    cout << "********************************" << endl;
    cout << "********** Data Input **********" << endl;
    cout << "Initial Investment Amount: $" << initialInvestmentAmount << endl;
    cout << "Monthly Deposit: $" << monthlyDeposit << endl;
    cout << "Annual Interest: %" << annualInterestRate << endl;
    cout << "Number of years: " << numberOfYears << endl;
    cout << "Press any key to continue . . ." << "\n" << endl;
    cin.get();

    cout << "\033[2J\033[1;1H";

    // Report header for no additional monthly deposits
    cout << "         Balance and Interest Without Additional Monthly Deposits          " << endl;
    cout << "===========================================================================" << endl;
    cout << "  Year              Year End Balance          Year End Earned Interest     " << endl;
    cout << "---------------------------------------------------------------------------" << "\n" << endl;

    currentBalance = initialInvestmentAmount;
    monthlyInterestRate = (annualInterestRate / 100) / 12;

    // Display report data with no additional monthly deposits
    DisplayReportData(numberOfYears, currentBalance, 0, monthlyInterestRate);

    // Report header for additional monthly deposits
    cout << "         Balance and Interest With Additional Monthly Deposits             " << endl;
    cout << "===========================================================================" << endl;
    cout << "  Year              Year End Balance          Year End Earned Interest     " << endl;
    cout << "---------------------------------------------------------------------------" << "\n" << endl;

    // Display report data with additional monthly deposits
    DisplayReportData(numberOfYears, currentBalance, monthlyDeposit, monthlyInterestRate);

    cout << "Press any key to continue . . ." << endl;
    cin.get();

    cout << "\033[2J\033[1;1H";

}

// Give user the option to start over or exit the program
void GetUserInput()
{
    // Set formatting for doubles
    cout << fixed << setprecision(2) << right;
    int userInput = 1;

    while (userInput == 1) {
        DisplayMenuAndReports();

        cout << "Enter 1 or 2 to continue: " << "\n" << endl;
        cout << "1. Make changes to investment options" << endl;
        cout << "2. Exit program" << endl;
        userInput = GetValidIntegerInput("Valid inputs are 1 or 2. Please try again!");

        // Validate user input
        while (userInput != 1 && userInput != 2) {
            cout << "Valid inputs are 1 or 2. Please try again!" << endl;
            userInput = GetValidIntegerInput("Valid inputs are 1 or 2. Please try again!");
        }
    }
}

int main() 
{
    GetUserInput();
}
