// Контейнеры STL: 
//deque, stack, queue, priority_queue
//set, multiset, map, multimap
//Итераторы. Стандартные алгоритмы. Предикаты.

#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include "Point.h"
#include "MyVector.h"
#include "MyString.h"
#include "Rect.h"

using namespace std;
#define	  stop __asm nop

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

template <class T> void predic(T& v) {
	cout << v << " ";
}



template <typename T>
class izm
{
private:
	int x;
	int y;
public:
	izm(int x, int y) { this->x = x; this->y = y; }
	void operator()(T& v) { 
		v.SetX(x);
		v.SetY(y);
	}
};


template<typename T> T Last(stack<T>&arr) {
	return arr.top();
}

template<typename T, typename U, typename V> T Last(priority_queue<T, U, V>&arr) {
	return arr.top();
}


template<typename T> T Last(queue<T>&arr) {
	return arr.front();
}
//Первая часть — это способ объявления функции, которая вызывается
//при вызове экземпляра класса в качестве функции.Вторая пара скобок 
//будет содержать фактические аргументы.
template<typename T> void output(T& arr)
{
	cout << ' ';
	while (!arr.empty())
	{
		cout << Last(arr) << endl; //FIXME объединить Last()
		arr.pop();
	}
}




template <int n, int m>
bool Pred1_1(const Point& p) {
	return (p.get_x() >= -n) && (p.get_y() >= -n) && (p.get_x() <= m) && (p.get_y() <= m);
}


class StrOut
{
public:
	bool operator()(const char* str1, const char* str2) {
		return(str1[0] > str2[0]);
	}
};

int main()
{

	setlocale(0, "");
	//Очередь с двумя концами - контейнер deque
	deque<Point> deqPoint;
	//Создайте пустой deque с элементами типа Point. 
	// С помощью
	//assign заполните deque копиями элементов вектора. 
	vector<Point> v11;
	v11.push_back(Point(1,1));
	v11.push_back(Point(2, 2));
	v11.push_back(Point(3, 3));

	deqPoint.assign(v11.begin(),v11.end());
	stop
		// С помощью
		//разработанного Вами в предыдущем задании универсального шаблона
		//выведите значения элементов на печать
		pr(deqPoint, " ");

	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'
	deque<MyString> deqStr;

	deqStr.push_back("Alsdjaj");
	deqStr.push_back("aaushduashduiahduishd");
	deqStr.push_back("baaaaaaa");
	deqStr.push_back("asadjkasdnjadsnj");
	deqStr.push_front("mlkjlkjjk");
	deqStr.insert(deqStr.begin()+1, "achka");

	deqStr.erase(remove_if(deqStr.begin(), deqStr.end(), [](MyString& str) { return str[0] == 'A' || str[0] == 'a'; }), deqStr.end());
	stop
		////////////////////////////////////////////////////////////////////////////////////


		//Напишите шаблон функции для вывода значений stack, queue, priority_queue
		//Подумайте, как "получать" данное "с верхушки"?
		//Что происходит с контейнерами после вывода значений?


		////////////////////////////////////////////////////////////////////////////////////
		//stack

		//Создайте стек таким образом, чтобы
		//а) элементы стека стали копиями элементов вектора
		//б) при выводе значений как вектора, так и стека порядок значений был одинаковым 
		vector<int> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	stack<int> s;
	pr(vec1, "Vec");
	vector<int>::iterator it = vec1.end();
	while (it != vec1.begin()) {
		--it;
		s.push(*(it));

	}
	output(s);


	//Сравнение и копирование стеков
	//а) создайте стек и любым способом задайте значения элементов
	//б) создайте новый стек таким образом, чтобы он стал копией первого
	//в) сравните стеки на равенство
	//г) модифицируйте любой из стеком любым образом (push, pop, top)
	//д) проверьте, какой из стеков больше (подумайте, какой смысл вкладывается в такое сравнение)
	{

		stack<int> st1;
		st1.push(1);
		st1.push(3);
		st1.push(5);
		stack<int> st2;
		st2.push(2);
		st2.push(4);
		st2.push(6);
		if (st1 == st2) {
			cout << "st1 == st2";
		}
		else {
			const char* s = (st1 > st2)? ">":"<";
			cout << "s1 " << *s << " s2 \n";
		}

		stop

	}


	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point,
	//при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?
	{
		Point a(1,1);
		Point* aPt = &a;
		Point b(2, 2);
		Point* bPt = &b;
		Point c(3, 3);
		Point* cPt = &c;

		vector <Point*> vecPt;
		vecPt.push_back(aPt);
		vecPt.push_back(bPt);
		vecPt.push_back(cPt);
		queue <Point*, vector<Point*>> quePt(vecPt);
		Point* other = quePt.front();
		quePt.front() = quePt.back();
		quePt.back() = other;

		
		stop
	}
	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?


	{
		//vector <const char*> mass{ "qwerty", "aaa", "ccc", "bbb" };
		const char* mass[5] = {"haha", "qwerty", "aaa", "ccc", "bbb"};
		priority_queue < const char*, vector<const char*>, StrOut> str;
		for (int i = 0; i < 5; i++) {
			str.push(mass[i]);
		}
		output(str);

	}


	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом)
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...
	//г) Создайте два множества, которые будут содержать одинаковые значения
	//		типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого
	//	контейнера, например, элементов массива	(что происходит, если в массиве имеются дубли?)

	Point x1(1, 1);
	Point x2(2, 2);
	Point x3(3, 3);
	Point x4(0, 0);
	set <Point> ss{x1, x3, x2};
	pr(ss, "set");
	ss.insert(x4);
	pr(ss, "set");

	set<int> ss1{0, 1, 2, 3 };
	set<int> ss2 = {3, 2, 1, 0, 3, 3};

	vector<int> vv = { 0, 0, 5, 6, 6, 7, 7, 9 };
	ss1.insert(vv.begin(), vv.begin() + 7);
	pr(ss1, "set");
	////////////////////////////////////////////////////////////////////////////////////
	//multiset
	{
		Point x1(1, 1);
		Point x2(2, 2);
		Point x3(3, 3);
		Point x4(0, 0);
		multiset <Point> mss{ x1, x3, x2 };
		pr(mss, "multiset");
		mss.insert(x4);
		pr(mss, "multiset");

		multiset<int> mss1{ 0, 1, 2, 3 };
		multiset<int> mss2 = { 3, 2, 1, 0 };

		vector<int> vv = { 0, 0, 5, 6, 6, 7, 7, 9 };
		mss2.insert(vv.begin(), vv.begin() + 7);
		pr(mss2, "multiset");

	}
	////////////////////////////////////////////////////////////////////////////////////
	//map	
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>,
	//	при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое

	//е) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")


	pair<const char*, int> pair1 = { "Churova", 170000 };
	pair<const char*, int> pair2 = { "Lobanov", 200000 };
	pair<const char*, int> pair3 = { "Iakunin", 250000 };
	map<const char*, int> worker{pair1, pair2, pair3};
	pair<const char*, int> pair4 = { "Bogdanova", 170500 };
	worker.insert(pair4);
	worker["Cherepnov"] = 230000;

	for (map<const char*, int>::iterator itr = worker.begin(); itr != worker.end(); itr++)
	{
		cout << itr->first << " - " << itr->second << endl;
	}

	int other= worker["Bogdanova"];
	worker.erase(worker.find("Bogdanova"));
	worker["Iakunina"] = other;
	stop
	cout << "\n";
	for (map<const char*, int>::iterator itr = worker.begin(); itr != worker.end(); itr++)
	{
		cout << itr->first << " - " << itr->second << endl;
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

	multimap<string, pair<string, string>> dictionary;
	dictionary.insert({ "strange", {"чужой", "странный"} });
	dictionary.insert({ "bat", {"бита", "летучая мышь"} });
	dictionary.insert({ "cape", {"плащ", "мыс"} });
	dictionary.insert({ "mean", {"", "грубый"} });
	dictionary.insert({ "mean", {"", "означать"} });

	cout << "\n";
	for (multimap<string, pair<string, string>>::iterator itr = dictionary.begin(); itr != dictionary.end(); itr++)
	{
		cout << itr->first << " " << itr->second.first << " " << itr->second.second << endl;
	}
	cout << "\n";

	cout << "\n";
	auto word = dictionary.equal_range("mean");
//	auto low = std::lower_bound(word.first, word.second, 3);
//	auto up = std::lower_bound(word.first, word.second, 3);
	/*for (auto i = low; i != up; i++)
		std::cout << (*i).first << ":" << (*i).second.second << '\n';*/
	for (auto i = dictionary.lower_bound("mean"); i != dictionary.upper_bound("mean"); i++)
		std::cout << (*i).first << ":" << (*i).second.second << '\n';
	cout << "\n";



	///////////////////////////////////////////////////////////////////

		//Итераторы

		//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
		//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
		//являются копиями элементов set, но упорядочены по убыванию
		set<Point, greater<>> SetPoint{ Point(1, 1), Point(2, 2), Point(3, 3), Point(4, 4) };
		vector<Point> SetPointRev(SetPoint.rbegin(), SetPoint.rend());
		stop

			//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
			//vector и set из предыдущего задания на экран.

		copy(SetPoint.begin(), SetPoint.end(), ostream_iterator<Point>(cout, " "));
		cout << "\n";
		copy(SetPointRev.begin(), SetPointRev.end(), ostream_iterator<Point>(cout, " "));
		cout << "\n";

		//Итераторы вставки. С помощью возвращаемых функциями:
		//back_inserter()
		//front_inserter()
		//inserter()
		//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
		//какие из итераторов вставки можно использовать с каждым контейнером.
		/*  •back_insert_iterator(использует push_back)
			• front_insert_iterator(использует push_front)
			• insert_iterator(использует insert)*/
		back_insert_iterator<vector<Point>> back_iter = back_inserter(SetPointRev);
		front_insert_iterator<deque<Point>> front_iter = front_inserter(deqPoint);
		insert_iterator<vector<Point>> iter = inserter(SetPointRev, find(SetPointRev.begin(),
			SetPointRev.end(), Point(2, 3)));

	///////////////////////////////////////////////////////////////////

		//Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

		// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
		//(массив, vector, list...)
		//С помощью алгоритма for_each в любой последовательности с элементами любого типа
		//распечатайте значения элементов
		//Подсказка : неплохо вызываемую функцию определить как шаблон
		
		for_each(SetPointRev.begin(), SetPointRev.end(), predic<Point>);
		stop

		//С помощью алгоритма for_each в любой последовательности с элементами типа Point
		//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
		//как шаблон) и выведите результат с помощью предыдущего предиката

		for_each(SetPointRev.begin(), SetPointRev.end(), izm<Point>(1, 1));
		for_each(SetPointRev.begin(), SetPointRev.end(), predic<Point>);

		//С помощью алгоритма find() найдите в любой последовательности элементов Point
		//все итераторы на элемент Point с указанным значением.
		auto itt = SetPointRev.begin();
		Point point = Point(1, 1);
		find(itt, end(SetPointRev), point);



		//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
		////По умолчанию алгоритм сортирует последовательность по возрастанию.
		//Что должно быть определено в классе Point?
		// Замечание: обобщенный алгоритм sort не работает со списком, так как
		//это было бы не эффективно => для списка сортировка реализована методом класса!!!
		sort(SetPointRev.begin(), SetPointRev.end());



		//Создайте глобальную функцию вида: bool Pred1_1(const Point& ), которая будет вызываться
		//алгоритмом find_if(), передавая в качестве параметра очередной элемент последовательности.
		//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
		//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
		//[-n, +m].
		find_if(SetPointRev.begin(), SetPointRev.end(), Pred1_1<1, 1>);


		//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
		//располагая прямоугольники по удалению центра от начала координат.
		Rect r1(1,2,1,2);
		Rect r2(2, 3, 3, 2);
		Rect r3(7,1,4,2);
		vector<Rect> VecRect{r1,r2,r3};

		sort(VecRect.begin(), VecRect.end(), [](Rect& dl, Rect& hi) {
			return dl.Center() < hi.Center();});




	{//transform
		//Напишите функцию, которая с помощью алгоритма transform переводит 
		//содержимое объекта string в нижний регистр.
		//Подсказка: класс string - это "почти" контейнер, поэтому для него
		// определены методы begin() и end()
			string str = "DONFOSNFJSNFJDFN";
			transform(str.begin(), str.end(), str.begin(), tolower);
			cout << "\n\n" << str;

		//Заполните list объектами string. С помощью алгоритма transform сформируте
		//значения "пустого" set, конвертируя строки в нижний регистр
			list<string> ListString{ "AIAIAIA", "JJJJJJ", "JSDNJSNCJCN", "JSNJNDJNJDNJSN"};
			set<string> SetString;

			transform(ListString.begin(), ListString.end(), inserter(SetString, SetString.begin()), [](string s) {
				for (int i = 0; i < s.size(); i++)
					s[i] = tolower(s[i]);
				return s;});

			//inserter - это шаблон удобной функции, который создает std::insert_iterator для контейнера c и его итератор я с типом, выведенным из типа аргумента.

		stop
	}
	{// map

		//Сформируйте любым способом вектор с элементами типа string.
		//Создайте (и распечатайте для проверки) map<string, int>, который будет
		//содержать упорядоченные по алфавиту строки и
		//количество повторений каждой строки в векторе
		cout << "\n";
		vector<string> VecString{ "AAAAAA", "asmkldmaklsdm", "IWANTTOSLEEEEEP", "VIUVIUVIUVI", "AAAAAA" };
		map<string, int> MapString;
		auto iter = VecString.begin();
		while (iter != VecString.end()) {
			MapString[*iter]++;
			iter++;
		}
		for (map<string, int>::iterator itr = MapString.begin(); itr != MapString.end(); itr++)
		{
			cout << itr->first << " - " << itr->second << endl;
		}





	}




	return 0;
}

