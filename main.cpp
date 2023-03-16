/*
Project: Calculator
Author: Angelika Ostrowska

Environments tested: Visual Studio (Windows), Clion (Windows)

*/

#include <iostream>
#include "calculator.h"
using namespace std;

int main()
{
	Calculator calc;
	double a = 10.0;
	double b = 5.0;
	double c = 0.0;

	calc.info();
	cout << endl;
	cout << "Addition: 10.0 + 5.0 = " << calc.add(a, b) << endl;
	cout << "Subtraction: 10.0 - 5.0 = " << calc.subtract(a, b) << endl;
	cout << "Subtraction: 5.0 - 10.0 = " << calc.subtract(b, a) << endl;
	cout << "Multiplication: 10.0 * 5.0 = " << calc.multiply(a, b) << endl;
	cout << "Division: 10.0 / 5.0 = " << calc.divide(a, b) << endl;
	cout << "Division: 5.0 / 10.0 = " << calc.divide(b, a) << endl << endl;

	cout << "Show Memory: " << calc.showMemory() << endl;
	calc.addToMemory();
	cout << "Add last operation's result to Memory" << endl;
	cout << "Memory: " << calc.showMemory() << endl;
	calc.subtractFromMemory();
	cout << "Subtract last operation's result from Memory" << endl;
	cout << "Memory: " << calc.showMemory() << endl << endl;

	calc.addToMemory(4.5);
	cout << "Add given value to Memory: Memory + 4.5" << endl;
	cout << "Memory: " << calc.showMemory() << endl;
	calc.subtractFromMemory(8.0);
	cout << "Subtract given value from Memory: Memory - 8.0" << endl;
	cout << "Memory: " << calc.showMemory() << endl << endl;

	/*
	cout << "Attempt to do 10.0 / 0.0 will throw Zero Division Error" << endl;
	try
	{
		calc.divide(a, c);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	*/

	return 0;
}
