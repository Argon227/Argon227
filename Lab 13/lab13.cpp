// lab13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "lab13.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	char arr2[] = "test";
	my_string ms1;
	my_string ms2(arr2);
	cin >> ms1;
	ms1 += ms2;
	cout << ms1 << endl;//выводит в конце какую-то кашу;
	char arr3[] = "test";
	my_string ms3(arr3);
	char arr4[] = "te";
	int	n = ms3.Find(arr4);
    cout << n << endl;//неправильный вывод;
	system("PAUSE");
    return 0;
}

