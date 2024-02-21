//=======================================================================
//	Лабораторная №3. Шаблоны функций. Шаблоны классов. Стандартные шаблоны С++.
//				Обработка исключений.
//=======================================================================
//Используйте недостающие файлы из лабораторной 2
#include "stdafx.h"
#include "MyVector.h"
#include "MyString.h"
#include <stdexcept>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "MyVector.h"
using namespace std;


//============= Шаблон функции для вывода с помощью итератора
template <class T> void pr(T& v, string s)
{
	cout << "\n\n\t" << s << "  # Sequence:\n";

	// Итератор любого контейнера
	typename T::iterator p;
	int i;

	for (p = v.begin(), i = 0; p != v.end(); p++, i++)
		cout << endl << i + 1 << ". " << *p;
	cout << '\n';
}

template <typename S> void Swap(S a, S b) {
	S c = a;
	a = b;
	b = a;
}

class StackOverflow : public std::exception {
public:
	virtual const char* what() {
		return "Stack overflow\n";
	}
};

class StackUnderflow : public std::exception {
public:
	virtual const char* what() {
		return "Stack under flow\n";
	}
};

class StackOutOfRange : public std::exception {
public:
	virtual void Out() {
		std::cout << "\n Stack Out Of Range" << "\n";
	}


};

template <class T, int max_size> class MyStack
{
	T m_ar[max_size];
	int size;
public:
	MyStack() {
		for (int i = 0; i < max_size; i++) { m_ar[i] = 0; }
		size = 0; }
	int GetSize() { return size; }
	int Capacity() { return (max_size - size); }
	void Push(T m) { if (size >= max_size - 1) throw StackOverflow();  m_ar[size] = m; size++;}
	T Pop() { if (size = 0) throw StackUnderflow(); T vr = m_ar[size]; size--; return vr; }
	T operator[](int ind) { if (size < 0 || ind > size) {throw StackOutOfRange();} return m_ar[ind]; }
};





int main()
{

	//===========================================================
	// Шаблоны функций
	//===========================================================
	// Создайте шаблон функции перестановки двух параметров - Swap().
	// Проверьте работоспособность созданного шаблона с помощью
	// приведенного ниже фрагмента.
	{
		int i = 1, j = -1;
			Swap (i, j);

		double a = 0.5, b = -5.5;
			Swap (a, b);

		Vector u(1, 2), w(-3, -4);
			Swap(u, w);

				// Если вы достаточно развили класс MyString в предыдущей работе,
				// то следующий фрагмент тоже должен работать корректно.

		MyString s1("Your fault"), s2("My forgiveness");
		Swap(s1, s2);
	}
	//===========================================================
	// Шаблоны классов
	//===========================================================
	// Создайте шаблон класса MyStack для хранения элементов любого типа T.
	// В качестве основы для стека может быть выбран массив.
	// Для задания максимального размера стека может быть использован
	// параметр-константа шаблона
	// Обязательными операциями со стеком являются "Push" и "Pop","GetSize" и "Capacity"
	// Необязательной - может быть выбор по индексу (operator[]).
	// Для того, чтобы гарантировать корректное выполнение этих операций 
	// следует генерировать исключительные ситуации.

	// С помощью шаблона MyStack создайте стек переменных типа int, затем
	// стек переменных типа double и, наконец, стек из переменных типа Vector 
	// Если вы подготовите три класса для обработки исключений,
	// то следующий фрагмент должен работать
	try
	{
		cout << "\tTest MyStack\n";
		MyStack <int, 3> stack;

		cout << "\nInteger Stack capacity: " << stack.Capacity();

		stack.Push(1);
		stack.Push(2);
		stack.Push(3);

		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";

				stack.Push(4);	// Здесь должно быть "выброшено" исключение

		cout << "\nInteger Stack pops: " << stack.Pop();
		cout << "\nInteger Stack pops: " << stack.Pop();

		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";
		stack.Pop();
				stack.Pop();		// Здесь должно быть "выброшено" исключение
		stack.Push(2);

		// int i = stack[3];	// Здесь должно быть "выброшено" исключение

		MyStack<Vector, 5> ptStack;

		cout << "\nVector Stack capacity: " << ptStack.Capacity();

		ptStack.Push(Vector(1, 1));
		ptStack.Push(Vector(2, 2));

		cout << "\nVector Stack pops: ";
		// Используйте метод класса Vector для вывода элемента
		ptStack.Pop().Out();

		cout << "\nVector Stack has: " << ptStack.GetSize() << " elements";
	}
	catch (StackOverflow)
	{
		cout << "\nStack overflow";
	}
	catch (StackUnderflow)
	{
		cout << "\nStack underflow";
	}
	catch (StackOutOfRange o)
	{
		o.Out();
	}

	stop;

	//=======================================================================
	// Контейнеры стандартной библиотеки. Последовательности типа vector
	//=======================================================================

	// Создайте пустой вектор целых чисел. Узнайте его размер с помощью метода size(),
	// С помощью метода push_back() заполните вектор какими-либо значениями.
	// Получите новый размер вектора и выведите значения его элементов.
	// В процессе работы с вектором вы можете кроме количества реально заполненных
	// элементов (size()) узнать максимально возможное количество элементов (max_size()),
	// а также зарезервированную память (capacity()).

	vector<int> v;
	int n = v.size();
	v.push_back(-1);
	v.push_back(-2);
	n = v.size();
	n = v.capacity();
	n = v.max_size();

	// Так как мы часто будем выводить последовательности, то целесообразно
	// создать шаблон функции для вывода любого контейнера.
	// Проанализируйте коды такого шабдлона (pr), который приведен выше
	// Используйте его для вывода вашего вектора

	pr(v, "Vector of ints");

	// Используем другой конструктор для создания вектора вещественных
	// с начальным размером в 2 элемента и заполнением (222.).
	// Проверим параметры вектора. Затем изменим размер вектора и его заполнение
	// (метод - resize()) и вновь проверим параметры.

	vector<double> vd(2, 222.);
	pr(vd, "Vector of doubles");
	n = vd.size(); //2
	n = vd.capacity(); //2
	n = vd.max_size(); //536870911

	vd.resize(5, 555.);
	pr(vd, "After resize");
	n = vd.size(); //2
	n = vd.capacity(); //2
	n = vd.max_size(); //536870911
	stop;
	//// Используя метод at(), а также операцию выбора [], измените значения
	//// некоторых элементов вектора и проверьте результат.
	vd.at(2) = 7.;
	vd[1] = 5.;
	pr(vd, "After at");

	//// Создайте вектор вещественных, который является копией существующего.
	vector<double> wd = vd;
	pr(wd, "Copy");

	//// Создайте вектор, который копирует часть существующей последовательности
	vector<double> ud(vd.begin() + 1, vd.begin() + 4);
	pr(ud, "Copy part");

	//// Создайте вектор вещественных, который является копией части обычного массива.
	double ar[] = { 0., 1., 2., 3., 4., 5. };

	vector<double> va(ar, ar + 3);
	pr(va, "Copy part of array");

	//// Создайте вектор символов, который является копией части обычной строки
	char s[] = "Array is a succession of chars";

	vector<char> vc(s + 3, s + 7);
	pr(vc, "Copy part of c-style string");

	//// Создайте вектор элементов типа Vector и инициализируйте
	//// его вектором с координатами (1,1).
	vector<Vector> vv(1, Vector(1, 1));

	cout << "\n\nvector of Vectors\n";
	for (int i = 0; i < vv.size(); i++)
		vv[i].Out();

	//// Создайте вектор указателей на Vector и инициализируйте его адресами
	//// объектов класса Vector

	vector<Vector*> vp(1, new Vector(1, 1));
	vp.push_back(new Vector(2, 2));

	cout << "\n\nvector of pointers to Vector\n";

	for (int i = 0; i < vp.size(); i++)
		vp[i]->Out();

	//// Научитесь пользоваться методом assign и операцией
	//// присваивания = для контейнеров типа vector.
	vp.assign(6, new Vector(6, 6));

	cout << "\n\nAfter assign\n";
	for (int i = 0; i < vp.size(); i++)
		vp[i]->Out();

	//// Декларируйте новый вектор указателей на Vector и инициализируйте его 
	//// с помощью второй версии assign
	vector<Vector*> vpNew;
	vpNew.assign(vp.begin(), vp.end() - 1);

	cout << "\n\nNew vector after assign\n";
	for (int i = 0; i < vpNew.size(); i++)
		vpNew[i]->Out();


	//// На базе шаблона vector создание двухмерный массив и
	//// заполните его значениями разными способами.
	//// Первый вариант - прямоугольная матрица
	//// Второй вариант - ступенчатая матрица


	////========= Ступенчатая матрица
	vector <vector<double> > vdd;
	for (int i = 0; i < 5; i++) {
		vdd.push_back(vector<double>(5));
		for (int j = 0; j < vdd.size(); j++) {
			vdd[i][j] = double(i+j);
		}
	}

	cout << "\n\n\tTest vector of vector<double>\n";
	for (int i = 0; i < vdd.size(); i++)
	{
		cout << endl;
		for (int j = 0; j < vdd[i].size(); j++)
			cout << vdd[i][j] << "  ";
	}


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < vdd.size(); j++) {
			vdd[i] = vector<double>(5, 0);
		}
	}

	for (unsigned int i = 1; i < vdd.size(); i++)
		for (int j = 0; j <= i; j++) {
			vdd[i][j] = i;
		}

	cout << "\n\n\tTest vector of vector<double>\n";
	for (unsigned int i = 1; i < vdd.size(); i++)
	{
		cout << endl;
		for (unsigned int j = 0; j < vdd[i].size(); j++)
			cout << vdd[i][j] << "  ";
	}

	//===================================
	// Простейшие действия с контейнерами
	//===================================
	//3б. Получение значения первого и последнего элементов последовательности.
	//Получение размера последовательности. Присваивание значений
	//элементов одной последовательности элементам другой - assign().

	//Создайте и проинициализируйте вектор из элементов char. Размер -
	//по желанию.
	vector<char> Ch1;
	for (int i = 0; i < 10; i++)
		Ch1.push_back(65 + i);
	//Создайте и проинициализируйте массив из элементов char. Размер -
	//по желанию.
	char M[] = { 'L', '$', '.', '-', '+', 'K', '*'};
	//Получите значение первого элемента вектора ( front() )
	cout << "\nChar front = " << Ch1.front();
	//Получите значение последнего элемента вектора ( back() )
	cout << "\nChar back = " << Ch1.back();
	//Получите размер вектора
	cout << "\nChar size = " << Ch1.size();
	//Присвойте вектору любой диапазон из значений массива cMas.
	Ch1.assign(M, M + 5);
	//Проверьте размер вектора, первый и последний элементы.
	cout << "\nnew Char front = " << Ch1.front();
	//Получите значение последнего элемента вектора ( back() )
	cout << "\nnew Char back = " << Ch1.back();
	//Получите размер вектора
	cout << "\nnew Char size = " << Ch1.size();
//
//stop;


	//3в. Доступ к произвольным элементам вектора с проверкой - at()
	//и без проверки - []
	//Создайте неинициализированный вектор из 8 элементов char - vChar2.
	//С помощью at() присвойте четным элементам вектора значения
	//элементов vChar1 из предыдущего задания,
	//а с помощью [] присвойте нечетным элементам вектора vChar2 значения
	//массива {'K','U','K','U'}.
	vector<char> Ch2(8);
	char M2[] = { 'K','U','K','U' };

	for (int i = 1; i < Ch2.size(); i += 2) 
		Ch2.at(i) = Ch1.at(i/2);

	for (int i = 0; i < Ch2.size(); i += 2) 
		Ch2[i] = M2[i/2];


stop;
	
try {
	//Попробуйте "выйти" за границы вектора с помощью at() и
	//с помощью []. Обратите внимание: что происходит при
	//попытке обращения к несуществующему элементу в обоих случаях

	char Ch = Ch2.at(100); //exception std::out_of_range
	//char Ch = Ch2[100]; //debug assertion failed: vector subscript out of range
}
catch (std::out_of_range)
{
}

	//3г.Добавьте в конец вектора vChar2  - букву Z (push_back()). Для
	//расширения кругозора можете ее сразу же и выкинуть (pop_back())
	Ch2.push_back('Z');
	Ch2.pop_back();

	stop;

	//
	//	//3д. Вставка-удаление элемента последовательности insert() - erase()
	//	//Очистка последовательности - clear()





		//Вставьте перед каждым элементом вектора vChar2 букву 'W'
	for (int i = 0; i < Ch2.size(); i += 2)
		Ch2.insert(Ch2.begin() + i, 'W');

	//Вставьте перед 5-ым элементом вектора vChar2 3 буквы 'X'

	Ch2.insert(Ch2.begin() + 4, 3, 'X');

	//Вставьте перед 2-ым элементом вектора vChar2 с третьего по
	//шестой элементы массива "aaabbbccc"
	char M3[] = "aaabbbccc";
	Ch2.insert(Ch2.begin() + 1, M3 + 2, M3 + 6);

	//Сотрите c первого по десятый элементы vChar2
	Ch2.erase(Ch2.begin(), Ch2.begin() + 10);

	stop;

	//Уничтожьте все элементы последовательности - clear()
	Ch2.clear();
	stop;

	//Создание двухмерного массива
	//5x10 2
	vector <vector<char>> Mass(5, vector<char>(10, 2));
	stop;

	///////////////////////////////////////////////////////////////////
	
		//Задание 4. Списки. Операции, характерные для списков.
		//Создайте два пустых списка из элементов Vector - ptList1 и
		//ptList2
		list<Vector> ptList1, ptList2;
		//Наполните оба списка значениями с помощью методов push_back(),
		//push_front, insrert()
		for (int i = 0; i < 10; i++) 
			ptList1.push_back(Vector(i, i * i));
		for (int i = 0; i < 10; i++) 
			ptList1.push_front(Vector((i + 5) * 2, (3* i) + 5));
		ptList1.insert(ptList1.begin(), Vector(6, 66));
		///////
		for (int i = 0; i < 5; i++) 
			ptList2.push_back(Vector(2 * i, i * i * 2));
		for (int i = 0; i < 5; i++) 
			ptList2.push_front(Vector((i + 2) * 2, (i * 2) + 2));
		ptList2.insert(ptList2.end(), Vector(7, 777));
		//Отсортируйте списки - sort().
		//Подсказка: для того, чтобы работала сортировка, в классе Vector
		//должен быть переопределен оператор "<"
		ptList1.sort(); ptList2.sort();
		stop;

		//Объедините отсортированные списки - merge(). Посмотрите: что
		//при этом происходит со вторым списком.

		ptList1.merge(ptList2); //второй список обнулился 
		stop;

		//Исключение элемента из списка - remove()
		//Исключите из списка элемент с определенным значением.
		//Подсказка: для этого необходимо также переопределить
		//в классе Vector оператор "=="
		ptList1.remove(Vector(7, 777));

		stop;
	
	///////////////////////////////////////////////////////////////////
	
		//Задание 5. Стандартные алгоритмы.Подключите заголовочный файл
		// <algorithm>
		//5а. Выведите на экран элементы ptList1 из предыдущего
		//задания с помощью алгоритма for_each()
		for_each(ptList1.begin(), ptList1.end(), [](Vector& v) { v.Out(); });

		stop;

		//5б.С помощью алгоритма find() найдите итератор на элемент Vector с
		//определенным значением. С помощью алгоритма find_if() найдите
		//итератор на элемент, удовлетворяющий определенному условию,
		//например, обе координаты точки должны быть больше 2.
		//Подсказка: напишите функцию-предикат, которая проверяет условие
		//и возвращает boolean-значение (предикат может быть как глобальной
		//функцией, так и методом класса)

		auto t = find(ptList1.begin(), ptList1.end(), Vector(9, 81));

		t = find_if(ptList1.begin(), ptList1.end(), [](Vector& v) {return v.pred(); });

		  stop;

		//Создайте список из указателей на элеметы Vector. С помощью
		//алгоритма find_if() и предиката (можно использовать предикат -
		//метод класса Vector, определенный в предыдущем задании) найдите в
		//последовательности элемент, удовлетворяющий условию

		  list<Vector*> Ukaz;
		  for (int i = 0; i <10; i++) Ukaz.push_back(new Vector(i*2*3+5));

		  auto it2 = find_if(Ukaz.begin(), Ukaz.end(), [](Vector* v) {return v->pred(); });


		  stop;

		//5в. Создайте список элементов Vector. Наполните список
		//значениями. С помощью алгоритма replace() замените элемент
		//с определенным значением новым значением. С помощью алгоритма
		//replace_if() замените элемент, удовлетворяющий какому-либо
		//условию на определенное значение. Подсказка: условие
		//задается предикатом.
		  list <Vector> list2;
		  for (int i = 0; i < 10; i++) list2.push_back(Vector(i, i*2));

		  replace(list2.begin(), list2.end(), Vector(0, 0), Vector(5, 1));

		  replace_if(list2.begin(), list2.end(), [](Vector v) {return v > 2; }, Vector(5, 1));
	  //Сформировали значения элементов списка


		stop;


		//5г. Создайте вектор строк (string). С помощью алгоритма count()
		//сосчитайте количество одинаковых строк. С помощью алгоритма
		//count_if() сосчитайте количество строк, начинающихся с заданной
		//буквы

		list <string> listStr;
		listStr.push_back("aoaoaooaoo");
		listStr.push_back("boboboobbo");
		listStr.push_back("ababbababba");
		listStr.push_back("aoaoaooaoo");

		int n1 = count(listStr.begin(), listStr.end(), "aoaoaooaoo");
		string a = "a";
		int k1 = count_if(listStr.begin(), listStr.end(), [a](string str) {return str[0] == a[0]; });

		stop;
		//5д. С помощью алгоритма count_if() сосчитайте количество строк,
		//которые совпадают с заданной строкой. Подсказка: смотри тему
		//объекты-функции
		string sss;
		int m1 = count_if(listStr.begin(), listStr.end(), [sss](string str) {return str == sss; });
		stop;
	

	cout << "\n\n";
}