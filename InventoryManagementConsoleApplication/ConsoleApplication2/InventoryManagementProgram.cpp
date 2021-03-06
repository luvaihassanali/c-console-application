#include "stdafx.h"
#include "vld.h"
#include "dLinkedList.h"
#include <sstream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void initStock(dLinkedList *l);
void initMainMenu(dLinkedList *l);
void initCustomerMenu(dLinkedList *l);
void initMgmtMenu(dLinkedList *l);
void initBuyingMenu(dLinkedList *l);
void removeProduct(dLinkedList *l);
void addProduct(dLinkedList *l);
void increaseStock(dLinkedList *l);
double totalPrice = 0;
double tempPrice = 0;
int numPurchases = 0;
std::string purchaseString = "";


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	dLinkedList *list = new dLinkedList();
	initStock(list);
	initMainMenu(list);
	delete list;
    return 0;
}

void initMainMenu(dLinkedList *l)
{
	std::cout << "\n - - - - - - - - - - - - - - - - - - - - - - - - - \n";
	std::cout << "|         INVENTORY MANANGEMENT APPLICATION       |\n";
	std::cout << " - - - - - - - - - - - - - - - - - - - - - - - - - \n";
	std::cout << "\n 1. Customer options\n 2. Management Options\n 3. Exit\n\n";
	int choice;
	do {
		std::cout << " Enter choice: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (choice != 1 && choice != 2 && choice != 3);
	std::cout << "Choice: " + std::to_string(choice);
	switch (choice)
	{
	case 1: initCustomerMenu(l);
		break;
	case 2: initMgmtMenu(l);
		break;
	case 3: break;
	}
}

void initCustomerMenu(dLinkedList *l) 
{
	std::cout << "\n - - - - - - - - - - - - - - - \n";
	std::cout << "|         CUSTOMER MENU       |\n";
	std::cout << " - - - - - - - - - - - - - - - \n";
	std::cout << "\n 1. Go shopping\n 2. Back to main menu\n\n";
	int choice;
	do {
		std::cout << " Enter choice: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (choice != 1 && choice != 2);
	switch (choice) 
	{
	case 1:	l->printProducts(l->getHead());
		std::cout << "\n Enter corresponding number for product you wish to buy\n Enter 0 to finish\n";
		totalPrice = 0;
		tempPrice = 0;
		numPurchases = 0;
		purchaseString = "";
		initBuyingMenu(l);
		break;
	case 2: initMainMenu(l);
		break;
	}
}

void initBuyingMenu(dLinkedList *list)
{

	int choice;

	do {
		std::cout << " Enter choice: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (-1 >= choice || choice > list->size);
	if (choice == 0) {
		if (numPurchases == 0) 
		{
			std::cout << " Thank you for browsing\n";
		}
		else 
		{
			std::stringstream ss;
			ss << totalPrice;
			std::cout << " You bought " + std::to_string(numPurchases) + " items today:\n" + purchaseString + " You've spent a total of $" + ss.str() + "\n";
		}
		std::cout << " Returning to customer menu\n";
		initCustomerMenu(list);
	}
	else {
		Node* temp = list->getHead();
		for (int i = 0; i<choice-1; i++) 
		{
			temp = temp->next;
		}
		
		Product *p = temp->getData();
		std::cout << " " + p->getName();
		std::cout << "\n Enter quantity: ";
		int quantity;
		bool rightQuantity = false;
		std::cin >> quantity;
		while (!rightQuantity)
		{
			if (quantity > p->getCount())
			{
				std::cout << " Not enough stock - enter different amount: ";
				std::cin >> quantity;
			}
			else {
				rightQuantity = true;
			}
		}
		p->decCount(quantity);
		numPurchases += quantity;
		std::stringstream ss;
		double x = p->getPrice()*quantity;
		ss << x;
		totalPrice += x;
		purchaseString += " " + p->getName() + " $" + ss.str() + " " + std::to_string(quantity) + "\n";
		temp = nullptr;
		p = nullptr;
		initBuyingMenu(list);
	}


}
void initMgmtMenu(dLinkedList *l)
{
	std::cout << "\n - - - - - - - - - - - - - - - - \n";
	std::cout << "|         MANAGEMENT MENU       |\n";
	std::cout << " - - - - - - - - - - - - - - - - \n";
	std::cout << "\n 1. Add product\n 2. Remove product\n 3. Increase stock\n 4. List products\n 5. List suppliers\n 6. Return to main menu\n\n";
	int choice;
	do {
		std::cout << " Enter choice: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (-1 >= choice || choice >= 7);
	switch (choice) {
	case 1: addProduct(l);
		initMgmtMenu(l);
		break;
	case 2: removeProduct(l);
		initMgmtMenu(l);
		break;
	case 3: increaseStock(l);
		initMgmtMenu(l);
		break;
	case 4: l->printProducts(l->getHead());
		initMgmtMenu(l);
		break;
	case 5: l->printSuppliers(l->getHead());
		initMgmtMenu(l);
		break;
	case 6: initMainMenu(l);
		break;
	}
}

void addProduct(dLinkedList *l) 
{
	std::string name;
	std::string address = "";
	std::string phone_number = "";
	std::cout << " Adding new product\n Enter supplier name: ";
	getline(std::cin, name);
	std::cout << " Enter address: ";
	getline(std::cin, address);
	std::cout << " Enter phone number: ";
	getline(std::cin, phone_number);
	Supplier *s = new Supplier(name, address, phone_number);
	double price = 0;
	int count = 0;
	int expiry = 0;
	std::string pname = "";
	std::cout << " Enter product name: ";
	getline(std::cin, pname);
	std::cout << " Enter price (ex. 13.42): ";
	std::cin >> price;
	std::cout << " Enter days till expiry - if perishable enter 999: ";
	std::cin >> expiry;
	std::cout << " Enter amount of stock: ";
	std::cin >> count;
	if (count == 999) {
		NonPerishable *nonperishable = new NonPerishable(name, price, s, count);
		l->addNode(nonperishable);
	}
	else {
		Perishable *perishable = new Perishable(name, price, s, count, expiry);
		l->addNode(perishable);
	}
	std::cout << " \nProduct added succesfully\n";
}
void removeProduct(dLinkedList * l)
{
	std::string name;
	std::cout << " Enter product name to delete: ";
	std::cin >> name;
	l->deleteProduct(name, l->getHead());
}

void increaseStock(dLinkedList * l)
{
	std::string name = "";
	int count = 0;
	std::cout << " Enter product name to increase stock: ";
	std::cin >> name;
	std::cout << " Enter amount of stock ordered: ";
	std::cin >> count;
	bool inc = l->increaseStock(l->getHead(), name, count);
	if (inc == false)
	{
		std::cout << "\n Product not found, try again\n";
		increaseStock(l);
	}
	else
	{
		std::cout << " Product stock increased succesfully\n";
	}
}
void initStock(dLinkedList* list) {
	Supplier *s1 = new Supplier("Natrel", "51 Broadway Drive", "6138606052");
	Supplier *s2 = new Supplier("General Mills", "54 Farmway St", "3432155858");
	Supplier *s3 = new Supplier("Fresh Farm", "2 OToole Lane", "6134243921");
	Supplier *s4 = new Supplier("Fresh Farm", "2 OToole Lane", "6134243921");
	Supplier *s5 = new Supplier("Fresh Farm", "2 OToole Lane", "6134243921");
	Supplier *s6 = new Supplier("Campbells Soup", "34 Industrial", "4243562233");
	Supplier *s7 = new Supplier("Planters", "5433 Grand Avenue", "3439136666");
	Supplier *s8 = new Supplier("Planters", "5433 Grand Avenue", "3439136666");
	Supplier *s9 = new Supplier("Natrel", "51 Broadway Drive", "6138606052");
	Supplier *s10 = new Supplier("General Mills", "54 Farmway St", "3432155858");
	Perishable *p1 = new Perishable("Milk", 4.24, s1, 8, 30);
	NonPerishable *p2 = new NonPerishable("Cornflakes Cereal", 3.99, s2, 10);
	Perishable *p3 = new Perishable("Strawberries", 2.99, s3, 2, 22);
	Perishable *p4 = new Perishable("Blueberries", 2.99, s4, 9, 22);
	Perishable *p5 = new Perishable("Blackberries", 2.99, s5, 10, 22);
	NonPerishable *p6 = new NonPerishable("Tomato Soup", 0.99, s6, 2);
	NonPerishable *p7 = new NonPerishable("Cashew Nuts", 5.67, s7, 7);
	NonPerishable *p8 = new NonPerishable("Almonds", 3.88, s8, 5);
	Perishable *p9 = new Perishable("Fancy Cheese", 7.99, s9, 3, 60);
	NonPerishable *p10 = new NonPerishable("Peanut Butter", 3.49, s10, 12);
	list->addNode(p1);
	list->addNode(p2);
	list->addNode(p3);
	list->addNode(p4);
	list->addNode(p5);
	list->addNode(p6);
	list->addNode(p7);
	list->addNode(p8);
	list->addNode(p9);
	list->addNode(p10);
}