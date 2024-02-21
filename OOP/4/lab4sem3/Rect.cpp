#include "Rect.h"
#include "stdafx.h"
#include <iostream>
Rect::Rect() : Shape(this), ptLT(), ptRB() {}

Rect::Rect(/*const Vector LT, const Vector RB*//*const */Vector& LT, /*const*/ Vector& RB) :Shape(this), ptLT(LT), ptRB(RB) {}


Rect::Rect(int l, int t, int r, int b) :Shape(this), ptLT(l, t), ptRB(r, b) {}

//Rect Rect::Inflate()
//{
//	return Inflate(1);
//}

Rect::Rect(const Rect& other_Rect) : Shape(this)
{
	*this = other_Rect;
}


void Rect::Inflate(double i_size)
{
	this->Inflate(i_size, i_size, i_size, i_size);
}

void Rect::Inflate(double i_x, double i_y)
{
	this->Inflate(i_x, i_y, i_x, i_y);
}

void Rect::Inflate(double l, double t, double r, double b)
{
	Vector sm1(l, t);
	Vector sm2(l, t);
	this->ptLT += sm1;
	this->ptRB += sm2;
}
void Rect::Out()
{
	std::cout << "Rect(";
	ptLT.OutTo();
	std::cout << ", ";
	ptRB.OutTo();
	std::cout << ") \n";
}

void Rect::Out() const
{
	cout << "\nRect (" << this->ptLT.get_x() << ", " << this->ptLT.get_y() << ", "
		<< this->ptRB.get_x() << ", " << this->ptRB.get_y() << ")";
}

void Rect::Move(Vector& v)
{
	this->ptLT += v;
	this->ptRB += v;
}

double Rect::Area()
{
	return ((this->ptRB.get_x() - this->ptLT.get_x()) * (this->ptLT.get_y() - this->ptRB.get_y()));
}