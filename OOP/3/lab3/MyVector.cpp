#include "stdafx.h"
#include "MyVector.h"


Vector::Vector(double c1, double c2): Shape() {
	// ++Count;
	x=c1;   y=c2;
}

Vector::Vector(): Shape() {
	// ++Count;
	x = y = 0.;
}

Vector::Vector(const Vector& other): Shape() {
	// ++Count;
	*this = other;
}

Vector::~Vector() {
	// --Count;
}

void Vector::Out() {
	cout << "\nVector:  x = " << x << ",  y = " << y;
}

// void Vector::PrintCount() {
// 	cout << "\n Now there are " << Count << " vectors";
// }

Vector& Vector::operator= (const Vector& v) {
	if (this == &v)
		return *this;
	x = v.x;
	y = v.y;
	return *this;
}

Vector Vector::operator+(const Vector& other) const {
	Vector tmp;
	tmp.x = this->x + other.x;
	tmp.y = this->y + other.y;
	return tmp;
}

double Vector::operator!() const {
	return sqrt(x*x+ y*y);
}

bool Vector::operator==(const Vector& other) const {
	double this_module = this->operator!();
	double other_module = other.operator!();
	return  (this_module - other_module < DBL_EPSILON) && (other_module - this_module < DBL_EPSILON);
}

bool Vector::operator>(const Vector& other) const {
	double this_module = this->operator!();
	double other_module = other.operator!();
	return this_module - other_module > DBL_EPSILON;
}

bool Vector::operator<(const Vector& other) const {
	double this_module = this->operator!();
	double other_module = other.operator!();
	return other_module - this_module > DBL_EPSILON;
}

// Покомпонентное сравнение
// bool Vector::operator==(const Vector& other) const {
// 	return  (this->x - other.x < DBL_EPSILON) && (other.x - this->x < DBL_EPSILON) && 
// 			(this->y - other.y < DBL_EPSILON) && (other.y - this->y < DBL_EPSILON);
// }


Vector Vector::operator*(double scalar) const {
	return Vector(scalar * x, scalar * y); 
}


Vector operator*(double scalar, const Vector& vector) {
    return Vector(scalar * vector.x, scalar * vector.y);
}

double Vector::operator*(const Vector& other) const {
	return x*other.x + y*other.y;
}