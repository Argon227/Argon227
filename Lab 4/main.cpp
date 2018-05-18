#define CATCH_CONFIG_MAIN
#include <iostream>

#include "catch.hpp"
#include "matrix.h"

Matrix::Matrix():rows(0), columns(0){}
Matrix::Matrix(int row, int cols): rows(row), columns(cols){
    arr = new int*[row];
    for(int i = 0; i < row; i++){
        arr[i] = new int[cols]{};
    }
}
Matrix::~Matrix(){
//        for(int i = 0; i < rows; i++){
//            delete[] arr[i];
//        }
//        delete[] arr;
}

int Matrix::Rows(){
    return rows;
}
int Matrix::Columns(){
    return columns;
}
int Matrix::Element(int i, int j) {
    if (i < rows && j < columns) {
        return arr[i][j];
    }else{
        return 1;
    }
}

void Matrix::Read(string filename) {
    ifstream file(filename);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            file >> arr[i][j];
        }
    }
}

void Matrix::Print(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            cout.width(rows);
            cout << arr[i][j] << " ";
        }
        cout<<endl;
    }
}

Matrix Matrix::operator+(Matrix& other)const{
    assert(rows == other.rows && columns == other.columns);
    Matrix result(other.rows, other.columns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result.arr[i][j] = arr[i][j] + other.arr[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(Matrix& other)const{
    assert(rows == other.rows && columns == other.columns);
    Matrix result(other.rows, other.columns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            result.arr[i][j] = arr[i][j] - other.arr[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator*(Matrix& other)const{
    assert(columns == other.rows);
    Matrix result(rows, other.columns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < other.columns; j++){
            int tmp = 0;
            for(int t = 0; t < columns; t++){
                tmp += arr[i][t]*other.arr[t][j];
            }
            result.arr[i][j] = tmp;
        }
    }
    return result;
}
Matrix Matrix::Transp()const{
    Matrix result(columns, rows);
    for (int i = 0; i < rows; i++){
        for( int j = 0; j < columns; j++){
            result.arr[j][i] = arr[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator=(Matrix& other)const{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            arr[i][j] = other.arr[i][j];
        }
    }
    return *this;
}
bool Matrix::operator==(Matrix& other)const{
    if(rows != other.rows || columns != other.columns){
        return false;
    }else{
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                if(arr[i][j] != other.arr[i][j]){
                    return false;
                }
            }
        }
    }
    return true;
}

ostream& operator<<(ostream& os,const Matrix& other){
    for (int i = 0; i < other.rows; i++){
        for (int j = 0; j < other.columns; j++){
            os.width(other.rows);
            os << other.arr[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

SCENARIO("matrix new w/o params","[new w/o params]"){
    Matrix matrix;
    REQUIRE(matrix.Rows() == 0);
    REQUIRE(matrix.Columns() == 0);
}

SCENARIO("matrix new with params","[new with params]"){
    Matrix matrix(3,3);
    REQUIRE(matrix.Rows() == 3);
    REQUIRE(matrix.Columns() == 3);
}

SCENARIO("matrix operator+","[oper+]"){
    Matrix matrix1(2,2), matrix2(2,2);
    ofstream file1("A.txt");
    file1 << "1 2 3 4";
    file1.close();
    ofstream file2("B.txt");
    file2 << "5 6 7 8";
    file2.close();
    matrix1.Read("A.txt");
    matrix2.Read("B.txt");
    REQUIRE(matrix1.Element(0,0) + matrix2.Element(0,0) == 6);
    REQUIRE(matrix1.Element(0,1) + matrix2.Element(0,1) == 8);
    REQUIRE(matrix1.Element(1,0) + matrix2.Element(1,0) == 10);
    REQUIRE(matrix1.Element(1,1) + matrix2.Element(1,1) == 12);
}

SCENARIO("matrix operator-","[oper-]"){
    Matrix matrix1(2,2), matrix2(2,2);
    ofstream file1("A.txt");
    file1 << "1 2 3 4";
    file1.close();
    ofstream file2("B.txt");
    file2 << "4 6 8 1";
    file2.close();
    matrix1.Read("A.txt");
    matrix2.Read("B.txt");
    REQUIRE(matrix2.Element(0,0) - matrix1.Element(0,0) == 3);
    REQUIRE(matrix2.Element(0,1) - matrix1.Element(0,1) == 4);
    REQUIRE(matrix2.Element(1,0) - matrix1.Element(1,0) == 5);
    REQUIRE(matrix2.Element(1,1) - matrix1.Element(1,1) == -3);
}

SCENARIO("matrix operator*", "[oper*]") {
    Matrix matrix1(2,2), matrix2(2,2);
    ofstream file1("A.txt");
    file1 << "1 2 3 4";
    file1.close();
    ofstream file2("B.txt");
    file2 << "4 3 2 1";
    file2.close();
    matrix1.Read("A.txt");
    matrix2.Read("B.txt");
    REQUIRE(matrix1.Element(0,0) * matrix2.Element(0,0) + matrix1.Element(0,1) * matrix2.Element(1,0) == 8);
    REQUIRE(matrix1.Element(0,0) * matrix2.Element(0,1) + matrix1.Element(0,1) * matrix2.Element(1,1) == 5);
    REQUIRE(matrix1.Element(1,0) * matrix2.Element(0,0) + matrix1.Element(1,1) * matrix2.Element(1,0) == 20);
    REQUIRE(matrix1.Element(1,0) * matrix2.Element(0,1) + matrix1.Element(1,1) * matrix2.Element(1,1) == 13);
}

SCENARIO("matrix operator==" , "[oper==]") {
    Matrix matrix1(2,2), matrix2(2,2);
    ofstream file1("A.txt");
    file1 << "1 1 1 1";
    file1.close();
    ofstream file2("B.txt");
    file2 << "1 1 1 1";
    file2.close();
    matrix1.Read("A.txt");
    matrix2.Read("B.txt");
    for (int i = 0; i < matrix1.Rows(); i++)
    {
        for (int j = 0; j < matrix1.Columns(); j++)
        {
            REQUIRE(matrix1.Element(i,j) == matrix2.Element(i,j));
        }
    }

}

SCENARIO("matrix operator=" , "[oper=]") {
    Matrix matrix1(2,2), matrix2(2,2);
    ofstream file1("A.txt");
    file1 << "1 2 3 4";
    file1.close();
    matrix1.Read("A.txt");
    matrix2 = matrix1;
    REQUIRE(matrix1.Element(0,0) == 1);
    REQUIRE(matrix1.Element(0,1) == 2);
    REQUIRE(matrix1.Element(1,0) == 3);
    REQUIRE(matrix1.Element(1,1) == 4);

}


