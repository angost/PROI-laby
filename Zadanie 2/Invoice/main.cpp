//Author: Angelika Ostrowska

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "product.h"
#include "invoice.h"
using namespace std;

int main(int argc, char *argv[])
{
	string seller = "Firm A"; string buyer = "Firm B";
	string issueDate = "2022-05-01"; string issuePlace = "Cracow";
	Invoice inv1(seller, buyer, issueDate, issuePlace);
	if (argc == 2)
	{
		ifstream i_file(argv[1]);
		if (i_file.is_open())
		{	
			try
			{
				i_file >> inv1;
				if (inv1.countItems() == 0)
					throw runtime_error("");
				i_file.close();
				cout << "Created invoice using data from file" << endl;
			}
		catch (...)
			{
				i_file.close();
				cout << "Corrupted data" << endl;
				return 1;
			}
		}
	}
	else
	{
		Product standardProduct1("paper", 0.1, 250, "PLN");
		Product standardProduct2("pen", 0.5, 100, "EUR");
		Product standardProduct3("paperclip", 0.3, 50, "USD");
		vector<Product> products = { standardProduct1, standardProduct2, standardProduct3 };
		inv1.addItem(products);
		cout << "Created invoice using standard products" << endl;
	}
	

	cout << endl << "Invoice data:" << endl << inv1;
	cout << endl << "Total invoice value:" << endl;
	map<string, double> totalValue = inv1.countTotalValue();
	for (const auto& pair : totalValue)
	{
		cout << pair.first << ": " << pair.second << endl;
	}

	ofstream o_file("newInvoice.txt");
	if (o_file.is_open())
	{
		o_file << inv1;
		o_file.close();
		cout << endl << "Saved invoice to file" << endl;
	}

	return 0;
}


