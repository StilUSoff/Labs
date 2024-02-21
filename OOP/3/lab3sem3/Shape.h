#pragma once
#include "stdafx.h"
class Vector;
class Shape
{
private:
	int x;
	static int Count;
public:
	static Shape* shapes[1000];
	Shape(Shape* ch) {
		if (Count <= 999) shapes[Count] = ch;
		Count++;
	};
	~Shape(){ Count--;}
	static void PrintCount();
	virtual void Move(Vector& v) = 0;
	virtual void Out() const = 0;
	virtual double Area() = 0;
	static int GetCount() {return Count;}

};


