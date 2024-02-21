#include <string>
#include "MyString.h"

using namespace std;
#pragma warning(disable:4996)

//������������ - ����������
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

MyString::~MyString() {
    delete m_pStr;
}

const char* MyString::GetString() const {
    if (m_pStr == nullptr) return nullptr;
    return m_pStr;
}


void MyString::SetNewString(const char* str) {
    delete m_pStr;
    Check(str);
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




MyString MyString::ConcatStr(const char* str) {
    if (str == nullptr) return nullptr; //������ �� ������ � ������������

    int len_str = strlen(str);
    int m_len = (m_pStr == nullptr ? 0 : strlen(m_pStr));

    char* new_str = new char[len_str + m_len + 1]; //+1 ������ ��� �� ������ ��� ��������� ������
    if (m_pStr) {
        memcpy(new_str, m_pStr, m_len);
        memcpy(new_str + m_len, str, len_str + 1);
    }
    else memcpy(new_str, str, len_str + 1);
    delete[] m_pStr;
    m_pStr = new_str;
    return m_pStr;
}

MyString Concat(int count, ...) {
    MyString str; //������ ��������� ������
    va_list ptr; //��������� 
    va_start(ptr, count); //������ ������ ����������
    while (count != 0) {
        str.ConcatStr(va_arg(ptr, const char*)); //��������� �� ��� Concat �� ������� ��� �������� ����������
        count--;
    }
    va_end(ptr);
    return str;
}



std::ostream& operator<<(std::ostream& out, const MyString& str) {
    out << str.GetString();
    return out;
}






MyString& MyString::operator= (const MyString& other) {

    if (this->m_pStr == other.m_pStr) return *this;

    delete[] this->m_pStr;
    Check(other.m_pStr);

    return *this;
}


MyString& MyString::operator+=(const MyString& other) {
    ConcatStr(other.m_pStr); //������� 
    return *this;
}
MyString MyString::operator+(const MyString& other) const {
    return MyString(*this) += other; //������ ��������� �� +=
}
MyString MyString::operator+(const char* other) const
{
    //������� 
    return MyString(*this).ConcatStr(other);
}



MyString& MyString::operator = (MyString&& other) noexcept {
    delete[] m_pStr;
    m_pStr = other.m_pStr;
    other.m_pStr = 0;
    return *this;
}
