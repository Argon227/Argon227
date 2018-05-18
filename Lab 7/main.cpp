#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "complex.h"
using namespace std;


    Complex::Complex():Re(0.0),Im(0.0){};
    Complex::Complex(double re, double im): Re(re), Im(im){}
    Complex::Complex(const Complex& other): Re(other.Re), Im(other.Im){}

    void Complex::print(ostream& os){
        if(Im < 0){
            os << Re << Im << "i" << endl;
        }else{
            os << Re <<"+"<< Im << "i" << endl;
        }
    }

    double Complex::real(){
        return Re;
    }
    double Complex::imaginary(){
        return Im;
    }


    Complex Complex::add(const Complex& other){
        return Complex(Re+other.Re, Im+other.Im);
    }
    Complex Complex::sub(const Complex& other){
        return Complex(Re-other.Re, Im-other.Im);
    }
    Complex Complex::mul(int number){
        return Complex(Re*number, Im*number);
    }
    Complex Complex::div(int number){
        try{
            if(number == 0){
                throw 1;
            }
            Re = Re/number;
            Im = Im/number;
        }catch (int number){
            cout << "Division by zero" << endl;

        }
        return Complex(Re, Im);
    }

    Complex Complex::operator*(const Complex& other){
        return Complex(Re*other.Re - Im*other.Im, Im*other.Re + Re*other.Im);
    }
    Complex Complex::operator/(const Complex& other){
        return Complex((Re*other.Re + Im*other.Im)/(other.Re*other.Re + other.Im*other.Im),(Re*other.Im - Im*other.Re)/(other.Re*other.Re + other.Im*other.Im));
    }
    Complex Complex::operator+=(const Complex& other){
        Re += other.Re;
        Im += other.Im;
        return Complex(Re, Im);
    }
    Complex Complex::operator-=(const Complex& other){
        Re -= other.Re;
        Im -= other.Im;
        return Complex(Re, Im);
    }
    Complex Complex::operator*=(const Complex& other){
        double  tmp;
        tmp = Re*other.Re - Im*other.Im;
        Im = Im*other.Re + Re*other.Im;
        Re = tmp;
        return Complex(Re,Im);
    }
    Complex Complex::operator/=(const Complex& other){
        double tmp;
        tmp = (Re*other.Re + Im*other.Im)/(other.Re*other.Re + other.Im*other.Im);
        Im =  (Re*other.Im - Im*other.Re)/(other.Re*other.Re + other.Im*other.Im);
        Re = tmp;
        return Complex(Re,Im);
    }
    Complex Complex::operator=(const Complex& other){
        Re = other.Re;
        Im = other.Im;
        return Complex(Re,Im);
    }
    bool Complex::operator==(const Complex& other){
        return (Re == other.Re && Im == other.Im);
    }

SCENARIO("complex new without param","[new without param]"){
    Complex complex;
    REQUIRE(complex.real() == 0);
    REQUIRE(complex.imaginary() == 0);
}

SCENARIO("complex new with pram","[new with param]"){
    Complex complex(2,-3);
    REQUIRE(complex.real() == 2);
    REQUIRE(complex.imaginary() == -3);
}

SCENARIO("complex copy","[copy]"){
    Complex complex1(2,-3);
    Complex complex2(complex1);
    REQUIRE(complex2.real() == 2);
    REQUIRE(complex2.imaginary() == -3);
}

SCENARIO("complex sum","[sum]"){
    Complex complex1(2,-3), complex2(4,2), complex3(6,-1);
    REQUIRE((complex1.add(complex2) == complex3) == true);
}

SCENARIO("complex sub","[sub]"){
    Complex complex1(2,-3), complex2(4,2), complex3(-2,-5);
    REQUIRE((complex1.sub(complex2) == complex3) == true);
}

SCENARIO("complex mul ", "[mul]") {
    Complex complex1(2, -3), complex2;
    int numbers = 2;
    complex2 = complex1.mul(numbers);
    REQUIRE(complex2.real() == 4);
    REQUIRE(complex2.imaginary() == -6);
}

SCENARIO("complex div", "[div]") {
    Complex complex1(2, -3), complex2;
    int numbers = 2;
    complex2 = complex1.div(numbers);
    REQUIRE(complex2.real() == 1);
    REQUIRE(complex2.imaginary() == -1.5);
}

SCENARIO("complex operator*","[oper*]"){
    Complex complex1(2,-3), complex2(4,2), complex3(14,-8);
    REQUIRE((complex1*complex2 == complex3) == true);
}

SCENARIO("complex operator/","[oper/]"){
    Complex complex1(2,10), complex2(1,5), complex3(2,0);
    REQUIRE((complex1/complex2 == complex3) == true);
}

SCENARIO("complex operator +=","[oper+=]"){
    Complex complex1(2,-3), complex2(4,2), complex3(6,-1);
    complex1 += complex2;
    REQUIRE((complex1 == complex3) == true);
}

SCENARIO("complex operator -=","[oper-=]"){
    Complex complex1(2,-3), complex2(4,2), complex3(-2,-5);
    complex1 -= complex2;
    REQUIRE((complex1 == complex3) == true);
}

SCENARIO("complex operator *=","[oper-*=]"){
    Complex complex1(2,-3), complex2(4,2), complex3(14,-8);
    complex1 *= complex2;
    REQUIRE((complex1 == complex3) == true);
}

SCENARIO("complex operator /=","[oper/=]"){
    Complex complex1(2,10), complex2(1,5), complex3(2,0);
    complex1 /= complex2;
    REQUIRE((complex1 == complex3) == true);
}

SCENARIO("complex operator =","[oper=]"){
    Complex complex1(2,-3), complex2(4,2);
    complex1 = complex2;
    REQUIRE((complex1 == complex2) == true);
}

SCENARIO("complex operator ==","[oper==]"){
    Complex complex1(2,-3), complex2(2,-3);

    REQUIRE((complex1 == complex2) == true);
}





//int main() {
//    Complex complex1(2,10), complex2(1,5);
//
//    Complex complex3 = complex1/complex2;
//    complex1 /= complex2;
//    complex3.print(cout);
//    complex1.print(cout);
//
//
//    return 0;
//}