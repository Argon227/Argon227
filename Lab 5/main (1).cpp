#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

//template <class TYPE>
class Matrix{
private:
    int **arr;
    int rows;
    int columns;
public:
    Matrix(){}
    Matrix(int row, int cols): rows(row), columns(cols){
        arr = new int*[row];
        for(int i = 0; i < row; i++){
            arr[i] = new int[cols]{};
        }
    }

    ~Matrix(){
//        for(int i = 0; i < rows; i++){
//            delete[] arr[i];
//        }
//        delete[] arr;
    }

    int Rows(){
        return rows;
    }

    int Columns(){
        return columns;
    }


    void Read(string filename){
        ifstream file(filename);

        if (!file.is_open()){
            cout << "ERROR";
        }else{
            file >> rows >> columns;

            arr = new int*[rows];
            for(int i = 0; i < rows; i++){
                arr[i] = new int[columns];
            }

            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    file >> arr[i][j];
                }
            }
        }
        file.close();
    }

    void Print(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout << arr[i][j] << " ";
            }
            cout<<endl;
        }
    }

    Matrix operator+(Matrix& other)const {
        assert(rows == other.rows && columns == other.columns);
        Matrix result(other.rows, other.columns);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                result.arr[i][j] = arr[i][j] + other.arr[i][j];
            }
        }
        return result;
    }

    Matrix operator-(Matrix& other)const {
        assert(rows == other.rows && columns == other.columns);
        Matrix result(other.rows, other.columns);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                result.arr[i][j] = arr[i][j] - other.arr[i][j];
            }
        }
        return result;
    }

    Matrix operator*(Matrix& other)const {
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

    Matrix Transp()const {
        Matrix result(columns, rows);
        for (int i = 0; i < rows; i++){
            for( int j = 0; j < columns; j++){
                result.arr[j][i] = arr[i][j];
            }
        }
        return result;
    }

    Matrix operator=(Matrix& other)const{
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                arr[i][j] = other.arr[i][j];
            }
        }
        return *this;
    }

    bool operator==(Matrix& other)const{
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

    friend istream& operator>>(istream& is, Matrix& other){
        for (int i = 0; i < other.rows; i++){
            for (int j = 0; j < other.columns; j++){
                cout<<"arr["<<i<<"]["<<j<<"] = ";
                is >> other.arr[i][j];
            }
        }
        return is;
    }

    friend ostream& operator<<(ostream& os,const Matrix& other){
        for (int i = 0; i < other.rows; i++){
            for (int j = 0; j < other.columns; j++){
                os.width(other.rows);
                os << other.arr[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }

};
int main() {

    Matrix matrix1;
    Matrix matrix2;
    Matrix matrix3(4,4);
    Matrix matrix4;

    cin >> matrix3;
    cout << matrix3;

    matrix1.Read("A.txt");
    matrix2.Read("B.txt");
    matrix4.Read("D.txt");

    cout << "Умножение матриц 1 и 2 == 3? => " << ((matrix1*matrix2) == matrix4);
    return 0;
}