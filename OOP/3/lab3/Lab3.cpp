//=======================================================================
//	Лабораторная №3. Шаблоны функций. Шаблоны классов. Стандартные шаблоны С++.
//				Обработка исключений.
//=======================================================================
//Используйте недостающие файлы из лабораторной 2
#include "stdafx.h"
#include "MyVector.h"
#include "MyString.h"
#include "MyStack.h"
#include "utils.h"


//============= Шаблон функции для вывода с помощью итератора
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

		Vector u(1,2), w(-3,-4);
		Swap(u, w);

		// Если вы достаточно развили класс MyString в предыдущей работе,
		// то следующий фрагмент тоже должен работать корректно.
		
		MyString s1 ("Your fault"), s2 ("My forgiveness");
		Swap (s1, s2);
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

		cout << "\nInteger Stack capacity: " << stack.Capacity() << endl;

		stack.Push(1);
		stack.Push(2);
		stack.Push(3);

		cout << "\nInteger Stack has: " << stack.GetSize() << " elements\n";

		 stack.Push(4);	// Здесь должно быть "выброшено" исключение

		cout << "\nInteger Stack pops: " << stack.Pop();
		cout << "\nInteger Stack pops: " << stack.Pop();
		
		cout << "\nInteger Stack has: " << stack.GetSize() << " elements\n";
		stack.Pop();

		 stack.Pop();		// Здесь должно быть "выброшено" исключение

		stack.Push(2);
		
		// int i = stack[3];	// Здесь должно быть "выброшено" исключение

		MyStack<Vector, 5> ptStack;
		
		cout << "\nVector Stack capacity: " << ptStack.Capacity();
		
		ptStack.Push(Vector(1,1));
		ptStack.Push(Vector(2,2));
		
		cout << "\nVector Stack pops: ";

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
	};


// 	//=======================================================================
// 	// Контейнеры стандартной библиотеки. Последовательности типа vector
// 	//=======================================================================
	
// 	// Создайте пустой вектор целых чисел. Узнайте его размер с помощью метода size(),
// 	// С помощью метода push_back() заполните вектор какими-либо значениями.
// 	// Получите новый размер вектора и выведите значения его элементов.
// 	// В процессе работы с вектором вы можете кроме количества реально заполненных
// 	// элементов (size()) узнать максимально возможное количество элементов (max_size()),
// 	// а также зарезервированную память (capacity()).

	vector<int> v;
	int n = v.size();

	v.push_back(-1);
	v.push_back(-2);
	
	n = v.size(); // 2
	n = v.capacity(); // 2
	n = v.max_size(); // -1 - размер максимального контейнера не ограничен.


// 	// Так как мы часто будем выводить последовательности, то целесообразно
// 	// создать шаблон функции для вывода любого контейнера.
// 	// Проанализируйте коды такого шабдлона (pr), который приведен выше
// 	// Используйте его для вывода вашего вектора

	pr (v, "Vector of ints");
	
// 	// Используем другой конструктор для создания вектора вещественных
// 	// с начальным размером в 2 элемента и заполнением (222.).
// 	// Проверим параметры вектора. Затем изменим размер вектора и его заполнение
// 	// (метод - resize()) и вновь проверим параметры.
	
	vector<double> vd(2, 222.);
	pr (vd, "Vector of doubles");
	n = vd.size();
	n = vd.capacity();
	n = vd.max_size();

	vd.resize(5, 333.); // Добавит еще два элемента == 333.0

	// vd.resize(1, 333.); // Уберет один последний элемент
	// =vd.resize(1);       // Уберет один последний элемент

	pr (vd, "After resize");
	n = vd.size(); // 5
	n = vd.capacity(); // 5
	n = vd.max_size(); // -1
	

//	// Используя метод at(), а также операцию выбора [], измените значения
//	// некоторых элементов вектора и проверьте результат.
	vd.at(0) = 1.1;
	vd[2] = 2.2;
	pr(vd, "After at");
	

//	// Создайте вектор вещественных, который является копией существующего.
	vector<double> wd(vd);
	pr(wd, "Copy");
	

//	// Создайте вектор, который копирует часть существующей последовательности
    vector<double> ud(vd.begin() + 1, vd.begin() + 3);
	pr(ud, "Copy part");


// 	// Создайте вектор вещественных, который является копией части обычного массива.
	double ar[] = { 0., 1., 2., 3., 4., 5. };
    vector<double> va (ar + 2, ar + 5);
	pr (va, "Copy part of array");
	

// 	// Создайте вектор символов, который является копией части обычной строки
	char s[] = "Array is a succession of chars";
	vector<char> vc (s + 6, s + 15);
	pr (vc, "Copy part of c-style string");


// 	// Создайте вектор элементов типа Vector и инициализируйте его вектором с координатами (1,1).
	vector<Vector> vv {Vector(1, 1)};
	cout << "\n\nVector of Vectors\n";
	for (int i=0;  i < vv.size();  i++)
		vv[i].Out();


// 	// Создайте вектор указателей на Vector и инициализируйте его адресами объектов класса Vector
	Vector v1(3, 4);
	Vector v2(5, 2);
	vector<Vector*> vp {&v1, &v2};
	cout << "\n\n\nVector of pointers to Vector\n";
	for (int i = 0;  i < vp.size();  i++)
		vp[i]->Out();


// 	// Научитесь пользоваться методом assign и операцией присваивания = для контейнеров типа vector.
	vp.assign(2, &v1);
	cout << "\n\nAfter assign\n";
	for (int i=0;  i < vp.size();  i++)
		vp[i]->Out();
	
	
// 	// Декларируйте новый вектор указателей на Vector и инициализируйте его с помощью второй версии assign
	vector<Vector*> vpNew;
	vpNew.assign(vp.begin(), vp.end());
	cout << "\n\nNew vector after assign\n";
	for (int i=0;  i < vpNew.size();  i++)
		vpNew[i]->Out();


// 	// На базе шаблона vector создание двухмерный массив и заполните его значениями разными способами.
// 	// Первый вариант - прямоугольная матрица
// 	// Второй вариант - ступенчатая матрица

	
// 	//========= Ступенчатая матрица
	int MatrixSize = 5;

	vector<vector<double>> vdd(MatrixSize);
	for (int i=0;  i < vdd.size();  i++)
		vdd[i] = vector<double>(i+1, double(i));
	
	cout << "\n\nTest vector of vector<double>\n";
	for (int i=0;  i < vdd.size();  i++) {
		cout << endl;
		for (int j=0;  j < vdd[i].size();  j++)
			cout << vdd[i][j] << "  ";
	};

	vector<vector<double>> vdr(MatrixSize);
	for (int i=0;  i < vdr.size();  i++)
		vdr[i] = vector<double>(MatrixSize, double(i));
	
	cout << "\n\nTest vector of vector<double>\n";
	for (int i=0;  i < vdr.size();  i++) {
		cout << endl;
		for (int j=0;  j < vdr[i].size();  j++)
			cout << vdr[i][j] << "  ";
	};

	//===================================
	// Простейшие действия с контейнерами
	//===================================


	//3б. Получение значения первого и последнего элементов последовательности.
	//Получение размера последовательности. Присваивание значений
	//элементов одной последовательности элементам другой - assign().

	 // Создайте и проинициализируйте вектор из элементов char.
    vector<char> charVector = {'a', 'b', 'c', 'd', 'e'};

    // Создайте и проинициализируйте массив из элементов char.
    char charArray[] = {'x', 'y', 'z', 'w', 'v'};

    // Получите значение первого элемента вектора (front())
    char firstElement = charVector.front();
    std::cout << "\n\n\nПервый элемент вектора: " << firstElement << std::endl;

    // Получите значение последнего элемента вектора (back())
    char lastElement = charVector.back();
    std::cout << "Последний элемент вектора: " << lastElement << std::endl;

    // Получите размер вектора
    std::cout << "Размер вектора: " << charVector.size() << std::endl;

    // Присвойте вектору любой диапазон из значений массива charArray
    charVector.assign(charArray, charArray + 4);

    // Проверьте размер вектора, первый и последний элементы после присваивания
    std::cout << "\nПосле присваивания:" << std::endl;
    std::cout << "Размер вектора: " << charVector.size() << std::endl;
    std::cout << "Первый элемент вектора: " << charVector.front() << std::endl;
    std::cout << "Последний элемент вектора: " << charVector.back() << std::endl;



	//3в. Доступ к произвольным элементам вектора с проверкой - at() и без проверки - []

	//Создайте неинициализированный вектор из 8 элементов char - vChar2.
	//С помощью at() присвойте четным элементам вектора значения
	//элементов vChar1 из предыдущего задания,
	//а с помощью [] присвойте нечетным элементам вектора vChar2 значения
	//массива {'K','U','K','U'}.

	char kukushka[4] = {'K','U','K','U'};

	vector<char> vChar2(8);
	for (int i = 0; i < vChar2.size(); i++) {
		if (i % 2 == 0) {
			vChar2.at(i) = charVector.at(i/2);
		}
		else {
			vChar2[i] = kukushka[i/2];
		}
	}
	
	pr(vChar2, "vChar2");
	  
	//Попробуйте "выйти" за границы вектора с помощью at() и
	//с помощью []. Обратите внимание: что происходит при
	//попытке обращения к несуществующему элементу в обоих случаях
	
	try {
		vChar2.at(10) = 'a';
	}
	catch (std::out_of_range) {
		cout << "Out of range" << endl;
	}

	// vChar2[10] = 'a'; // error
	


	//3г.Добавьте в конец вектора vChar2  - букву Z (push_back()). Для
	//расширения кругозора можете ее сразу же и выкинуть (pop_back())

	vChar2.push_back('Z');
	vChar2.pop_back();
	

	//3д. Вставка-удаление элемента последовательности insert() - erase()
	//Очистка последовательности - clear()

	//Вставьте перед каждым элементом вектора vChar2 букву 'W'
	vector<char>::iterator it = vChar2.begin();
    while (it != vChar2.end()) {
        it = vChar2.insert(it, 'W');
        it+=2;
	}

	//Вставьте перед 5-ым элементом вектора vChar2 3 буквы 'X'
	vChar2.insert(vChar2.begin() + 4, 3, 'X');


	//Вставьте перед 2-ым элементом вектора vChar2 с третьего по
	//шестой элементы массива "aaabbbccc"
	char aaabbbccc[9] = {'a','a','a','b','b','b','c','c','c'};
	vChar2.insert(vChar2.begin() + 1, aaabbbccc + 2, aaabbbccc + 5);
  

	//Сотрите c первого по десятый элементы vChar2
	vChar2.erase(vChar2.begin(), vChar2.begin() + 10);
	

	//Уничтожьте все элементы последовательности - clear()
	vChar2.clear();


///////////////////////////////////////////////////////////////////

	//Задание 4. Списки. Операции, характерные для списков.

	//Создайте два пустых списка из элементов Vector - ptList1 и ptList2
	list<Vector> ptList1;
	list<Vector> ptList2;



	//Наполните оба списка значениями с помощью методов push_back(), push_front, insrert()
	ptList1.push_back(Vector(1, 2));
    ptList1.push_back(Vector(2, 3));
    ptList1.push_back(Vector(3, 4));

    ptList2.push_front(Vector(4, 1));
    ptList2.push_front(Vector(2, 2));
    ptList2.push_front(Vector(3, 5));

    ptList2.insert(ptList2.begin(), Vector(1, 1));

	//Отсортируйте списки - sort().
	//Подсказка: для того, чтобы работала сортировка, в классе Vector
	//должен быть переопределен оператор "<"

	ptList1.sort();
	ptList2.sort();
  
	//Объедините отсортированные списки - merge(). Посмотрите: что
	//при этом происходит со вторым списком.

	ptList1.merge(ptList2);
	// второй список стал пустым


	//Исключение элемента из списка - remove()
	//Исключите из списка элемент с определенным значением.
	//Подсказка: для этого необходимо также переопределить
	//в классе Vector оператор "=="

	ptList1.remove(Vector(1, 1));
	ptList1.remove(Vector(3, 5));



///////////////////////////////////////////////////////////////////

	//Задание 5. Стандартные алгоритмы.Подключите заголовочный файл <algorithm>

	//5а. Выведите на экран элементы ptList1 из предыдущего задания с помощью алгоритма for_each()
	for_each(ptList1.begin(), ptList1.end(), [](Vector v) { v.Out(); });


	//5б.С помощью алгоритма find() найдите итератор на элемент Vector с определенным значением. 
	list<Vector>::iterator itr2 = find(ptList1.begin(), ptList1.end(), Vector(4, 1));
	bool wasFound = itr2 != ptList1.end();


	// С помощью алгоритма find_if() найдите
	//итератор на элемент, удовлетворяющий определенному условию, 
	//например, обе координаты точки должны быть больше 2.
	//Подсказка: напишите функцию-предикат, которая проверяет условие
	//и возвращает boolean-значение (предикат может быть как глобальной
	//функцией, так и методом класса)

	list<Vector>::iterator itr3 = find_if(ptList1.begin(), ptList1.end(), [](Vector v) {return v > Vector(5, 5);});
	wasFound = itr3 != ptList1.end();


	//Создайте список из указателей на элеметы Vector. С помощью 
	//алгоритма find_if() и предиката (можно использовать предикат - 
	//метод класса Vector, определенный в предыдущем задании) найдите в
	//последовательности элемент, удовлетворяющий условию
	
	list<Vector*> ptList3;
	list<Vector*>::iterator itr4 = find_if(ptList3.begin(), ptList3.end(), [](Vector* v) {return *v > Vector(5, 5);});
	wasFound = itr3 != ptList1.end();


	//5в. Создайте список элементов Vector. Наполните список
	//значениями. С помощью алгоритма replace() замените элемент
	//с определенным значением новым значением. С помощью алгоритма
	//replace_if() замените элемент, удовлетворяющий какому-либо
	//условию на определенное значение. Подсказка: условие
	//задается предикатом.

	list<Vector> ptList5 = {Vector(1, 1), Vector(2, 2), Vector(3, 3)};
	replace(ptList5.begin(), ptList5.end(), Vector(2, 2), Vector(4, 4));
	replace_if(ptList5.begin(), ptList5.end(), [](Vector v) {return v < Vector(2, 2);}, Vector(5, 5));


	//5г. Создайте вектор строк (string). С помощью алгоритма count()
	//сосчитайте количество одинаковых строк. С помощью алгоритма
	//count_if() сосчитайте количество строк, начинающихся с заданной
	//буквы

	vector<string> strVector = {"abc", "abc", "def", "abc"};
	int c = count(strVector.begin(), strVector.end(), "abc");
	c = count_if(strVector.begin(), strVector.end(), [](string s) {return s[0] == 'a';});


	//5д. С помощью алгоритма count_if() сосчитайте количество строк,
	//которые совпадают с заданной строкой. Подсказка: смотри тему
	//объекты-функции

	string str = "abc";
	c = count_if(strVector.begin(), strVector.end(), [str](string s) {return s == str;});

}