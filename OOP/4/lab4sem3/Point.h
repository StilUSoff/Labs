#pragma once
#include "MyVector.h"
class Point
{
	int m_x;
	int m_y;
public:
	Point() { m_x = 0; m_y = 0; }
	Point(int x, int y) {
		m_x = x; m_y = y;
	}
	Point(Vector v) { m_x = v.get_x(); m_y = v.get_y(); }
	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; };
	int get_x() const { return m_x; }
	int get_y() const { return m_y; };

	friend Point& operator-=(Point& point, const int num);
	friend Point& operator-=(Point& point, const Point& other);
	Point& operator +=(const Point& other);
	bool operator!=(const Point& other) {

	}
	Point& operator +=(const int num);

	Point operator+(const Point& other);
	Point operator+(const int num);
	friend Point operator+(const int num, const Point& point);
	Point operator+() const;
	Point operator-() const;

	friend Point operator-(const Point& point, const int num);
	friend Point operator-(const Point& point, const Point& other);


	friend bool operator<(const Point& point1, const Point& point2) {
		return (point1.m_x < point2.m_x && point1.m_y < point2.m_y);
	}

	friend bool operator>(const Point& point1, const Point& point2) {
		return (point1.m_x > point2.m_x && point1.m_y > point2.m_y);
	}

	friend bool operator==(const Point& point1, const Point& point2) {
		return (point1.m_x == point2.m_x && point1.m_y == point2.m_y);
	}
	friend ostream& operator<<(ostream&, const Point& c)
	{
		cout << c.m_x << " " << c.m_y << "\n";
		return cout;
	}

};
