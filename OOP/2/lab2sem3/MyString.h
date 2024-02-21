#pragma once
class MyString
{
private:
	char* m_pStr;		// Ёлемент данных класса (адрес строки)
public:
	MyString();
	MyString(const MyString& other);
	MyString(const char* s);	// ќбъ€вление конструктора
	~MyString();		// ќбъ€вление деструктора
	MyString(char* s);
	MyString& operator = (const MyString& other);
	void Copy(char* s);
	const char* GetString();	// ќбъ€вление метода (accessor)
	int GetLength();	// ќбъ€вление метода (длина строки)
	void Check(const char* str);
};
#pragma once
