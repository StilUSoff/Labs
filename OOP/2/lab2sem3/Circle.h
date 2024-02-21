#pragma once
#include "Shape.h"
#include "MyVector.h"

class Circle : public Shape
{
private:
	Vector ptCntr;
	double R;
public:
	Circle():Shape(this), ptCntr(), R(0) {};
	Circle(const Vector i_ptCntr, const double i_R):Shape(this), ptCntr(i_ptCntr), R(i_R) {};
	Circle(const double i_x, const double i_y, const double i_R):Shape(this), ptCntr(i_x, i_y), R(i_R) {};
	Circle(Circle& other);
	Circle& operator= (const Circle& other);
	virtual void Move(Vector& v);
	virtual void Out() const;
	virtual double Area();
};
