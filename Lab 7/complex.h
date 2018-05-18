//
// Created by levin on 24.04.18.
//

#ifndef LAB_7_COMPLEX_H
#define LAB_7_COMPLEX_H


#include <iostream>

using namespace std;
class Complex
{
private:
    double Re, Im;
public:
    Complex();
    Complex(double, double);
    void print(ostream&);
    Complex add(const Complex&);
    Complex sub(const Complex&);
    Complex mul(int a);
    Complex div(int a);
    double real();
    double imaginary();
    Complex(const Complex&);
    Complex operator*(const Complex&);
    Complex operator/(const Complex&);
    Complex operator+=(const Complex&);
    Complex operator-=(const Complex&);
    Complex operator*=(const Complex&);
    Complex operator/=(const Complex&);
    Complex operator=(const Complex&);
    bool operator==(const Complex&);
};

#endif //LAB_7_COMPLEX_H
