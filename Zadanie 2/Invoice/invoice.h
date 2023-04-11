#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "product.h"
using namespace std;

class Invoice
{
private:
	vector<Product> items;
	string seller;
	string buyer;
	string issueDate;
	string issuePlace;
public:
	Invoice(string seller, string buyer, string issueDate, string issuePlace);
	Invoice(string seller, string buyer, string issueDate, string issuePlace, vector<Product> items);
	string getSeller() const;
	string getBuyer() const;
	string getIssueDate() const;
	string getIssuePlace() const;
	vector<Product> getItems() const;
	void addItem(Product item);
	void addItem(vector<Product> items);
	int countItems() const;
	map<string, double> countTotalValue() const;
};

ostream& operator<<(ostream& os, Invoice& inv);
istream& operator>>(istream& is, Invoice& inv);