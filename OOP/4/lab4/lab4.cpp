#include "utils.h"
#include "Point.h"
#include "MyString.h"
#include "Rect.h"

using namespace std;	


int main()
{

	//Очередь с двумя концами - контейнер deque

	//Создайте пустой deque с элементами типа Point. С помощью
	//assign заполните deque копиями элементов вектора. С помощью
	//разработанного Вами в предыдущем задании универсального шаблона
	//выведите значения элементов на печать

	deque<Point> pointDeque;
	//pointDeque[5];
    vector<Point> pointVector;

    pointVector.push_back(Point(1, 2));
    pointVector.push_back(Point(3, 4));
    pointVector.push_back(Point(5, 6));

	pointDeque.assign(pointVector.begin(), pointVector.end());

	pr(pointDeque, "pointDeque");


	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'

	deque<MyString> myStringDeque;

	myStringDeque.push_back(MyString("abc"));
	myStringDeque.push_front(MyString("def"));
	myStringDeque.insert(myStringDeque.begin(), MyString("ghi"));

	pr(myStringDeque, "myStringDeque");

	for (auto it = myStringDeque.begin(); it != myStringDeque.end(); ) {
		if (it->GetString()[0] == 'a' || it->GetString()[0] == 'A') {
			it = myStringDeque.erase(it);
		} else {
			++it;
		}
	}

	pr(myStringDeque, "myStringDeque");

	////////////////////////////////////////////////////////////////////////////////////


	//Напишите шаблон функции для вывода значений stack, queue, priority_queue
	//Подумайте, как "получать" данное "с верхушки"?
	//Что происходит с контейнерами после вывода значений?


	////////////////////////////////////////////////////////////////////////////////////
	//stack

	//Создайте стек таким образом, чтобы
	//а) элементы стека стали копиями элементов вектора
	//б) при выводе значений как вектора, так и стека порядок значений был одинаковым 

	stack<Point> pointStack;

	for (int i = pointVector.size() - 1; i >= 0; i--) {
        pointStack.push(pointVector[i]);
    }

	pr(pointVector, "pointVector");
	myPr(pointStack, "pointStack");


	//Сравнение и копирование стеков
	//а) создайте стек и любым способом задайте значения элементов
	//б) создайте новый стек таким образом, чтобы он стал копией первого
	//в) сравните стеки на равенство
	//г) модифицируйте любой из стеком любым образом (push, pop, top)
	//д) проверьте, какой из стеков больше (подумайте, какой смысл вкладывается в такое сравнение)
	{
		
		stack<Point> pointStack1;
		stack<Point> pointStack2;

		pointStack1.push(Point(1, 2));
		pointStack1.push(Point(10, 10));
		pointStack1.push(Point(5, 6));

		pointStack2 = pointStack1;

		cout << endl << (pointStack1 == pointStack2) << endl;

		pointStack1.pop();

		cout << (pointStack1 < pointStack2) << endl;

		// Сравнение между объектами стеков основывается на попарном сравнении элементов этих списков. 
		// Отношение "меньше" между двумя объектами стека основывается на сравнении первой пары неравных элементов.
	}


	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point, при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?
	{	
		Point* p1 = new Point(1, 2);
		Point* p2 = new Point(10, 10);
		Point* p3 = new Point(5, 6);//delete

		deque<Point*> pointPDeque{p1, p2, p3};
		queue<Point*> pointPQueue(pointPDeque);

		pointPQueue.front()->x = 100;
		pointPQueue.back()->y = 150;

		myPr(pointPQueue, "pointPQueue");

		delete p1, p2, p3;
	}


	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?

	{
		const char* str1 = "cccc";
		const char* str2 = "aaa";
		const char* str3 = "c";

		const char* strArr[] = {str1, str2, str3};

		priority_queue<const char*, vector<const char*>, CompareStr> strPQueue(strArr, strArr + 3);//FIXME

		// c b a 
		//strPQueue.pop(); // c
		myPr(strPQueue, "strPQueue");
	}
	

	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом)
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...

	// В контейнере std::set в C++ элементы не могут быть изменены после того, как они были добавлены в множество. 
	// Это связано с тем, что std::set представляет собой контейнер, реализующий структуру данных "множество" (set), 
	// которая подразумевает уникальность элементов и автоматическую сортировку.

	//г) Создайте два множества, которые будут содержать одинаковые значения типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого контейнера, например, элементов массива (что происходит, если в массиве имеются дубли?)

	// определить операторы сравнения (например, оператор < или ==), чтобы можно было создавать множество объектов класса Point
	{
		set<Point> pointSet;

		pointSet.insert(Point(1, 2));
		pointSet.insert(Point(10, 10));
		pointSet.insert(Point(5, 6));

		pr(pointSet, "pointSet");

		set<int> intSet1{1, 2, 3, 4, 5};
		multiset<int> intSet2{5, 4, 3, 2, 1, 5};

		pr(intSet1, "intSet1");
		pr(intSet2, "intSet2");

		int intArr[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
		intSet1.insert(intArr, intArr + 10);

		pr(intSet1, "intSet1");
	}

	////////////////////////////////////////////////////////////////////////////////////
	//map	
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>, при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое
	//е) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")

	{
		map<const char*, int> salaryMap;

		salaryMap["Ivanova"] = 100;
		salaryMap["Petrova"] = 200;
		salaryMap["Sidorova"] = 300;

		salaryMap.insert(make_pair("Kuznetsova", 400));
		salaryMap.insert(make_pair("Kuznetsov", 500));

		cout << endl;
		for (const auto& pair : salaryMap) {
			cout << pair.first << ": " << pair.second << endl;
		};

    	auto it = salaryMap.find("Ivanova");
    	if (it != salaryMap.end()) {
        	int salary = it->second;
        	salaryMap.erase(it);
        	salaryMap["Anton"] = salary;
		};

		cout << endl;
		for (const auto& pair : salaryMap) {
			cout << pair.first << ": " << pair.second << endl;
		};
	}

	////////////////////////////////////////////////////////////////////////////////////
	//multimap
	//а) создайте "англо-русский" словарь, где одному и тому же ключу будут соответствовать
	//		несколько русских значений - pair<string,string>, например: strange: чужой, странный...
	//б) Заполните словарь парами с помощью метода insert или проинициализируйте с помощью 
	//		вспомогательного массива пара (пары можно конструировать или создавать с помощью шаблона make_pair)
	//в) Выведите все содержимое словаря на экран
	//г) Выведите на экран только варианты "переводов" для заданного ключа. Подсказка: для нахождения диапазона
	//		итераторов можно использовать методы lower_bound() и upper_bound()

{
		multimap<string, string> dict;

		dict.insert(make_pair("strange", "чужой"));
		dict.insert(make_pair("strange", "странный"));
		dict.insert(make_pair("strange", "необычный"));
		dict.insert(make_pair("label", "метка"));
		dict.insert(make_pair("label", "наклейка"));

		cout << endl;
		for (const auto& pair : dict) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}

		string wordToFind = "label";
		cout << "\nПереводы для ключа '" << wordToFind << "':" << endl;
		auto lower = dict.lower_bound(wordToFind);
		auto upper = dict.upper_bound(wordToFind);
		for (auto it = lower; it != upper; ++it) {
			cout << it->second << endl;
		}

}

///////////////////////////////////////////////////////////////////

	//Итераторы

	//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
	//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
	//являются копиями элементов set, но упорядочены по убыванию

	// Реверсивный итератор (Reverse Iterator).
	// Реверсивный итератор предоставляет возможность перебирать элементы коллекции в обратном порядке. 
	// Это означает, что он начинает с конца коллекции и двигается к ее началу. 
	// Реверсивные итераторы полезны, когда вам нужно выполнить обратный обход элементов в обратном порядке

	{
		set<Point> pointSet;

		pointSet.insert(Point(1, 2));
		pointSet.insert(Point(10, 10));
		pointSet.insert(Point(5, 6));

		vector<Point> pointVector(pointSet.rbegin(), pointSet.rend());

		pr(pointVector, "pointVector");


	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.

		cout << "\n";

		ostream_iterator<Point> outputIterator(cout, "\n");

		// Используем ostream_iterator для вывода элементов вектора
		for (const Point& point : pointVector) {
			*outputIterator = point;  // Записываем значение в поток
			++outputIterator;       // Перемещаем итератор вперед
		}

		cout << "\n";

		// Используем ostream_iterator для вывода элементов множества
		for (const Point& point : pointSet) {
			*outputIterator = point;  // Записываем значение в поток
			++outputIterator;       // Перемещаем итератор вперед
		}

		cout << "\n";


	//Итераторы вставки. С помощью возвращаемых функциями:
	//back_inserter()
	//front_inserter()
	//inserter()
	//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
	//какие из итераторов вставки можно использовать с каждым контейнером.

	back_insert_iterator<vector<Point>> backInserter(pointVector);
	*backInserter = Point(1, 1);

	// back_insert_iterator<set<Point>> backInserter2(pointSet);  // 'class std::set<Point>' has no member named 'push_back' 
	// front_insert_iterator<vector<Point>> frontInserter(pointVector); // 'class std::vector<Point>' has no member named 'push_front'
	// front_insert_iterator<set<Point>> frontInserter(pointSet); // class std::set<Point>' has no member named 'push_front'
	
	list<int> lst;
	front_insert_iterator<list<int>> front_inserter_it(lst);
	*front_inserter_it = 2;

	set<int> my_set = {3, 5, 8};
    inserter(my_set, next(my_set.begin(), 1)) = 7;
}

///////////////////////////////////////////////////////////////////

	//Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

	vector<Point> pv {Point(1, 1), Point(2, 2), Point(3, 3)};

	// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
	//(массив, vector, list...)
	//С помощью алгоритма for_each в любой последовательности с элементами любого типа
	//распечатайте значения элементов
	//Подсказка : неплохо вызываемую функцию определить как шаблон
	
	for_each(pv.begin(), pv.end(), printElement<Point>);
	cout << '\n';

	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
	//как шаблон) и выведите результат с помощью предыдущего предиката

	for_each(pv.begin(), pv.end(), changeElement<Point, 3>);
	for_each(pv.begin(), pv.end(), printElement<Point>);
	cout << '\n';

	//С помощью алгоритма find() найдите в любой последовательности элементов Point
	//все итераторы на элемент Point с указанным значением.

	auto it = find(pv.begin(), pv.end(), Point(4, 4));
	while (it != pv.end()) {
		cout << *it << endl;
		it = find(next(it), pv.end(), Point(4, 4));
	}
	
	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
	////По умолчанию алгоритм сортирует последовательность по возрастанию.
	//Что должно быть определено в классе Point?
	// Замечание: обобщенный алгоритм sort не работает со списком, так как
	//это было бы не эффективно => для списка сортировка реализована методом класса!!!
	
	sort(pv.begin(), pv.end());
	pr(pv, "pv2");

	//Создайте глобальную функцию вида: bool Pred1_1(const Point& ), которая будет вызываться
	//алгоритмом find_if(), передавая в качестве параметра очередной элемент последовательности.
	//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
	//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
	//[-n, +m].

	auto it2 = find_if(pv.begin(), pv.end(), Pred1_1<3, 5>); //FIXME


	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
	//располагая прямоугольники по удалению центра от начала координат.

	vector<Rect> rects;
    rects.push_back(Rect(1, 2));
    rects.push_back(Rect(3, 4));
    rects.push_back(Rect(2, 2));

	sort(rects.begin(), rects.end(), [](const Rect& a, const Rect& b) {
        return a.distanceFromOrigin() < b.distanceFromOrigin();
    });

	//Напишите функцию, которая с помощью алгоритма transform переводит 
	//содержимое объекта string в нижний регистр.
	//Подсказка: класс string - это "почти" контейнер, поэтому для него
	// определены методы begin() и end()

	string str = "ABC";
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	cout << str << endl;


	//Заполните list объектами string. С помощью алгоритма transform сформируте
	//значения "пустого" set, конвертируя строки в нижний регистр
	
	list<string> strList{"ABC", "DEF", "GHI"};
	set<string> strSet;
	transform(strList.begin(), strList.end(), inserter(strSet, strSet.begin()), [](string& str) {
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	});
		
	//Сформируйте любым способом вектор с элементами типа string.
	//Создайте (и распечатайте для проверки) map<string, int>, который будет
	//содержать упорядоченные по алфавиту строки и
	//количество повторений каждой строки в векторе
	
	vector<string> strVector{"ABC", "DEF", "GHI", "ABC", "DEF", "GHI", "ABC", "DEF", "GHI"};
	map<string, int> strMap;

	for (const auto& str : strVector) {
		strMap[str]++;
	}

	for (const auto& pair : strMap) {
		cout << pair.first << ": " << pair.second << endl;
	}

	return 0;
}

