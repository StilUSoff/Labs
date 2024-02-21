#pragma once
#include "Shape.h"
class Vector: public Shape
{
private:
	double x, y;	// Координаты вектора на плоскости
public:
	//========== Три конструктора
	Vector(double c1, double c2);
	Vector();							// Default
	Vector(double m) :Shape(this) { x = m; y = m; };
	Vector(const Vector& v);
	~Vector() { }
	//====== Переопределение операций =====//
	Vector& operator= (const Vector& v);	// Присвоение
	Vector operator+(const Vector& other);
	Vector& operator+= (const Vector& other);
	Vector& operator-= (const Vector& other);
	void Out();
	void OutTo();
	double get_x() const { return x; };
	double get_y() const { return y; };
	int operator!() const;
	bool operator>(const Vector& other);
	bool operator==(const Vector& other) const
	{
		if ((fabs(this->x - other.x) < DBL_EPSILON) and (fabs(this->y - other.y) < DBL_EPSILON)) {
			return true;
		}
		return false;
	}
	bool operator<(const Vector& other)
	{
		int e1 = sqrt(this->x * this->x + this->y * this->y);
		int e2 = sqrt(other.x * other.x + other.y * other.y);
		return e1 < e2 ? 1 : 0;
	}
	Vector operator*(const double ch);
	friend Vector operator*(const double ch, const Vector other);
	virtual void Move(Vector& v);
	virtual void Out() const;
	virtual double Area() { return 0; };
	bool pred() const { return ((x > 2 && y > 2) ? 1 : 0); };

};
 

