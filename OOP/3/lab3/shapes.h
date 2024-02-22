#include "MyVector.h"

class Rect: public Shape
{
private:
	Vector ptLT, ptRB;

public:
	Rect();
	Rect(Vector c1, Vector c2);
    Rect(double left, double top, double right, double bottom);
    Rect(const Rect& other);
	Rect& operator=(const Rect& other);

    void Inflate(double d = 1);
    void Inflate(double d_h, double d_v);
    void Inflate(double d_l, double d_t, double d_r, double d_b);

	void Out();
    void Move (Vector& v) override;
	double Area(); 
};


class Circle: public Shape
{
private:
	Vector ptCntr; 
    double R;

public:
    Circle(double x, double y, double r);

	void Out();
    void Move (Vector& v) override;
	double Area() override; 
};
