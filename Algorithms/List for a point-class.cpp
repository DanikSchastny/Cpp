// List for Point-class.
//

#include "stdafx.h"

class Point 
{
private:
	int x, y;
	void setX(int x);
	void setY(int y);
public:
	Point() {}
	Point(int x, int y);
	~Point() {}

	inline void displayPoint();

	inline int getX();
	inline int getY();


	friend std::istream& operator>>(std::istream&, Point&);
	friend std::ostream& operator<< (std::ostream&, Point&);

	void operator =(Point&);
};
struct PointElement
{
	Point x;
	PointElement* next;
};

class PointList
{
private:
	PointElement* head;

public:
	void add(Point x);
	void show();
	~PointList();
	PointList() {};
};

PointList::~PointList()
{
	while (head != nullptr)
	{
		PointElement* temp = head->next;
		delete head;
		head = temp;
	}
}

void PointList::add(Point x)
{
	PointElement* temp = new PointElement;

	temp->x = x;
	temp->next = head;
	head = temp;

}

void PointList::show()
{
	PointElement* temp = head;

	while (temp != nullptr)
	{
		std::cout << temp->x;
		temp = temp->next;

	}
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

inline void Point::displayPoint()
{
	std::cout << "x: " << x << " y: " << y << std::endl;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

std::istream& operator >>(std::istream& input, Point& point)
{
	int x, y;
	input >> x >> y;

	point.setX(x);
	point.setY(y);

	return input;
}

std::ostream& operator <<(std::ostream& output, Point& point)
{
	output << point.x << "  " << point.y << std::endl;
	return output;
}

void Point::operator = ( Point& point)
{
	this->x = point.getX();
	this->y = point.getY();
}

inline int Point::getX()
{
	return this->x;
}

inline int Point::getY()
{
	return this->y;
}


int main()
{
	PointList lst;

	for (int i = 0; i < 5; ++i)
	{
		Point x;
		std::cin >> x;
		lst.add(x);
	}
	lst.show();
	
	system("pause");
    return 0;
}

