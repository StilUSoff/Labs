#include "utils.h"
#include "MyString.h"

void MyString::Copy (char* s)
{
	delete [] m_pStr;

	// Динамически выделяем требуемое количество памяти.
	int len = strlen(s) + 1;
	m_pStr = new char[len];

	// + 1, так как нулевой байт тоже нужно скопировать
	// Если память выделена, копируем строку-аргумент в строку-член класса
	if (m_pStr)
		strcpy_s (m_pStr, len, s);
}

MyString::MyString() {
	m_pStr = new char[1];
	m_pStr[0] = '\0';
}

MyString::MyString (char* s)
{
	m_pStr = 0;
	Copy(s);
}

MyString::~MyString()
{
	delete[] m_pStr;
}

// Метод класса
char* MyString::GetString()
{
	return m_pStr;
}

int MyString::GetLength()
{
	return strlen(m_pStr) + 1;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) Copy(other.m_pStr);
	return *this;
}


MyString::MyString(const MyString& other)
{
	m_pStr = 0;
	Copy(other.m_pStr);
}

ostream& operator<<(ostream& os, const MyString& p) {
	os << "MyString(" <<  p.m_pStr << ")";
    return os;
}
