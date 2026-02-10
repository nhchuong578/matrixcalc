// file: smatrix.cpp
//class SquareMatrix: public Matrix
#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
#include "smatrix.h"
using namespace std;

//constructors
SquareMatrix:: SquareMatrix(const int& s):Matrix(s,s){
   size = s;
}

SquareMatrix:: SquareMatrix(const int& s, const double& val): Matrix(s, s , val){
    size = s;
}

SquareMatrix::SquareMatrix(const SquareMatrix& smat):Matrix(smat.getSize(), smat.getSize()){
    size = smat.getSize();
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            entry[i][j] = smat(i , j); 
        }
    }
}
SquareMatrix::SquareMatrix(const Matrix& mat):Matrix(mat.getRows(), mat.getCols()){
    assert(mat.getRows()== mat.getCols());
    size = mat.getRows();
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            entry[i][j] = mat(i , j); 
        }
    }
}

//destructors
SquareMatrix::~SquareMatrix(){
    //do nothing
}

//3. assignment operators
    //from square matrix
    SquareMatrix& SquareMatrix::operator=(const SquareMatrix& smat){
    //make sure the 2 matrices are of the same size
        assert(size == smat.getSize());
        //assign entry by entry
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                entry[i][j] = smat(i , j); 
            }
        }
        return *this;
    }

    //from regular matrix
    SquareMatrix& SquareMatrix::operator=(const Matrix& mat) {
        // 1. Ensure the incoming matrix is actually square
        assert(mat.getRows() == mat.getCols());

        // 2. Call the base class operator=
        Matrix::operator=(mat);

        // 3. Update the local size member
        this->size = mat.getRows();

        return *this;
    }
//additional methods
int SquareMatrix::getSize() const{
    return size;
}
bool SquareMatrix::isSymmetric() const{
    int Flag=1;
    for (int i=0 ; i < size; ++i){
        for (int j= 0; j <size; ++j){
            if (entry[i][j]!= entry[j][i]){
                Flag = 0;
            }
        }
    }
    return Flag;
}

bool SquareMatrix::isLowTri() const{
    int Flag = 1;
    for (int i = 0; i < size; ++i){
        for (int j = i+1 ; j < size; ++j){
            if(entry[i][j] != 0) Flag = 0;
        }
    }
    return Flag;
}
bool SquareMatrix::isUpTri() const{
    int Flag = 1;
    for (int i = 1; i < size; ++i){
        for (int j = i-1 ; j >= 0 ; --j){
            if(entry[i][j] != 0) Flag = 0;
        }
    }
    return Flag;
}
//virtual double det() const; // virtual --> different for implementations
//bool SquareMatrix::isInvertible() const;
//SquareMatrix inverse() const;

//overwritten methods
void SquareMatrix::print(string name) const{
    cout<<"Square "<<name<<": "<<endl;
    for (int i = 0; i < size; ++i){
        for (int j =0; j < size; ++j){
            cout<<entry[i][j]<<", ";
        }
        cout<<endl;
    }
    cout<<endl;
}


//additional methods
double SquareMatrix::det() const {
	int	size_h(size);	// size of submatrix Ah
	double	result(0.0);

	if (size_h == 1)
		result = entry[0][0];
	else
	{
		size_h = size - 1;
		for (int j = 0; j < size; ++j)
		{
			// form Ah with row 0 and col j removed from A
			SquareMatrix Ah(size_h);
			Ah.zeros();
			for (int ii = 0; ii < size_h; ++ii)
			{
				for (int jj = 0; jj < j; ++jj)
					Ah(ii, jj) = entry[ii + 1][jj];
				for (int jj = j; jj < size_h; ++jj)
					Ah(ii, jj) = entry[ii + 1][jj + 1];
			}
			// recursion
			result += pow(-1.0, j) * entry[0][j] * Ah.det();
		}	// endfor j
	}	// endif

	return result;
}

bool SquareMatrix::isInvertible() const{
    if (det() != 0) return 1;
    else return 0;
}
// cofactor matrix by removing row p and col q
SquareMatrix SquareMatrix::cofactor(const int& p, const int& q) const {
	assert(p > -1 && p < size);
	assert(q > -1 && q < size);		

	Matrix temp(size - 1, size, 0.0);
	// remove row p
	for (int jj = 0; jj < temp.getCols(); ++jj)
	{
		for (int ii = 0; ii < p; ++ii)
			temp(ii, jj) = entry[ii][jj];
		for (int ii = p; ii < temp.getRows(); ++ii)
			temp(ii, jj) = entry[ii+1][jj];
	}

	SquareMatrix co(size - 1, 0.0);

	// remove col q
	for (int ii = 0; ii < co.getSize(); ++ii)
	{
		for (int jj = 0; jj < q; ++jj)
			co(ii, jj) = temp(ii,jj);
		for (int jj = q; jj < co.getSize(); ++jj)
			co(ii, jj) = temp(ii,jj+1);
	}

	return co;
}

SquareMatrix SquareMatrix::adjoint() const {
	SquareMatrix adj(size, 0.0);

	if (size == 1) {
		adj(0, 0) = 1;
		return adj;
	}

	// temp is used to store cofactors of A[][]
	int sign = 1;
	SquareMatrix temp(size-1, 0.0);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Get cofactor of A[i][j]
			temp = cofactor(i, j);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj(j,i) = (sign) * temp.det();
		}
	}

	return adj;
}

SquareMatrix SquareMatrix::inverse() const {
	assert( fabs(det()) > 0.0 );

	// Find adjoint
	SquareMatrix adj = adjoint();

	// Find Inverse using formula inverse(A) = adj(A)/det(A)
	SquareMatrix inv(size, 0.0);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			inv(i,j) = adj(i,j) / det();

	return inv;
}

int SquareMatrix::rank(SquareMatrix smat) const {
    //If a Square Matrix is non-singular, its rank is equal its size
    if (smat.isInvertible()) return smat.getSize();
    //If it is Low-/Up-Tri, its rank is its diagonal entry different from 0
    else if (smat.isLowTri() || smat.isUpTri()) {
        int rank = 0;
        for (int i = 0; i < smat.getSize(); ++i) {
            if (smat(i, i) != 0) rank++;
        }
        return rank;
    }

    else {
        return Matrix::rank(smat);
    }
}

Matrix SquareMatrix::x(SquareMatrix A, Matrix b) {
    assert(A.getSize() == b.getCols());
    assert(b.getRows() == 1);
    Matrix x(1, A.getSize());
    x.zeros();
    if (!A.isInvertible()) {
        cout << "This matrix is singular.The system may have no unique solution" << endl;
        return x;
    }
    x = b * A.inverse();
    return transpose(x);
}
