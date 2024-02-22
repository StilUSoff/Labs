#pragma once
#include <cmath> 
#include <iostream>	 // Эта - часть библиотеки STL (Standard Template Library)
#include <limits>	 // Полезные константы
#include <cstring>
#include <intrin.h> // Для __nop
#include <cfloat>		
#include <vector>		
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <queue>
// #include <priority_queue>
#include <list>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <type_traits>

using namespace std;


template <typename T> 
void pr(T& v, string s)
{
	cout<<"\n\n"<<s<<"  # Sequence:\n";
	
	// Итератор любого контейнера
	typename T::iterator p;
	int i;

	for (p = v.begin(), i=0;  p != v.end();  p++, i++)
		cout << endl << i+1 <<". "<< *p;
	cout << '\n';
}


template <typename T>
void myPr(T& container, string s) {
	cout<<"\n\n"<<s<<"  # Сontainer:\n";
	int i = 0;

	while (!container.empty()) {
		cout << endl << ++i <<". ";

		if constexpr ((is_same<T, stack<typename T::value_type>>::value) || (is_same<T, priority_queue<typename T::value_type>>::value)) {
			cout << container.top();
		} 
		else if constexpr (is_same<T, queue<typename T::value_type>>::value) {
			cout << container.front();
		}

		container.pop();
	};
	cout << '\n';
}


template <typename T>
void printElement(const T& element) {
    std::cout << element << " ";
}

template <typename T, int d>
void changeElement(T& element) {
	element.x += d;
	element.y += d;
}


class CompareStr
{
public:
    bool operator() (const char* str1, const char* str2) {
        return strcmp(str1, str2);
    }
};
