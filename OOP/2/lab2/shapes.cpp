// private:
// 	Vector ptLT, ptLT;
#include "stdafx.h"
#include "shapes.h"


Rect::Rect(): Shape() {
    ptLT = Vector();
    ptRB = Vector();
}

Rect::Rect(Vector c1, Vector c2): Shape() {
    ptLT = c1;
    ptRB = c2;
}

Rect::Rect(double left, double top, double right, double bottom): Shape() {
    ptLT = Vector(left, top);
    ptRB = Vector(right, bottom);
}

Rect::Rect(const Rect& other): Shape() {
    *this = other;
}

Rect& Rect::operator=(const Rect& other) {
	if (this == &other)
		return *this;

	ptLT = other.ptLT;
	ptRB = other.ptRB;

	return *this;
}

void Rect::Inflate(double d) {
    ptLT.x -= d;
    ptLT.y += d;
    ptRB.x += d;
    ptRB.y -= d;
}

void Rect::Inflate(double d_h, double d_v) {
    ptLT.x -= d_h;
    ptLT.y += d_v;
    ptRB.x += d_h;
    ptRB.y -= d_v;
}

void Rect::Inflate(double d_l, double d_t, double d_r, double d_b) {
    ptLT.x -= d_l;
    ptLT.y += d_t;
    ptRB.x += d_r;
    ptRB.y -= d_b;
}

void Rect::Out() {
    cout << "\nRect (" << ptLT.x << "," << ptLT.y << "," << ptRB.x << "," << ptRB.y << ")";
}

void Rect::Move(Vector& v) {
    ptLT.x += v.x;
    ptLT.y += v.y;
    ptRB.x += v.x;
    ptRB.y += v.y;
};

double Rect::Area() {
    return abs((ptRB.x-ptLT.x) * (ptLT.y-ptRB.y));
}; 


Circle::Circle(double x, double y, double r): Shape() {
    ptCntr = Vector(x, y);
    R = r;
}

void Circle::Out() {
    cout << "\nCircle (" << ptCntr.x << "," << ptCntr.y << "," << R << ")";
}

void Circle::Move(Vector& v) {
    ptCntr.x += v.x;
    ptCntr.y += v.y;
};

double Circle::Area() {
    return 3.14 * R * R;
}; 