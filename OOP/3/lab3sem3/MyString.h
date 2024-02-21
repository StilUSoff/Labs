#pragma once
class MyString
{
private:
	char* m_pStr;		// ������� ������ ������ (����� ������)
public:
	MyString();
	MyString(const MyString& other);
	MyString(const char* s);	// ���������� ������������
	~MyString();		// ���������� �����������
	MyString(char* s);
	MyString& operator = (const MyString& other);
	void Copy(char* s);
	char* GetString();	// ���������� ������ (accessor)
	int GetLength();	// ���������� ������ (����� ������)
	void Check(const char* str);

};

