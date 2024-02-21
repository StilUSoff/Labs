#include "stdafx.h"
#include "MyString.h"
#pragma warning(disable:4996)

MyString::MyString() {
	m_pStr = nullptr;
}
MyString::MyString(const char* str) {
	Check(str);
}
MyString::MyString(const MyString& other) {
	m_pStr = nullptr;
	Check(other.m_pStr);
}

void MyString::Copy(char* s)
{
	delete[] m_pStr;
	// ����������� �������� ��������� ���������� ������.
	int len = strlen(s) + 1;
	m_pStr = new char[len];
	// + 1, ��� ��� ������� ���� ���� ����� �����������
	// ���� ������ ��������, �������� ������-�������� � ������-���� ������
	if (m_pStr)
		strcpy_s(m_pStr, len, s);
}

// ����������� ������������.
MyString::MyString(char* s)
{
	m_pStr = 0;
	Copy(s);
}

// ����������� �����������.
MyString::~MyString()
{
	// ������������ ������, ������� � ������������ ��� ������-����� ������
	delete m_pStr;
}

// ����� ������
char* MyString::GetString()
{
	return m_pStr;
}

int MyString::GetLength()
{
	return strlen(m_pStr) + 1;
}

void MyString::Check(const char* str) {
	if (str == nullptr) {
		m_pStr = new char;
		*m_pStr = 0;
	}
	else {
		m_pStr = new char[strlen(str) + 1];
		strcpy(m_pStr, str);
	}
}

MyString& MyString::operator= (const MyString& other) {

	if (this->m_pStr == other.m_pStr) return *this;

	delete[] this->m_pStr;
	Check(other.m_pStr);

	return *this;
}