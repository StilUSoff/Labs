#include <cmath>			// математические функции
#include <locale.h>	// функции, устанавливающие национальные кодировки символов
#include <iostream>	// Эта - часть библиотеки STL (Standard Template Library)
#include <limits>			// Полезные константы
#include <conio.h>

using namespace std;		// Обеспечивает видимость имен STL

int n;	 // Глобальная переменная. По умолчанию она обнуляется.

namespace space	 // В пространстве имен - space
{
	int n = 1;	 // Объявлена переменная n
}				 // space определяет область видимости этой переменной

int  main()
{
	// Выполняя программу по шагам, следите за значениями переменных  и интерпретируйте результат, объясняя себе
	// наблюдаемые значения. Обратите внимание на разную интерпретацию отладчиком  signed и unsigned типов данных.
	char c = 'A'; // 65 'A' 0x41 
	// В комментарии справа полезно проставить десятичное символьное и шестнадцатиричное 
	// значения переменной после выполнения указанной строки. Вы должны видеть их в окне Autos.
	c = 0x42;		// 66 'B' 0x42
	c = -1;		// -1 'я' 0xff
	c = CHAR_BIT;	 // Размер переменной типа char, 8 бит
	

	// В комментариях напишите результат, возвращаемый оператором sizeof для
	// переменной типа wchar_t (ее размер)
	wchar_t cw = L'Ф'; //1060 'Ф'
	size_t ns = sizeof(cw); //2 байта

	unsigned char uc = 0x41; // 65 'А'
	uc = 'B'; // 66 'B'
	uc = -3; // 255 'я' 0xfe, тк 0xff - 255
	

	int i = 1; 
	i = -1; // всё хорошо, так как переменная signed
	

	unsigned int ui = 1; // 1
	ui = -1; //4294967295, так как unsigned

	short s = 0xffff;	 // Здесь compiler генерирует warning. Измените код, чтобы убрать warning
	s = short(0xffff);
	s = 1;

	//==== Измените код, чтобы убрать warning

	//int us = static_cast<int>(static_cast<unsigned short>(0xffff));
	//unsigned short us = static_cast<unsigned short>(static_cast<int>(5));
	unsigned short us = 0xffff;
	us = 5;

	long l = 0xffffffff; //-1
	l = -128;

	// Все эти константы вы должны найти в файле limits (float.h) и объяснить их смысл по комментариям


	l = FLT_MAX_EXP; // Максимальное целое значение для степени в нормализованной форме представления числа с плавающей точкой (запятой).(float)	
	l = DBL_MAX_EXP; // тоже самое только у double

	l = FLT_MANT_DIG; //Количество цифр мантиссы, соответственно для float
	l = DBL_DIG; // Количество десятичных цифр, которые могут быть округлены в число с плавающей точкой и обратно, без потери данных для doble

	l = FLT_MANT_DIG; // было выше
	l = DBL_MANT_DIG; // снова мантисса, но для double

	float f = -12.56;	 // Здесь warning. Уберите его.
	f = static_cast<float>(-12.56);
	f = -1.e-27f;  

	f = FLT_MAX;
	f = FLT_MIN;

	double d = 0.1234567890123456789123456789;
	d = -0.123456789012345e+306;
	d = DBL_MAX;
	d = DBL_MIN;
	d = DBL_EPSILON; // Самая маленькая разность между двумя пер-ми типа double

	uc = ~1;		 // Побитовое отрицание/ 255'я'
	i = ~0; //-1. Тк это знаковый int, а прошлый был беззнаковый 
	
	// Раннее (при компиляции) или неявное приведение типов данных
	// Объясните те значения, которые вы наблюдаете в окне Autos. Определите порядок выполения присваиваний.
	d = f = i = s = c = 1 / 3; // 0 char
	c = s = i = f = d = 100 / 3; // doublw 33.0
	c = s = i = f = d = 10 / 3; // double 3.0
	c = s = i = f = d = 1 / 3.; // double 0.3333333333333..
	// присваивание выполняется справа налево


	// Пример "небрежного" использования неявного приведения типов.	 Объясните результаты.
	i = 256; // int к int всё нормик
	c = i; // 0, так как это чар, то от -128 до 127

	uc = 255; //255, всё хорошо "я"
	unsigned char u = 2, sum = uc + u; // u = 2, но sum не 257, а 2
	

	// Явное приведение типов	Объясните разницу результатов в строках (3) и (4)
	i = 100;
	f = d = i / 3;							// (3) так как у нас i - int,то происходит целочисленное деление и после приведение к double в остватке все равно 0
	f = d = (double)i / 3;		// (4) мы привели к double 33, а после присвоили к другим doublr
	f = d = double(i) / 3;			// (4) мы привели i к double и теперь при деление на 3 у нас остатковая часть не теряется
	f = d = static_cast<double>(i) / 3;		// (4) более Сишное приведение
	

	// Область действия, область видимости и время существования. В этом фрагменте фигурируют четыре
	//  переменных с одним и тем же именем n.  Одна - глобальная, вторая определена в своем пространстве имен,
	// третья - локальная внутри функции main(), четвертая - локальная внутри блока. 
	//  Обратите внимание, что глобальная переменная и та, что в пространстве имен space - объявлены вне функции main()
	// Определите, к какой из четырех переменных идет обращение, cформулируйте область действия и область видимости
	// каждой переменной. Для выполнения задания рекомендуется пользоваться  закладкой "Watches" или "Locals" окна
	// "Autos". Подсказка: В окно "Watches" можно поместить сразу все переменные (n, ::n, и space::n)
	n = 100;
	space::n = 200;
	n++;
	int n;		//Где живет эта переменная ?  
	n = 10;
	::n++;

	{				//  Начало блока
		int n;		// Эта переменная живет внутри блока
		n = -1;
		n++;
		::n++;
		space::n++;
	}		// Конец блока
	n--;
	::n--;
	space::n--;

	// Спецификатор класса памяти - static Выполняя задание по шагам, обратите внимание на  разное поведение
	// переменных nLoc и nStat
	{
	Again:
		int outer;
		for (int i = 0; i < 5; i++)
		{
			static int nStat; //объявилась один раз
			{
				int nLoc = 0; //каждый раз объявляется по новой и прибавляется по новой
				nLoc++;		nStat++;
			}
			outer = nStat;
		}
		if (outer < 10)
			goto Again;
	}
	// Перечисления - enum. Обратите внимание на явную и неявную инициализацию констант
	enum RANK
	{
		One, //= 0 
		Two, // = 1
		Three,// = 2
		Four, // = 3
		Jack = 6, // = 6
		Queen, // = 7
		Ace = Queen + 3, // = 10
		Joker = 20 // 20
	};
	typedef RANK RANG;

	RANG r = Jack;
	if (r == Jack)
		r = Queen;

	if (r == Queen)
	{
		// Любой целочисленной переменной можно присвоить enum-переменную 
		int i = r;
		r = RANK(i++);		// Обратное преобразование надо указывать явно/ сначала присвоилось, а потом прибавилось
		i = r; //i = 7 снова
		r = RANK(++i); //теперь уже сначала прибавилось потом присвоилось
		i = r; //i = 8
	}
	RANK rr = Ace; //10
	
	//	Логический тип bool.	Выполняя задание по шагам, следите за значениями переменной b
	{
		int n = 127;
		bool b = n != 0; //True
		b = n == 0; //false
		b = n > 0; //true
		b = n <= 0; // false
		b = n > 1; //true

		int num = static_cast<int>(b); //num = 1
		if (b)
			cout << "\n\t My flag is: true" << "   or: " << b
			<< "\n\t Conversion to int: " << num << endl;
		b = n == num; //false
		cout << "\n\t Now the flag is: false" << "   or: " << b;
	}

	//	Модификатор const
	const double pi = acos(-1.);
	double space_permiability = 4.e-7 * pi;		//	Магнитная проницаемость пустоты
	const int dozen = 12;
	int var = dozen;

	//	Раскомментируйте следующую строчку и объясните ошибку компиляции (l-value означает left value)
		/*dozen = 1;*/
	//	Директивы условной трансляции. Объясните значение, которое принимает переменная version.
	//	Что нужно сделать для того, чтобы результат был другим?
#define _MSVER311
	const char* version;
#if defined _MSVER400
	version = "version 4.00";
#elif defined _MSVER311
	version = "version 3.11";
#else
	version = "version Unknown";
#endif

	cout << endl << version;
	

	//В окне ClassView или Solution Explorer поставьте фокус на имя проекта дайте команду Project/Properties.
	//	В диалоге Property Pages щелкните на папке Configuration Properties, убедитесь, что в разделе Code Generation
	//	установлена константа компиляции _DEBUG. Создайте директивы препроцессора и код С++, которые
	//	в зависимости от действующей конфигурации проекта (_DEBUG или NDEBUG) выводят соответствующее
	//	сообщение. Измените конфигурацию проекта (в диалоге Property Pages) и проверьте ваш код.
	//	Чтобы изменить конфигурацию пользуйтесь кнопкой Configuration Manager
	{
	#define DEBUG
	#ifdef DEBUG
			cout << "Debug";
	#endif

	}
	//	Простейшие циклы. Объясните суть происходящего. 
	{
		// Цикл while надо использовать, когда неизвестно количество итераций (повторений) цикла.
		cout << "\n\nGradually eat out all the units:\n\n";
		unsigned short us = 0xff;
		while (us)
		{
			cout << hex << us << endl;
			us &= us - 1;
		}
		cout << hex << us << "\nDone\n";
		// Цикл for надо использовать, когда известно количество итераций и/или есть код подготовки.
		// Подсказка: odd - нечетое, even - четное.
		cout << "\n\nShow even-odd:\n\n";
		for (int i = 0; i < 10; i++)
		{
			if (5 & 3)//101 011
				cout << i << " - odd\n";
			else
				cout << i << " - even\n";
		}
		// Когда нужно использовать цикл do-while? Когда сначала нужно выполнить не проверку условия, а действие
		char c = ' ';
		do
		{
			if (c == 'a')
				cout << "\nAction is a delegate type in C#";
			else if (c == 'b')
				cout << "\nbreak is one of the 'leave' statements in all C-like languages";
			else if (c == 'c')
				cout << "\ncontinue is a 'go on' statement in all C-like languages";
			else if (c == 'd')
				cout << "\ndo-while is a rarely used loop statement in all C-like languages";
			else
				cout << "\nPlease read the rules of this loop";
			cout << "\n\nEnter chars: a, b, c, d (q - to quit):\n\n";
			cin >> c;
			if (c == 'q')
				cout << "\nI am going to leave the loop\n";
		} while (c != 'q');
		
	}
	//	Логические условные операторы и циклы. Функция y = f(x) задана графиком
	//	Напишите фрагмент кода, который с шагом 0.1 вычисляет y = f(x)  и выводит в консольное окно значения x и y. 
	//	  y
	//	  | 
	//	 2|__________
	//	  |        2/\
	//	  |        /  \
	//	  |       /    \
	//	  |______/      \__________  x           y=-|(x*2)-4|+2
	//	  0      1   2   3
	//	 Реалируйте 2 варианта этого алгоритма:   1. Используйте операторы if	 2. Используйте тернарные операции    ? :
	{
		for (double x = 0.5; x < 3.5; x=x+0.1) {
			if ((x <= 1) || (x >= 3)) {
				cout << "x = " << x << " y = 0 \n";
			}
			else if ((x > 1) || (x <= 2)) {
				cout << "x = " << x << " y = " << 2*x-2 << "\n";
			}
			else {
				cout << "x = " << x << " y = " << 2 * x + 6 << "\n";
			}
			int y;
			cout << "x = " << x << " y = " << (((x<=1)||(x>=3))?0: y = -abs((x*2)-4)+2) << "\n";
		}
	}

	//	Напишите фрагмент, который с помощью for и switch реализует следующую логику. Если пользователь ввел:
	//	символ 'a',   ваш алгоритм выводит  "Ok" (в кавычках)
	//	символ 'b',   ваш алгоритм выводит  Bell (alert - звуковой сигнал)
	//	символ 'с',   ваш алгоритм выводит  число, которое равно количеству введенных символов
	//	символ 'Esc', ваш алгоритм выводит  "to quit use 'q'"
	//	символ 'q',   ваш алгоритм выводит  "Bye" и выходит из цикла ввода

	{
		int num = 0;
		for (char c = ' '; c != 'q'; c = _getch()) {
				switch (c)
				{
				case ' ':
					cout << " Hello! \n 'a' -> Ok \n 'b' -> Bell \n 'c' -> num of sym \n 'q' - Bye \n";
					break;
				case 'a':
					cout << "Ok\n";
					break;
				case 'b':
					cout << "\a";
				case 'c':
					cout << "num - \n" << num;
					break;
				case 27:
					cout << "to quit use 'q'\n";
					break;
				default:
					cout << "invalid value";
					break;
				}
				num++;
		}
		cout << "bye!";
	}


	//	Побитовые операции:  |, &, ~, ^ и сдвиги >>, <<
	//	Поменяйте местами байты переменной flags и выведите результат в консолное окно unsigned short flags = 0xaabb;
	//	Ваш код
	unsigned short flags = 0xbafe;
	unsigned short flags1 = flags << 8;
	unsigned short flags2 = flags >> 8;
	cout << "\n bits = " << hex << flags << " " << flags1 << "|" << flags2 << "=" << (flags1 | flags2);
	//	Для вывода в шестнадцатеричном виде используйте  cout <<"\n bits = " << hex << flags;
	//	В переменной unsigned char byte = 0x26; 
	unsigned char byte = 0x2f;
	byte |= (1 << 3);
	int ch = static_cast<unsigned char>(byte);
	cout << endl << hex << ch << endl << dec << ch; //- установите в единицу 3-й бит (счет от нуля). Выведите результат.

	//	- инвертируйте два младших бита. Выведите результат. 
	byte ^= 0x3;//1100 0011
	ch = static_cast<unsigned char>(byte);
	cout << endl << hex << ch << endl << dec << ch;

	//      - обнулите 4 младших бита. Выведите результат.
	byte &= 0x20;
	ch = static_cast<unsigned char>(byte);
	cout << endl << hex << ch << endl << dec << ch;

	//	cout <<endl << hex << flags << endl<<dec<<flags;    
	cout << "\n\n";
}	// Конец функции main()
