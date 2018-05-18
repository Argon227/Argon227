#include <iostream>

using namespace std;

class Complex{
private:
    double Re, Im;
public:
    Complex():Re(0.0),Im(0.0){};
    Complex(double re, double im): Re(re), Im(im){}
    Complex(const Complex& other): Re(other.Re), Im(other.Im){}

    void print(ostream& os){
        if(Im < 0){
            os << Re << Im << "i" << endl;
        }else{
            os << Re <<"+"<< Im << "i" << endl;
        }
    }


    Complex add(const Complex& other){
        return Complex(Re+other.Re, Im+other.Im);
    }
    Complex sub(const Complex& other){
        return Complex(Re-other.Re, Im-other.Im);
    }
    Complex mul(int number){
        return Complex(Re*number, Im*number);
    }
    Complex div(int number){
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

    Complex operator*(const Complex& other){
        return Complex(Re*other.Re - Im*other.Im, Im*other.Re + Re*other.Im);
    }
    Complex operator/(const Complex& other){
        return Complex((Re*other.Re + Im*other.Im)/(other.Re*other.Re + other.Im*other.Im),(-Re*other.Im + Im*other.Re)/(other.Re*other.Re + other.Im*other.Im));
    }
    Complex operator+=(const Complex& other){
        Re += other.Re;
        Im += other.Im;
        return Complex(Re, Im);
    }
    Complex operator-=(const Complex& other){
        Re -= other.Re;
        Im -= other.Im;
        return Complex(Re, Im);
    }
    Complex operator*=(const Complex& other){
        double  tmp;
        tmp = Re*other.Re - Im*other.Im;
        Im = Im*other.Re + Re*other.Im;
        Re = tmp;
        return Complex(Re,Im);
    }
    Complex operator/=(const Complex& other){
        double tmp;
        tmp = (Re*other.Re + Im*other.Im)/(other.Re*other.Re + other.Im*other.Im);
        Im =  (-Re*other.Im + Im*other.Re)/(other.Re*other.Re + other.Im*other.Im);
        Re = tmp;
        return Complex(Re,Im);
    }
    Complex operator=(const Complex& other){
        Re = other.Re;
        Im = other.Im;
        return Complex(Re,Im);
    }
    bool operator==(const Complex& other){
        return (Re == other.Re && Im == other.Im);
    }


    template <class CharT, class Traits>
    friend basic_ostream<CharT, Traits>& operator<<(basic_ostream<CharT, Traits>& os, const Complex& other){
        if (other.Im < 0)
        {
            os << other.Re << other.Im << "i" << std::endl;
        }
        else
        {
            os << other.Re << "+" << other.Im << "i" << std::endl;
        }
        return os;
    }

    template <class CharT, class Traits>
    friend basic_istream<CharT, Traits>& operator>>(basic_istream<CharT, Traits>& is, Complex& other){
        cout << "Введите дeйcтвительную и мнимую части числа: ";
        is >> other.Re >> other.Im;
        return is;
    };
};

int main() {

    Complex complex1(2,2), complex2(4,3), complex3, complex4;


    cout << "Комплексное число 1: " << complex1 <<endl;

    Complex complex(complex1);
    cout << "Конструктор копирования: " << complex <<endl;

    cin >> complex3;
    cout << "Комплексное число 3: " << complex3 <<endl;

    complex4 = complex3/complex1;
    cout << "Операция деления 3 числа на 1-ое: " << complex4 <<endl;

    complex4 = complex1*complex3;
    cout << "Операция умножения 3 числа на 1-ое: " << complex4 <<endl;

    complex4 += complex1;
    cout << "Оператор +=: " << complex4 <<endl;

    complex4 -= complex1;
    cout << "Оператор -=: " << complex4 <<endl;

    complex4 *= complex1;
    cout << "Оператор *=: " << complex4 <<endl;

    complex4 /= complex1;
    cout << "Оператор /=: " << complex4 <<endl;

    complex2 = complex1;
    cout << "Оператор копирования: " << complex2 <<endl;

    cout << "Оператор сравнения: " << (complex1 == complex2) <<endl;





    return 0;
}