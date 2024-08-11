/*
 * ModuleTwo.cpp
 *
 *  Date: [08 July, 2024]
 *  Author: [Taylor Colton]
 */

#include <iostream>

using namespace std;

int main() // main() should return an int, so I updated its signature to an int from a void
{
	char statement[100];
	double op1, op2; // Updated op1 and op2 from ints to doubles so the program could handle doubles from user inputs as well as ints
	char operation;
	char answer = 'Y'; // answer is a char and needs single quotes to be properly evaluated, rather than double quotes for a string

	while (answer == 'Y' || answer == 'y') // Added an OR operator to handle both lowercase and uppercase user input
	{
		cout << "Enter expression" << endl; // Added space before endl;

		cin >> op1 >> operation >> op2; // Swapped op1 and op2 to correct calculations

		if (operation == '+') // Removed ; to execute following statement and changed + to char
			cout << op1 << " + " << op2 << " = " << op1 + op2 << endl; // Fixed >> to match cout
		if (operation == '-') // Removed ; to execute following statement
			cout << op1 << " - " << op2 << " = " << op1 - op2 << endl; // Fixed >> to match cout
		if (operation == '*')
			cout << op1 << " * " << op2 << " = " << op1 * op2 << endl; // Corrected operation to match if statement
		if (operation == '/')
			cout << op1 << " / " << op2 << " = " << op1 / op2 << endl; // Corrected operation to match if statement

		cout << "Do you wish to evaluate another expression? " << endl;
		cin >> answer;
	}

	cout << "Program Finished." << endl; // Added "Program Finished." line as required
}
