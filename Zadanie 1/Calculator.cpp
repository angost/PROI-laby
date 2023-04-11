#include <iostream>
#include "calculator.h"
using namespace std;


Calculator::Calculator()
{
    memory = 0.0;
    last_operation_result = 0.0;
}

void Calculator::info()
{
    cout << "This is a Calculator class operating on doubles" << endl;
    cout << "Methods add, subtract, multiply, divide require 2 arguments" << endl;
    cout << "Calculator has its memory with 0 being the default value" << endl;
    cout << "Memory can be shown using showMemory, incremented using addToMemory or decremented using subtractFromMemory" << endl;
    cout << "Methods addToMemory and subtractFromMemory use result of the last operation if the argument is not provided" << endl;
}

void Calculator::debugInfo()
{
    #ifdef NDEBUG
        ;
    #else
        cout << "--------------" << endl;
        cout << "DEBUG INFO:" << endl;
        cout << "Current memory: " << this->memory << endl;
        cout << "Last operation result: " << this->last_operation_result << endl;
        cout << "--------------" << endl;
    #endif
}

double Calculator::add(double num1, double num2)
{
    double result = num1 + num2;
    this->last_operation_result = result;
    return result;
}

double Calculator::subtract(double num1, double num2)
{
    double result = num1 - num2;
    this->last_operation_result = result;
    return result;
}

double Calculator::multiply(double num1, double num2)
{
    double result = num1 * num2;
    this->last_operation_result = result;
    return result;
}

double Calculator::divide(double num1, double num2)
{
    if (num2 == 0.0)
    {
        throw runtime_error("Zero Division Error");
    }
    double result = num1 / num2;
    this->last_operation_result = result;
    return result;
}

void Calculator::addToMemory(double num)
{
    this->debugInfo();
    this->memory += num;
}

void Calculator::addToMemory()
{
    this->debugInfo();
    this->memory += this->last_operation_result;
}

void Calculator::subtractFromMemory(double num)
{
    this->debugInfo();
    this->memory -= num;
}

void Calculator::subtractFromMemory()
{
    this->debugInfo();
    this->memory -= this->last_operation_result;
}

double Calculator::showMemory()
{
    return this->memory;
}