#pragma once
#include <cstring>
#include <iostream>
using namespace std;

class my_string {
public:
	char* arr;
	int l;//����� ������;
	my_string();//����������� �� ���������;
	my_string(const my_string& str);//����������� ����������� ��� ������� ������;
	my_string(const char* str);//����������� ����������� ��� ������;
	~my_string();             //����������
	void print() const;            //����� ������ ������ �� �����
	my_string operator+(my_string s);  //�������� + ��� ���������� ���� �����
	my_string& operator=(my_string s); //�������� = (���������� �����)
	void operator+=(my_string &s);//�������� += ��� ���������� ���� �����
	char operator[](int value) const;  //�������� [] ��� ������� � ��������� �������� ������
	bool operator==(my_string& s) const;  //�������� �������� �� ��������� ==
	bool operator!=(my_string& s) const;  //�������� �������� �� ����������� !=
	int Find(char *s) const;         //����� ������ ��������� � ������
	bool Find_Symbol(char symbol) const;  //����� ������ ������� � ������
};

my_string::my_string() :arr(new char[1]) { l = 0; arr[0] = 0; }//����� ����� ����, �� ��� ���� ���������� �������� ������ ��� ��� 
//����-���������� '\0' � ����� ������;
my_string::my_string(const my_string& str) : arr(new char[str.l + 1])
{
	l = strlen(str.arr);//������� strlen ������� ����� ������ �� ���������� ����-�����������;
	for (int i = 0; i < str.l + 1; i++) {
		arr[i] = str.arr[i];
	}
}
my_string::my_string(const char* str) :arr(new char[strlen(str) + 1])
{
	l = strlen(str);
	for (int i = 0; i < l; i++) {
		arr[i] = str[i];
	}
}
my_string::~my_string() {
	delete[] arr;
	l = 0;
}
void my_string::print() const {
	for (int i = 0; i < l; i++) {
		  cout << arr[i];
	}
}
my_string my_string::operator+(my_string s) {
	char *buf = new char[l + s.l + 1];
	for (int i = 0; i < l; i++) {
		buf[i] = arr[i];
	}
	for (int j = 0; j < s.l; j++) {
		buf[l + j] = s.arr[j];
	}
	return my_string(buf);//����������� ����������� ������ buf;
}
my_string& my_string::operator=(my_string s) {
	delete[] this->arr;
	arr = new char[s.l + 1];
	l = s.l;
	for (int i = 0; i < s.l; i++) {
		arr[i] = s.arr[i];
	}
	return *this;
}
void my_string::operator+=(my_string& s) {
	char *buf = new char[l + 1];
	for (int i = 0; i < l; i++) {
		buf[i] = arr[i];
	}
	delete[] this->arr;
	arr = new char[l + s.l + 1];
	for (int i = 0; i < l; i++) {
		arr[i] = buf[i];
	}
	for (int j = 0; j < s.l; j++) {
		arr[l + j] = s.arr[j];
	}
	l += s.l;
}
char my_string::operator[](int value) const {
	if (value > 0 and value < l + 1) {
		return this->arr[value];//������ � ���� ������ ����� ��������� �� ������;
	}
}
bool my_string::operator==(my_string& s) const {
	if (l == s.l) {
		for (int i = 0; i < l; i++) {
			if (s.arr[i] != arr[i]) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}
bool my_string::operator!=(my_string& s) const {
	if (l == s.l) {
		for (int i = 0; i < l; i++) {
			if (s.arr[i] != arr[i]) {
				return true;
			}
		}
	}
	else {
		return true;
	}
	return false;
}
ostream& operator<<(ostream& output, my_string str) {
	output << str.arr;
	return output;
}
istream& operator>>(istream& input, my_string& str) {
	char *buf = new char[2048];
	input >> buf;
	delete[] str.arr;
	str.arr = new char[strlen(buf) + 1];
	str.l = strlen(buf);
	for (int i = 0; i < strlen(buf); i++) {
		str.arr[i] = buf[i];
	}

	return input;
}// ����� - ����� ��������� s � ������ arr (���� ������);
int my_string::Find(char *s) const {//����: ������ ���� ����� ��������� ������ �� ���� ������, � ������ �������������� ������ 
	//����� ������� ������, ������, ������� � ��������� ������� ������ ����� � �������, ����� ����� ����� ����� �� � ������� �� 
	//��� ������ ���������;
	int i, j;
	for (i = 0; i < l - strlen(s); i++) {//���� ���� ����������� ������;
		for (j = 0; arr[i + j] == s[j]; j++);//��������� ���������� �����������;
		if (j - strlen(s) == 1 and i == l - strlen(s)) return i;//���� ����������� ��������� �� ����� ��������,
		//������ �� ������� ����� ������, ������ ���������� ���������� (�������� ����-����������);
	}
	return -1;//����� ������ -1 ��� ��������� ���������� ���������;
}
bool my_string::Find_Symbol(char symbol) const {
	for (int i = 0; i < l; i++) {
		if (symbol == arr[i]) {
			return true;
		}
	}
	return false;
}