#pragma once
#include <cstring>
#include <iostream>
using namespace std;

class my_string {
public:
	char* arr;
	int l;//äëèíà ñòðîêè1;
	my_string();//êîíñòðóêòîð ïî óìîë÷àíèþ;
	my_string(const my_string& str);//êîíñòðóêòîð êîïèðîâàíèÿ äëÿ îáúåêòà êëàññà;
	my_string(const char* str);//êîíñòðóêòîð êîïèðîâàíèÿ äëÿ ñòðîêè;
	~my_string();             //äåñòðóêòîð
	void print() const;            //ìåòîä ïå÷àòè ñòðîêè íà ýêðàí
	my_string operator+(my_string s);  //îïåðàöèÿ + äëÿ ñêëåèâàíèÿ äâóõ ñòðîê
	my_string& operator=(my_string s); //îïåðàöèÿ = (ïðèñâîåíèå ñòðîê)
	void operator+=(my_string &s);//îïåðàöèÿ += äëÿ ñêëåèâàíèÿ äâóõ ñòðîê
	char operator[](int value) const;  //îïåðàöèÿ [] äëÿ äîñòóïà ê îòäåëüíûì ñèìâîëàì ñòðîêè
	bool operator==(my_string& s) const;  //îïåðàöèÿ ïðîâåðêè íà ðàâåíñòâî ==
	bool operator!=(my_string& s) const;  //îïåðàöèÿ ïðîâåðêè íà íåðàâåíñòâî !=
	int Find(char *s) const;         //ìåòîä ïîèñêà ïîäñòðîêè â ñòðîêå
	bool Find_Symbol(char symbol) const;  //ìåòîä ïîèñêà ñèìâîëà â ñòðîêå
};

my_string::my_string() :arr(new char[1]) { l = 0; arr[0] = 0; }//äëèíà ðàâíà íóëþ, íî ïðè ýòîì íåîáõîäèìî âûäåëèòü ïàìÿòü åùå ïîä 
//íóëü-òåðìèíàòîð '\0' â êîíöå ñòðîêè;
my_string::my_string(const my_string& str) : arr(new char[str.l + 1])
{
	l = strlen(str.arr);//ôóíêöèÿ strlen ñ÷èòàåò äëèíó ñòðîêè ïî äîñòèæåíèè íóëü-òåðìèíàòîðà;
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
	return my_string(buf);//êîíñòðóêòîð êîïèðîâàíèÿ ñòðîêè buf;
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
		return this->arr[value];//äîñòóï ê ïîëþ êëàññà ÷åðåç óêàçàòåëü íà îáúåêò;
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
}// äàëåå - ïîèñê ïîäñòðîêè s â ñòðîêå arr (ïîëå êëàññà);
int my_string::Find(char *s) const {//ñóòü: ïåðâûé öèêë áóäåò âûïîëíÿòü ïðîõîä ïî âñåé ñòðîêå, è èñêàòü ìåñòîïîëîæåíèå ïåðâîé 
	//áóêâû èñêîìîé ñòðîêè, âòîðîé, íà÷èíàÿ ñ íàéäåííîé ïîçèöèè ïåðâîé áóêâû — ñâåðÿòü, êàêèå áóêâû ñòîÿò ïîñëå íå¸ è ñêîëüêî èç 
	//íèõ ïîäðÿä ñîâïàäàþò;
	int i, j;
	for (i = 0; i < l - strlen(s); i++) {//ïîêà åñòü âîçìîæíîñòü ïîèñêà;
		for (j = 0; arr[i + j] == s[j]; j++);//ïðîâåðÿåì ñîâïàäåíèå ïîñèìâîëüíî;
		if (j - strlen(s) == 1 and i == l - strlen(s)) return i;//åñëè ïîñèìâîëüíî ñîâïàäàåò ïî äëèíå èñêîìîãî,
		//âåðíåì èç ôóíêöèè íîìåð ÿ÷åéêè, îòêóäà íà÷èíàåòñÿ ñîâïàäåíèå (ó÷èòûâàÿ íóëü-òåðìèíàòîð);
	}
	return -1;//èíà÷å âåðíåì -1 êàê ðåçóëüòàò îòñóòñòâèÿ ïîäñòðîêè;
}
bool my_string::Find_Symbol(char symbol) const {
	for (int i = 0; i < l; i++) {
		if (symbol == arr[i]) {
			return true;
		}
	}
	return false;
}
