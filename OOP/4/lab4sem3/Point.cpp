#include "Point.h"

Point Point::operator+(const Point& other) {
	return Point((this->m_x + other.m_x), (this->m_y + other.m_y));
}

Point Point::operator+(const int num) {
	return this->operator+(Point(num, num)); // делаем как бы Point с этим числом и складываем по первому оператору +
}

Point operator+(const int num, const Point& point) {
	return Point(num, num) + point; //опять как бы складываем два Pointa
}

Point& Point::operator+=(const Point& other) {
	*this = *this + other;
	return *this;
}

Point& Point::operator+=(const int num) {
	this->operator+=(Point(num, num));
	return *this;
}

Point operator-(const Point& point, const int num)
{
	return point - Point(num, num);
}
Point operator-(const Point& point, const Point& other) {
	return Point((point.m_x - other.m_x), (point.m_y - other.m_y));
}

// в минусе без "трюков" как в плюсе, потому что глобальная
Point& operator-=(Point& point, const int num) {
	point = point - num;
	return point;
}

Point& operator-=(Point& point, const Point& other) {
	point = point - other;
	return point;
}

Point Point::operator+() const {
	return *this;
}

Point Point::operator-() const {
	return Point(-this->m_x, -this->m_y);
}

