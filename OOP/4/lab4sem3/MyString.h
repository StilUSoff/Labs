#pragma once
#include <cstdarg>
#include <iostream>

class MyString
{
    char* m_pStr;	//строка-член класса
    void Check(const char*);

public:
    MyString();
    ~MyString();
    MyString(const char*);
    MyString(const MyString& other);
    MyString ConcatStr(const char* val);
    const char* GetString() const;
    void SetNewString(const char*);
    //---------------------------------------
    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
    //-------------------------------------------------------
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    MyString operator+(const MyString& other) const;
    MyString operator+(const char* str) const;
    MyString& operator+=(const MyString& other);
    bool operator==(const char* s) {
        return (strcmp(s, m_pStr) == 0);
    }
    bool operator==(MyString s) {
        return (strcmp(s.GetString(), m_pStr) == 0);
    }

    static MyString addExtension(const MyString& str) {
        return (str + ".txt");
    }
    char& operator[](int index)
    {
        return m_pStr[index];
    }

    // для константных объектов
    const char& operator[] (int index)  const
    {
        return m_pStr[index];
    }
};

MyString Concat(int count, ...);

