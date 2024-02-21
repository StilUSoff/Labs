#pragma once
#include "MyVector.h"
#include "Shape.h"
class Rect : public Shape
{
private:
	Vector ptLT, ptRB;
public:
	Rect();
	Rect(/*const */Vector &LT, /*const*/ Vector &RB);
	Rect(int l, int t, int r, int b);
	~Rect() {};
	//Rect Inflate();
	Rect(Rect& other_Rect);
	/*Rect Inflate(double i);
	Rect Inflate(double LT, double RB);
	Rect Inflate(double l, double t, double r, double b);*/
	void Inflate(double i = 1);
	void Inflate(double LT, double RB);
	void Inflate(double l, double t, double r, double b);
	void Out();
	virtual void Move(Vector& v);
	virtual void Out() const;
	virtual double Area();
};