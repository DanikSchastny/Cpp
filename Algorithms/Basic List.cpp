// ConsoleApplication21.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct Element
{
	int x;
	Element* pelement;
};

class List
{
private:
	Element* head;
public:
	void add(int value);
	void show();

	List() { head = nullptr;}
	~List();
};

List::~List()
{
	while (head != nullptr)
	{
		Element* temp = head->pelement;
		delete head;
		head = temp;
	}
}

void List::add(int value)
{
	Element* temp = new Element;
	temp->x = value;
	temp->pelement = head;
	head = temp;
}

void List::show()
{
	Element* temp = head;
	while (temp != nullptr)
	{
		std::cout << temp->x << std::endl;
		temp = temp->pelement;
	}
}

int main()
{
	List lst;
	int x;
	
	for (int i = 0; i <= 10; ++i)
	{
		std::cin >> x;
		lst.add(x);
	}

	lst.show();

	system("pause");
    return 0;
}

