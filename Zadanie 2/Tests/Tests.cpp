#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include "../Invoice/product.h"
#include "../Invoice/Product.cpp"
#include "../Invoice/invoice.h"
#include "../Invoice/Invoice.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	TEST_CLASS(productTests)
	{
	public:

		TEST_METHOD(createValidProduct)
		{
			string name = "table";
			double price = 150;
			double amount = 2;
			string currency = "PLN";
			double value = 300;

			Product prod1("table", 150, 2, "PLN");

			Assert::AreEqual(prod1.getName(), name);
			Assert::AreEqual(prod1.getPrice(), price);
			Assert::AreEqual(prod1.getAmount(), amount);
			Assert::AreEqual(prod1.getCurrency(), currency);
			Assert::AreEqual(prod1.getValue(), value);

			price = 0;
			value = 0;
			Product prod2("table", 0, 2, "PLN");
			Assert::AreEqual(prod2.getPrice(), price);
			Assert::AreEqual(prod2.getAmount(), amount);
			Assert::AreEqual(prod2.getCurrency(), currency);
			Assert::AreEqual(prod2.getValue(), value);

			name = "cheese";
			price = 6.8;
			amount = 0.5;
			currency = "EUR";
			value = 3.4;

			Product prod3(name, price, amount, currency);

			Assert::AreEqual(prod3.getName(), name);
			Assert::AreEqual(prod3.getPrice(), price);
			Assert::AreEqual(prod3.getAmount(), amount);
			Assert::AreEqual(prod3.getCurrency(), currency);
			Assert::AreEqual(prod3.getValue(), value);
		}

		TEST_METHOD(createInvalidProduct)
		{
			string name = "table";
			double price = 150;
			double amount = 2;
			string currency = "PLN";
			double value = 300;

			try
			{
				price = -5;
				Product prod1(name, price, amount, currency);
				Assert::Fail();
			}
			catch (runtime_error)
			{
			}
			catch (...)
			{
				Assert::Fail();
			}

			try
			{
				price = 150;
				amount = 0;
				Product prod2(name, price, amount, currency);
				Assert::Fail();
			}
			catch (runtime_error)
			{
			}
			catch (...)
			{
				Assert::Fail();
			}

			try
			{
				amount = 0;
				currency = "CZK";
				Product prod3(name, price, amount, currency);
				Assert::Fail();
			}
			catch (runtime_error)
			{
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(changeProductAmountValid)
		{
			string name = "cheese";
			double price = 6.8;
			double amount = 0.5;
			string currency = "EUR";
			double value = 3.4;

			Product prod1(name, price, amount, currency);
			Assert::AreEqual(prod1.getAmount(), amount);
			Assert::AreEqual(prod1.getValue(), value);

			double newAmount = 1;
			double newValue = 6.8;
			prod1.setAmount(newAmount);
			Assert::AreEqual(prod1.getAmount(), newAmount);
			Assert::AreEqual(prod1.getValue(), newValue);

		}

		TEST_METHOD(changeProductAmountInvalid)
		{
			string name = "cheese";
			double price = 6.8;
			double amount = 0.5;
			string currency = "EUR";
			double value = 3.4;

			Product prod1(name, price, amount, currency);
			Assert::AreEqual(prod1.getAmount(), amount);
			Assert::AreEqual(prod1.getValue(), value);

			try
			{
				double newAmount = 0;
				prod1.setAmount(newAmount);
				Assert::Fail();
			}
			catch (runtime_error)
			{
				Assert::AreEqual(prod1.getAmount(), amount);
				Assert::AreEqual(prod1.getValue(), value);
			}
			catch (...)
			{
				Assert::Fail();
			}

		}

		TEST_METHOD(compareProductsEqual)
		{
			string name = "printer";
			double price = 120;
			double amount = 10;
			string currency = "USD";

			Product prod1(name, price, amount, currency);
			Product prod2(name, price, amount, currency);

			bool productsEqual = (prod1 == prod2);
			Assert::AreEqual(productsEqual, true);
		}

		TEST_METHOD(compareProductsNotEqual)
		{
			string name = "printer";
			double price = 120;
			double amount = 10;
			string currency = "USD";

			Product prod1(name, price, amount, currency);

			currency = "PLN";
			Product prod2(name, price, amount, currency);

			bool productsEqual = (prod1 == prod2);
			Assert::AreEqual(productsEqual, false);
		}

		TEST_METHOD(incrementIfSameGivenSame)
		{
			string name = "table";
			double price = 150;
			double amount = 2;
			string currency = "PLN";
			Product prod1(name, price, amount, currency);
			amount = 3;
			double value = 3 * 150;
			Product prod2(name, price, amount, currency);
			prod1 += prod2;
			double newAmount = 5;
			double newValue = 5 * 150;
			Assert::AreEqual(prod1.getAmount(), newAmount);
			Assert::AreEqual(prod2.getAmount(), amount);
			Assert::AreEqual(prod1.getValue(), newValue);
			Assert::AreEqual(prod2.getValue(), value);
		}

		TEST_METHOD(incrementIfSameGivenDifferent)
		{
			string name = "table";
			double price = 150;
			double amount = 2;
			string currency = "PLN";
			double value = 2 * 150;
			Product prod1(name, price, amount, currency);
			double differentPrice = 150.1;
			double differentValue = 2 * 150.1;
			Product prod2(name, differentPrice, amount, currency);
			prod1 += prod2;
			Assert::AreEqual(prod1.getAmount(), amount);
			Assert::AreEqual(prod2.getAmount(), amount);
			Assert::AreEqual(prod1.getValue(), value);
			Assert::AreEqual(prod2.getValue(), differentValue);
		}
	
	};

	TEST_CLASS(invoiceTests)
	{
	public:
		TEST_METHOD(createValidInvoiceEmpty)
		{
			string seller = "Firm A";
			string buyer = "Firm B";
			string issueDate = "2023-03-23";
			string issuePlace = "Warsaw";
			Invoice inv1(seller, buyer, issueDate, issuePlace);
			Assert::AreEqual(inv1.getSeller(), seller);
			Assert::AreEqual(inv1.getBuyer(), buyer);
			Assert::AreEqual(inv1.getIssueDate(), issueDate);
			Assert::AreEqual(inv1.getIssuePlace(), issuePlace);
			Assert::AreEqual(inv1.countItems(), 0);

			vector<Product> empty;
			vector<Product> items = inv1.getItems();
			bool itemsEqual = (items == empty);
			Assert::AreEqual(itemsEqual, true);
		}

		TEST_METHOD(createValidInvoiceNotEmpty)
		{
			string name = "printer";
			double price = 120;
			double amount = 10;
			string currency = "USD";
			Product prod1(name, price, amount, currency);
			name = "table";
			Product prod2(name, price, amount, currency);
			vector<Product> products;
			products.push_back(prod1);
			products.push_back(prod2);

			string seller = "Firm A";
			string buyer = "Firm B";
			string issueDate = "2023-03-23";
			string issuePlace = "Warsaw";
			Invoice inv1(seller, buyer, issueDate, issuePlace, products);
			Assert::AreEqual(inv1.getSeller(), seller);
			Assert::AreEqual(inv1.getBuyer(), buyer);
			Assert::AreEqual(inv1.getIssueDate(), issueDate);
			Assert::AreEqual(inv1.getIssuePlace(), issuePlace);
			Assert::AreEqual(inv1.countItems(), 2);

			vector<Product> items = inv1.getItems();
			bool itemsEqual = (items == products);
			Assert::AreEqual(itemsEqual, true);
		}

		TEST_METHOD(addItemToInvoice)
		{
			string name = "printer";
			double price = 120;
			double amount = 10;
			string currency = "USD";
			Product prod1(name, price, amount, currency);
			vector<Product> products;
			products.push_back(prod1);
			string seller = "Firm A";
			string buyer = "Firm B";
			string issueDate = "2023-03-23";
			string issuePlace = "Warsaw";
			Invoice inv1(seller, buyer, issueDate, issuePlace, products);
			Assert::AreEqual(inv1.countItems(), 1);
			vector<Product> items = inv1.getItems();
			bool itemsEqual = (items == products);
			Assert::AreEqual(itemsEqual, true);

			name = "table";
			Product prod2(name, price, amount, currency);
			inv1.addItem(prod2);
			Assert::AreEqual(inv1.countItems(), 2);
			products.push_back(prod2);
			items = inv1.getItems();
			itemsEqual = (items == products);
			Assert::AreEqual(itemsEqual, true);
		}

		TEST_METHOD(countTotalInvoiceValue)
		{
			string name = "TV"; double price = 250; double amount = 4; string currency = "PLN";
			Product prod1(name, price, amount, currency);
			name = "chair"; price = 100; amount = 2; currency = "USD";
			Product prod2(name, price, amount, currency);
			name = "pen"; price = 0.5; amount = 10; currency = "EUR";
			Product prod3(name, price, amount, currency);
			vector<Product> products = {prod1, prod2, prod3};
			string seller = "Firm A"; string buyer = "Firm B";
			string issueDate = "2022-05-01"; string issuePlace = "Cracow";
			Invoice inv1(seller, buyer, issueDate, issuePlace, products);

			double expectedTotalValue = 250.0*4.0 + 100.0*2.0*4.35 + 0.5*10.0*4.69;
			map<string, double> totalValue = inv1.countTotalValue();
			Assert::AreEqual(totalValue["PLN"], expectedTotalValue);
			Assert::AreEqual(totalValue["USD"], expectedTotalValue / 4.35);
			Assert::AreEqual(totalValue["EUR"], expectedTotalValue / 4.69);
		}

		TEST_METHOD(countTotalInvoiceValueEmpty)
		{
			string seller = "Firm A"; string buyer = "Firm B";
			string issueDate = "2022-05-01"; string issuePlace = "Cracow";
			Invoice inv1(seller, buyer, issueDate, issuePlace);

			double zero = 0;
			map<string, double> totalValue = inv1.countTotalValue();
			Assert::AreEqual(totalValue["PLN"], zero);
			Assert::AreEqual(totalValue["USD"], zero);
			Assert::AreEqual(totalValue["EUR"], zero);
		}

		TEST_METHOD(inputOutputItemsToFile)
		{
			string name = "TV"; double price = 250; double amount = 4; string currency = "PLN";
			Product prod1(name, price, amount, currency);
			name = "chair"; price = 100; amount = 2; currency = "USD";
			Product prod2(name, price, amount, currency);
			name = "pen"; price = 0.5; amount = 10; currency = "EUR";
			Product prod3(name, price, amount, currency);
			vector<Product> products = { prod1, prod2, prod3 };
			string seller = "Firm A"; string buyer = "Firm B";
			string issueDate = "2022-05-01"; string issuePlace = "Cracow";
			Invoice inv1(seller, buyer, issueDate, issuePlace, products);

			ofstream o_file("invData.txt");
			if (o_file.is_open())
			{
				o_file << inv1;
				o_file.close();
			}

			seller = "Firm C"; buyer = "Firm D";
			issueDate = "2022-06-01"; issuePlace = "Cracow";
			Invoice inv2(seller, buyer, issueDate, issuePlace);

			ifstream i_file("invData.txt");
			if (i_file.is_open()) {
				i_file >> inv2;
				i_file.close();
			}

			vector<Product> items1 = inv1.getItems();
			vector<Product> items2 = inv2.getItems();
			bool itemsEqual = (items1 == items2);
			Assert::AreEqual(itemsEqual, true);
		}
	};

}
