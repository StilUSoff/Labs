#include "MyVector.h"
#include "stdafx.h"
Vector::Vector(double c1, double c2) : Shape(this)
{
	x = c1;   y = c2;
}

Vector::Vector() : Shape(this)
{
	x = y = 0.;
}

Vector::Vector(const Vector& v) : Shape(this)
{
	*this = v;
}

void Vector::Out()
{
	cout << "\nVector:  x = " << x << ",  y = " << y;
}

void Vector::OutTo()
{
	cout << x << ", " << y;
}

//====== Переопределение операций =====//
Vector& Vector::operator= (const Vector& v)	// Присвоение
{
	if (this == &v) // проходит проверка, не сравниваем ли мы равные элементы. Если равны, то просто выводим. Если нет, то приравниваем и возвращаем
		return *this;
	x = v.x;
	y = v.y;
	return *this;
}

Vector Vector::operator+(const Vector& other)
{
	return Vector((this->x + other.x), (this->y + other.y));
}

Vector& Vector:: operator+= (const Vector& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector& Vector:: operator-= (const Vector& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

int Vector::operator!() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

bool Vector::operator>(const Vector& other)
{
	int e1 = sqrt(this->x * this->x + this->y * this->y);
	int e2 = sqrt(other.x * other.x + other.y * other.y);
	return e1 > e2 ? 1 : 0;
}




Vector Vector::operator*(const double ch)
{
	return Vector(this->x * ch, this->y * ch);
}

Vector operator*(const double ch, const Vector other)
{
	return Vector(other.x * ch, other.y * ch);
}

void Vector::Out() const
{
	cout << "\n";
}

void Vector::Move(Vector& v)
{
	*this += v;
}