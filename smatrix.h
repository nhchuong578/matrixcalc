// class SquareMatrix
// - need to declare new features
// - need to define overwritten methods
#ifndef _SMATRIX_
#define _SMATRIX_
#include <string>
#include "matrix.h"


class SquareMatrix: public Matrix {
protected:
    int size;
public:
    //1. constructors
    SquareMatrix(const int& s);
    SquareMatrix(const int& s, const double& val);
    //copy constructor
    SquareMatrix(const SquareMatrix& smat);
    SquareMatrix(const Matrix& mat);
    
    //2. destructor
    virtual ~SquareMatrix();

    //3. assignment operators
    //from square matrix
    SquareMatrix& operator=(const SquareMatrix& smat);
    //from regular matrix
    SquareMatrix& operator=(const Matrix& mat);


    //new methods
    int getSize() const;
    bool isSymmetric() const;
    bool isLowTri() const;
    bool isUpTri() const;

    //overwritten methods
    void print(string name) const;

    //additional methods
    virtual double det() const; 
    bool isInvertible() const;
    SquareMatrix cofactor(const int& p, const int& q) const;
    SquareMatrix adjoint() const;
    SquareMatrix inverse() const;
    int rank(SquareMatrix smat) const;
    Matrix x(SquareMatrix A, Matrix b);
    
};

#endif
