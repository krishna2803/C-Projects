#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

// For documentation, read Matrix.cpp

class Matrix {
    private:
        float *data;
        unsigned char rows, cols;

    public:
        Matrix(unsigned char rows, unsigned char cols);
        Matrix(unsigned char order);
        Matrix(unsigned char rows, unsigned char cols, void* data);
        Matrix();
        ~Matrix();

        float get(unsigned char row, unsigned char col) const;
        const float operator()(unsigned char row, unsigned char col) const;
        void set(unsigned char row, unsigned char col, const float value);
        float& operator()(unsigned char row, unsigned char col);

        void print() const;
        operator char*() const;
        const char* toString();

        static Matrix identity(unsigned char order);
        static Matrix rand(unsigned char rows, unsigned char cols);
        static Matrix rand(unsigned char order);

        Matrix operator+(Matrix that);
        Matrix operator-(Matrix that);
        Matrix operator*(Matrix that);

        Matrix operator+(const float value);
        Matrix operator-(const float value);
        Matrix operator*(const float value);

        Matrix& operator+=(Matrix that);
        Matrix& operator-=(Matrix that);

        Matrix& operator+=(const float value);
        Matrix& operator-=(const float value);
        Matrix& operator*=(const float value);

        Matrix transpose();
        Matrix minor(unsigned char row, unsigned char col);
        const float determinant();
        Matrix adjoint();
        Matrix inverse();
};

#endif
