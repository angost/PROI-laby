#include<iostream>
#include "product.h"
using namespace std;

Product::Product(string name, double price, double amount, string currency)
{
	this->name = name;
	if (price < 0.0)
	{
		throw runtime_error("Price cannot be negative");
	}
	this->price = price;
	if (amount <= 0.0)
	{
		throw runtime_error("Amount cannot be negative nor zero");
	}
	this->amount = amount;
	if (currency != "USD" && currency != "EUR" && currency != "PLN")
		throw runtime_error("Currency has to be either USD, EUR or PLN");
	this->currency = currency;
	value = price * amount;
}

string Product::getName() const
{
	return this->name;
}

double Product::getPrice() const
{
	return this->price;
}

double Product::getAmount() const
{
	return this->amount;
}

double Product::getValue() const
{
	return this->value;
}

string Product::getCurrency() const
{
	return this->currency;
}

void Product::setAmount(double amount)
{
	if (amount <= 0.0)
	{
		throw runtime_error("Amount cannot be negative nor zero");
	}
	this->amount = amount;
	this->value = this->getPrice() * amount;
}


bool Product::operator==(Product compare) const
{
	bool equalName = (this->getName() == compare.getName());
	bool equalPrice = (this->getPrice() == compare.getPrice());
	bool equalAmount = (this->getAmount() == compare.getAmount());
	bool equalCurrency = (this->getCurrency() == compare.getCurrency());
	return (equalName && equalPrice && equalAmount && equalCurrency);
}

void Product::operator+=(Product productToAdd)
{
	bool equalName = (this->getName() == productToAdd.getName());
	bool equalPrice = (this->getPrice() == productToAdd.getPrice());
	bool equalCurrency = (this->getCurrency() == productToAdd.getCurrency());
	if (equalName && equalPrice && equalCurrency)
	{
		this->setAmount(this->getAmount() + productToAdd.getAmount());
	}
}

ostream& operator<<(ostream& os, Product& prod)
{
	os << prod.getName() << endl << prod.getPrice() << endl << prod.getAmount() << endl << prod.getCurrency();
	return os;
}
