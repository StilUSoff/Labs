#include "Shape.h"
int Shape::Count = 0;


Shape* Shape::shapes[1000] = { nullptr };

void Shape::PrintCount() {
	cout << Count << "\n";
}
