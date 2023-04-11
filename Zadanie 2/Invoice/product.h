#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Product
{
private:
	string name;
	// Price per unit
	double price;
	// Amount of units
	double amount;
	double value;
	string currency;
public:
	Product(string name, double price, double amount, string currency);
	string getName() const;
	double getPrice() const;
	double getAmount() const;
	double getValue() const;
	string getCurrency() const;
	void setAmount(double number);
	bool operator==(Product compare) const;
	void operator+=(Product productToAdd);
};

ostream& operator<<(ostream& os, Product& prod);