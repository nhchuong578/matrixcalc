    // file: matrix.cpp
#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
#include "matrix.h"
using namespace std;
//memory allocation
void Matrix::allocate(){
    entry = new double*[row];
    for (int i=0; i <row; ++i){
        entry[i]= new double[col];
    }
}
void Matrix::deallocate(){
    for (int i=0; i <row; ++i){
        delete [] entry[i];
    }
    delete [] entry;
}
//constructors
Matrix:: Matrix(const int& r, const int& c){
    assert(r > 0 && c > 0);
    row = r;
    col = c;
    allocate();
}

Matrix::Matrix(const int& r, const int& c, const double &val): 
Matrix(r,c){
    for(int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            entry[i][j] = val;
        }
    }
}
Matrix::Matrix(const Matrix& mat){
    row = mat.getRows();
    col = mat.getCols();
    allocate();

    //copy each entry of mat to entry
    for(int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            entry[i][j] = mat(i,j);
        }
    }
}

//destructor
Matrix::~Matrix(){
    deallocate();
}

//acess methods
int Matrix::getRows() const{
    return row;
}

int Matrix::getCols() const{
    return col;
}

double Matrix::getEntry(const int& rIdx, const int& cIdx) const{
    assert (rIdx >= 0 && cIdx >=0);
    assert (rIdx < row && cIdx < col);
    return entry[rIdx][cIdx];
}

//set methods
void Matrix::setEntry(const int& rIdx, const int& cIdx, const double& val){
    assert (rIdx >= 0 && cIdx >=0);
    assert (rIdx < row && cIdx < col);
    entry[rIdx][cIdx] = val;
}

//initializing methods
void Matrix::zeros() const{
    for (int i = 0; i < row; ++i){
        for (int j =0; j < col; ++j){
            entry[i][j] =0.0;
        }
    }
}
void Matrix::ones() const{
    for (int i = 0; i < row; ++i){
        for (int j =0; j < col; ++j){
            entry[i][j] =1.0;
        }
    }
}
void Matrix::eye() const{
    assert(row == col);
    zeros();
    for(int i = 0; i < row; ++i){
        entry[i][i] = 1.0;
    }
}

void Matrix::random() const{
    for (int i = 0; i < row; ++i){
        for (int j =0; j < col; ++j){
            entry[i][j] = 1+ rand() % 10;
        }
    }
}

void Matrix::print(const string& name) const{
    cout<<name<<": "<<endl;
    for (int i = 0; i < row; ++i){
        for (int j =0; j < col; ++j){
            cout<<entry[i][j]<<", ";
        }
        cout<<endl;
    }
    cout<<endl;
}

//operator methods:
//to get entry
double Matrix::operator()(const int& rIdx, const int& cIdx) const{
    assert (rIdx >= 0 && cIdx >=0);
    assert (rIdx < row && cIdx < col);
    return entry[rIdx][cIdx];
}
//to set entry
double& Matrix::operator()(const int& rIdx, const int& cIdx){
    assert (rIdx >= 0 && cIdx >=0);
    assert (rIdx < row && cIdx < col);
    return entry[rIdx][cIdx]; 
}
//assignment operator
Matrix& Matrix::operator=(const Matrix& mat) {
    // 1. Self-assignment check
    if (this == &mat) return *this;

    // 2. If sizes differ, reallocate memory
    if (row != mat.getRows() || col != mat.getCols()) {
        deallocate(); // Clean up old memory
        row = mat.getRows();
        col = mat.getCols();
        allocate(); // Allocate new size
    }

    // 3. Copy entries
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            entry[i][j] = mat(i, j);
        }
    }
    return *this;
}
//unary operators

//A = -B
Matrix Matrix::operator-() const{
    int r = row; 
    int c = col;
    Matrix nB(r, c);
    nB.zeros();
    //negate entry by entry
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            nB(i,j) = -entry[i][j];
        }
    }
    return nB;
}

//++A
Matrix& Matrix::operator++(){
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
           ++entry[i][j];
        }
    }   
    return *this;
}

//linear algebra
Matrix Matrix::operator+(const Matrix& mat) const{
    //make sure the 2 matrices are of the same size
    assert(row == mat.getRows());
    assert(col == mat.getCols());
    int r = row;
    int c = col;
    Matrix C(r , c);
    //initialize C with all zeros
    C.zeros();

    //add entry by entry
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            C(i,j) = entry[i][j] + mat(i, j);
        }
    }
    //return c
    return C;
}

//C = A-B
Matrix Matrix::operator-(const Matrix& B) const{
    assert(row == B.getRows());
    assert(col == B.getCols());
    int r = row;
    int c = col;
    Matrix C(r, c);
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            C(i,j) = entry[i][j] - B(i,j);
        }
    }
    return C;
}
Matrix Matrix::operator*(const Matrix& mat) const{
    assert(col == mat.getRows());
    int r = row;
    int c = mat.getCols();
    Matrix C (r, c);
    //initialize C with all zeros
    C.zeros();
    //C ij = Sum (Aik + Bkj)
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            for (int k = 0; k < col ; ++k){
                C(i,j) += entry[i][k] * mat(k, j); 
            }
        }
    }
    //return C
    return C;
}

//A +=B
Matrix& Matrix::operator+=(const Matrix& B){
    //make sure the 2 matrices are of the same size
    assert(row == B.getRows());
    assert(col == B.getCols());
    //add up entry  by entry
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            entry[i][j] += B(i , j); 
        }
    }
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& B){
    //make sure the 2 matrices are of the same size
    assert(row == B.getRows());
    assert(col == B.getCols());
    //add up entry  by entry
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            entry[i][j] -= B(i , j); 
        }
    }
    return *this;
}

//A *=alp 
Matrix& Matrix::operator*=(const double& alp){
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            entry[i][j] *= alp;
        }
    }
    return *this;
}
//A *= B
Matrix& Matrix::operator*=(const Matrix& B) {
    if (this->col != B.getRows()) {
        assert(this->col == B.getRows());
    }

    int r = this->row;
    int c = B.getCols();

    Matrix C(r, c);
    C.zeros();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            double sum = 0;
            for (int k = 0; k < this->col; ++k) {
                sum += this->entry[i][k] * B(k, j);
            }
            C(i, j) = sum;
        }
    }


    *this = C;

    return *this;
}


// end of class
//non-member operators
Matrix transpose(const Matrix& A){
    int r = A.getCols();
    int c = A.getRows();
    Matrix C(r,c);
    for (int i = 0; i < c; ++i){
        for (int j = 0; j < r; ++j){
            C(j, i) = A(i, j);
        }
    }
    return C;
}
/*
bool Matrix::isSymmetric() const{
    if(isSquare==1)
    int Flag=1;
    for (int i=0 ; i < row; ++i){
        for (int j= 0; j <col; ++j){
            if (entry[i][j]!= entry[j][i]){
                Flag = 0;
            }
        }
    }
    return Flag;
}
    */

