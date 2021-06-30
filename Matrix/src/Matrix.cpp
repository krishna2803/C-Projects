#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Matrix.hpp"

// initilaize as a (rows x cols) matrix
Matrix::Matrix(unsigned char rows, unsigned char cols) : rows(rows), cols(cols) {
    data = new float[rows * cols];
}

// initilize as a square matrix
Matrix::Matrix(unsigned char order) : rows(order), cols(order){
    data = new float[order * order];
}

// empty constructor so that
// a matrix can be initialized as Matrix mat;
// NOTE: REMEMBER to properly initilaize `mat` afterwards
//       it can cause segmentation faults if not done.
Matrix::Matrix() {
}

Matrix::~Matrix() {
    // there's no need to delete [] data;
}

// create a matrix from a data
Matrix::Matrix(unsigned char rows, unsigned char cols, void* data) : rows(rows), cols(cols) {
    this->data = (float*) data;
}

// get (row, col) element of this matrix
float Matrix::get(unsigned char row, unsigned char col) const {
    return data[row*cols+col];
}

// get [row-1][col-1] element of this matrix
const float Matrix::operator()(unsigned char row, unsigned char col) const {
    row-=1; col-=1;
    return data[col*rows+col];
}

// set (row, col) element of this matrix
void Matrix::set(unsigned char row, unsigned char col, const float value) {
    data[row*cols+col] = value;
}
// set [row-1][col-1] element of this matrix
float& Matrix::operator()(unsigned char row, unsigned char col) {
    row-=1; col-=1;
    return data[row*cols+col];
}

// print this matrix to stdout
void Matrix::print() const {
    for (unsigned char i = 0; i < rows; i++) {
        for (unsigned char j = 0; j < cols; j++) {
            printf("%.2f\t", get(i, j));
        }
        printf("\n");
    }
}

// convert this matrix to (const char*)
// can be used for printing more than two decimal places
Matrix::operator char*() const {
    // 12 bytes for each element (should be enough)
    char* buffer = new char[rows * cols * 12 + 1];
    for (unsigned char i = 0; i < rows; i++) {
        for (unsigned char j = 0; j < cols; j++) {
            sprintf(buffer+strlen(buffer), "%f ", get(i, j));
        }
        sprintf(buffer+strlen(buffer), "\n");
    }
    sprintf(buffer+strlen(buffer), "\0");
    return buffer;
}

// convert this matrix to (const char*)
// can be used for printing more than two decimal places
const char* Matrix::toString() {
    return (const char*) *this;
}

// return an (N x N) identity matrix
Matrix Matrix::identity(unsigned char order) {
    Matrix mat(order, order);
    for (int i=0; i<order; i++)
        mat.set(i, i, 1.0f);
    return mat;
}

// return a random (rows x cols) normalised matrix
// NOTE: random() is not seeded!
Matrix Matrix::rand(unsigned char rows, unsigned char cols) {
    const float k_inverseRandMax = 1.0f / RAND_MAX;
    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            mat.set(i, j, random()*k_inverseRandMax);
    return mat;
}

// return a random (order x order) normalised matrix
// NOTE: random() is not seeded!
Matrix Matrix::rand(unsigned char order) {
    return Matrix::rand(order, order);
}


// add a scalar to all elements
Matrix Matrix::operator+(const float value) {
    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            mat.set(i, j, get(i, j)+value);
    return mat;
}

// subtract scalar from all elements
Matrix Matrix::operator-(const float value) {
    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            mat.set(i, j, get(i, j)-value);
    return mat;
}

// multipy all elements of a matrix by some value
Matrix Matrix::operator*(const float value) {
    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            mat.set(i, j, get(i, j) * value);
    return mat;
}

// add two matrices
Matrix Matrix::operator+(Matrix that) {
    if (this->rows != that.rows || this->cols != that.cols) {
        fprintf(stderr, "Dimension Mismatch (%ux%u) and (%ux%u).\n", this->rows, this->cols, that.rows, that.cols);
        throw "Dimension Mismatch.\n";
    }
    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            mat.set(i, j, this->get(i, j) + that.get(i, j));
    
    return mat;
}

// subtract two matrices
Matrix Matrix::operator-(Matrix that) {
    if (this->rows != that.rows || this->cols != that.cols) {
        fprintf(stderr, "Dimension Mismatch (%ux%u) and (%ux%u).\n", this->rows, this->cols, that.rows, that.cols);
        throw "Dimension Mismatch.\n";
    }
    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            mat.set(i, j, this->get(i, j) - that.get(i, j));
    
    return mat;
}

// multiply two matrices
// OPIMIZATIONS NEEDED
Matrix Matrix::operator*(Matrix that) {
    if (this->cols != that.rows) {
        fprintf(stderr, "Dimension Mismatch (%ux%u) and (%ux%u).\n", this->rows, this->cols, that.rows, that.cols);
        throw "Dimension Mismatch.\n";
    }
    Matrix mat(this->rows, that.cols);
    for (unsigned char i=0; i<mat.rows; i++)
    for (unsigned char j=0; j<mat.cols; j++)
    for (unsigned char k=0; k < cols; k++)
        mat.set(i,j,mat.get(i,j)+this->get(i, k)*that.get(k,j));
    return mat;
}

// add a matrix to this matrix
Matrix& Matrix::operator+=(Matrix that) {
    if (this->rows != that.rows || this->cols != that.cols) {
        fprintf(stderr, "Dimension Mismatch (%ux%u) and (%ux%u).\n", this->rows, this->cols, that.rows, that.cols);
        throw "Dimension Mismatch.\n";
    }
    for (unsigned char i = 0; i < rows; i++)
        for (unsigned char j = 0; j < cols; j++)
            set(i, j, get(i, j) + that.get(i, j));
    return *this;
}

// subtract a matrix from this matrix
Matrix& Matrix::operator-=(Matrix that) {
    if (this->rows != that.rows || this->cols != that.cols) {
        fprintf(stderr, "Dimension Mismatch (%ux%u) and (%ux%u).\n", this->rows, this->cols, that.rows, that.cols);
        throw "Dimension Mismatch.\n";
    }
    for (unsigned char i = 0; i < rows; i++)
        for (unsigned char j = 0; j < cols; j++)
            set(i, j, get(i, j) - that.get(i, j));
    return *this;
}

// add a scalar to all elements of this matrix
Matrix& Matrix::operator+=(const float value) {
    for (unsigned char i = 0; i < rows; i++)
        for (unsigned char j = 0; j < cols; j++)
            set(i, j, get(i, j)-value);
    return *this;
}

// subtract a scalar from all elements of this matrix
Matrix& Matrix::operator-=(const float value) {
    for (unsigned char i = 0; i < rows; i++)
        for (unsigned char j = 0; j < cols; j++)
            set(i, j, get(i, j)-value);
    return *this;
}

// multiply all elements of this matrix by a scalar
Matrix& Matrix::operator*=(const float value) {
    for (unsigned char i=0; i<rows; i++)
        for (unsigned char j=0; j<cols; j++)
            set(i, j, get(i, j) * value);
    return *this;
}

// returns the minor (as a matrix) of an element in a matrix
Matrix Matrix::minor(unsigned char row, unsigned char col) {
    if (cols != rows) {
        fprintf(stderr, "Cannot calculate minor of a non-square matrix");
        throw "Non-square matrix\n";
    }
    Matrix mat(rows-1, cols-1);

    unsigned char m_i=0, m_j=0;
    for (unsigned char i=0; i<rows; i++)
    for (unsigned char j=0; j<cols; j++) {
        if (i == row || j == col) continue;
        mat.set(m_i, m_j++, get(i, j));
        if (m_j == cols-1) {
            m_j = 0;
            m_i++;
        }
    }
    return mat;
}

// returns the transpose of this matrix
Matrix Matrix::transpose() {
    Matrix mat(cols, rows);
    for (unsigned char i=0; i<mat.rows; i++)
        for (unsigned char j=0; j<mat.cols; j++)
            mat.set(i, j, get(j, i));
    return mat;
}

// calculates and returns determinant of the matrix
// OPIMIZATIONS NEEDED
const float Matrix::determinant() {
    if (cols != rows) {
        fprintf(stderr, "Cannot calculate determinant of a non-square matrix");
        throw "Non-square matrix\n";
    }
    
    if (cols == 1)
        return get(0,0);

    if (cols == 2)
        return get(0,0)*get(1,1)-get(0,1)*get(1,0);

    
    if (cols == 3)
        return get(0,0)*(get(1,1)*get(2,2)-get(2,1)*get(1,2))
              -get(0,1)*(get(1,0)*get(2,2)-get(2,0)*get(1,2))
              +get(0,2)*(get(1,0)*get(2,1)-get(2,0)*get(1,1));

    float det = 0.0f;
    for (unsigned char col=0; col<cols; col++) 
        det += get(0, col) * minor(0, col).determinant() * (1-(col&1)*2);

    return det;
}

// calculates and returns adjoint of the matrix
// OPIMIZATIONS NEEDED
Matrix Matrix::adjoint() {
    if (cols != rows) {
        fprintf(stderr, "Cannot calculate adjoint of a non-square matrix");
        throw "Non-square matrix\n";
    }

    Matrix mat(rows, cols);
    for (unsigned char i=0; i<rows; i++)
    for (unsigned char j=0; j<cols; j++) {
        // (i+j)&1 returns 1 if it is odd, 0 otherwise
        // (1-((i+j)&1)*2) => if (i+j) is even, multiply by 1 else multiply by -1
        float val = minor(i, j).determinant() * (1-((i+j)&1)*2);
        if (val != 0.0f)
            mat.set(j, i, val);
    }
    return mat;
}

// calculates and returns inverse of the matrix
// OPIMIZATIONS NEEDED
Matrix Matrix::inverse() {
    if (cols != rows) {
        fprintf(stderr, "Cannot calculate inverse of a non-square matrix");
        throw "Non-square matrix\n";
    }
    float det = 0.0f;
    Matrix mat(rows, cols);

    if (rows == 1) {
        det = get(0, 0);
        if (det == 0.0f) {
            fprintf(stderr, "Cannot calculate inverse of a singular matrix");
            throw "singular matrix\n";
        }
        mat.set(0, 0, get(0, 0) / det);
        return mat;
    }

    if (rows == 2) {
        det = get(0,0)*get(1,1)-get(0,1)*get(1,0);
        if (det == 0.0f) {
            fprintf(stderr, "Cannot calculate inverse of a singular matrix");
            throw "Singular matrix\n";
        }
        mat.set(0, 0, get(1, 1));
        mat.set(1, 1, get(0, 0));
        mat.set(0, 1,-get(0, 1));
        mat.set(1, 0,-get(1, 0));
        mat *= 1.0f / det;
        return mat;
    }

    for (unsigned char i=0; i<rows; i++)
    for (unsigned char j=0; j<cols; j++) {
        // (i+j)&1 returns 1 if it is odd, 0 otherwise
        // (1-((i+j)&1)*2) => if (i+j) is even, multiply by 1 else multiply by -1
        float val = minor(i, j).determinant()*(1-((i+j)&1)*2);
        if (!i) det += val * get(0, j);
        if (val != 0.0f) mat.set(j, i, val);
    }
    if (det == 0.0f) {
        fprintf(stderr, "Cannot calculate inverse of a singular matrix");
        throw "Singular matrix\n";
    }
    return mat * (1.0f / det);
}
