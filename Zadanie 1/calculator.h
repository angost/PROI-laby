#pragma once
#include<iostream>
using namespace std;
class Calculator {
private:
	double memory;
	double last_operation_result;
	void debugInfo();
public:
	Calculator();
	void info();
	double add(double num1, double num2);
	double subtract(double num1, double num2);
	double multiply(double num1, double num2);
	double divide(double num1, double num2);
	void addToMemory(double num);
	void addToMemory();
	void subtractFromMemory(double num);
	void subtractFromMemory();
	double showMemory();
};

