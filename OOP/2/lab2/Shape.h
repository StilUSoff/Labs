#include "stdafx.h"

class Vector;

class Shape
{
	int x;
private:
    static inline unsigned Count{};

public:
	const static inline unsigned size = 1000;
	static inline Shape* shapes[size];

	static unsigned GetCount(){return Count;};
	
	Shape() {
		shapes[Count] = this;
		++Count;
	};

	~Shape() {
        for (int i = 0; i < size; i++) {
            if (shapes[i] == this) {
                for (int j = i; j < size-1; j++) {
                    shapes[j] = shapes[j + 1];
                }
				shapes[size-1] = nullptr;
            };
        };
		--Count;
	};

	static void PrintCount() {
		cout << "\n Now there are " << Count << " shapes";
	};

    virtual void Move (Vector& v) = 0;
	virtual void Out() = 0;
	virtual double Area() = 0; 
};
