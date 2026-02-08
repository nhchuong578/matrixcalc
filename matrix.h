#ifndef _MATRIX_
#define _MATRIX_
#include <string>
using namespace std;
class SquareMatrix;
class Matrix{
//member data
protected: 
    int row;
    int col;
    double **entry; 

    //for internal use ONLY
    void allocate();
    void deallocate();

//member methods
public:
    //constructors
    Matrix(const int& r, const int& c); 
    Matrix(const int& r, const int& c, const double &val); // set all entries to val
    Matrix(const Matrix& mat_); // copy constructor

    //destructor
    virtual ~Matrix();

    //access methods
    int getRows() const;
    int getCols() const;
    double getEntry(const int& rIdx, const int& cIdx) const;

    
    //set methods
    void setEntry(const int& rIdx, const int& cIdx, const double& val);
    
    //initializing methods
    void zeros() const;
    virtual void ones() const; // virtual
    void eye() const;
    virtual void random() const; // virtual
    void print(const string& name) const;

    //operator methods
    double operator()(const int& rIdx, const int& cIdx) const;
    double& operator()(const int& rIdx, const int& cIdx);

    Matrix& operator=(const Matrix& mat);

    //A = -B
    //A: return
    //B: caller and input
    Matrix operator-() const;

    //C = A -B
    Matrix operator-(const Matrix& B) const;

    //++A
    //A:return caller and input
    Matrix& operator++();

    //A+=B
    //caller: A
    //input B
    //return A
    Matrix& operator+=(const Matrix& B);

    //A-=B
    Matrix& operator-=(const Matrix& B);

    //A*=alp
    Matrix& operator*=(const double& alp);

    //linear algebra operators
    // C = A + B 
    // C: return
    // A: caller
    // B: input

    Matrix operator+(const Matrix& mat) const;

    //matrix-matrix multiplication
    //E = A*D
    //E: return
    //A: caller
    //D: input
    
    Matrix operator*(const Matrix& mat) const;

    //A *= B
    //A: return
    //A:caller
    //B: input
    Matrix& operator*=(const Matrix& B);

    // new methods (lab 5)
    SquareMatrix isSquare() const;
}; // end of class 

//non-member operator
//B = transpose(A);
//B: return
//A: caller and input
Matrix transpose(const Matrix& A);



    
    
#endif