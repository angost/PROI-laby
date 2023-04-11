#include<iostream>
#include <vector>
#include <map>
#include "invoice.h"
#include "product.h"
using namespace std;

Invoice::Invoice(string seller, string buyer, string issueDate, string issuePlace)
{
	this->seller = seller;
	this->buyer = buyer;
	this->issueDate = issueDate;
	this->issuePlace = issuePlace;
}

Invoice::Invoice(string seller, string buyer, string issueDate, string issuePlace, vector<Product> items)
{
	this->seller = seller;
	this->buyer = buyer;
	this->issueDate = issueDate;
	this->issuePlace = issuePlace;
	this->items = items;
}

string Invoice::getSeller() const
{
	return this->seller;
}

string Invoice::getBuyer() const
{
	return this->buyer;
}

string Invoice::getIssueDate() const
{
	return this->issueDate;
}

string Invoice::getIssuePlace() const
{
	return this->issuePlace;
}

vector<Product> Invoice::getItems() const
{
	return this->items;
}

void Invoice::addItem(Product item)
{
	this->items.push_back(item);
}

void Invoice::addItem(vector<Product> items)
{
	for (Product itemToAdd : items)
	{
		this->items.push_back(itemToAdd);
	}
}

int Invoice::countItems() const
{
	return int (this->items.size());
}

map<string, double> Invoice::countTotalValue() const
{
	map<string, double> totalValue = {
		{"PLN", 0},
		{"USD", 0},
		{"EUR", 0}
	};
	double USDtoPLN = 4.35;
	double EURtoPLN = 4.69;
	for (Product item : this->getItems())
	{
		double itemValue = item.getValue();
		string itemCurrency = item.getCurrency();
		if (itemCurrency == "USD")
		{
			itemValue = itemValue * USDtoPLN;
		}
		else if (itemCurrency == "EUR")
		{
			itemValue = itemValue * EURtoPLN;
		}
		totalValue["PLN"] += itemValue;
	}
	totalValue["USD"] = totalValue["PLN"] / USDtoPLN;
	totalValue["EUR"] = totalValue["PLN"] / EURtoPLN;
	return totalValue;
}

ostream& operator<<(ostream& os, Invoice& inv)
{
	os << inv.countItems() << endl;
	for (Product prod : inv.getItems())
	{
		os << prod << endl;
	}
	return os;
}

istream& operator>>(istream& is, Invoice& inv)
{
	int itemSize;
	is >> itemSize;
	for (int i = 0; i < itemSize; i++)
	{
		string name; double price; double amount; string currency;
		is >> name; is >> price; is >> amount; is >> currency;
		Product prod(name, price, amount, currency);
		inv.addItem(prod);	
	}
	return is;
}
