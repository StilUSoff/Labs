#include "Circle.h"
Circle::Circle(Circle& other) : Shape(this)
{
	*this = other;
}

Circle& Circle::operator= (const Circle& other)
{
	if (this != &other)
	{
		this->ptCntr = other.ptCntr;
		this->R = other.R;

	}
	return *this;
}

double Circle::Area()
{
	return (acos(-1.) * R * R);
}

 void Circle::Out() const
{
	std::cout << " Circle center" << ptCntr.get_x() << ", " << ptCntr.get_y() << ". << Radius = " << R;
}


 void Circle::Move(Vector& v)
 {
	 this->ptCntr += v;
 }