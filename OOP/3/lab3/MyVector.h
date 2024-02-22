#include "Shape.h"


class Vector: public Shape
{
	friend class Rect;
	friend class Circle;

private:
	double x, y;	// Координаты вектора на плоскости
	// static inline unsigned Count{};

public:
	Vector (double c1, double c2);
	Vector ();
	Vector(const Vector& other);

	~Vector();
	
	//====== Переопределение операций =====//
	Vector& operator= (const Vector& v);	// Присвоение

	Vector operator+(const Vector& other) const;

	Vector operator*(double scalar) const;
	double operator*(const Vector& other) const;
	friend Vector operator*(double scalar, const Vector& vector);

	double operator!() const;

	bool operator==(const Vector& other) const;
	bool operator>(const Vector& other) const;
	bool operator<(const Vector& other) const;

	void Out() override;
	void Move (Vector& v) override {};
	double Area() override {return 0;}; 

	// static void PrintCount();
};
