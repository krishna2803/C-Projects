# Matrix
Simple C++ matrix class with basic operator overloaded matrix operations.

## Features
&#x2705; Square and Non-Square Matrices  
&#x2705; Matrix-Matrix addition, subtraction and multiplication  
&#x2705; Matrix-Scalar addition, subtraction and multiplication  
&#x2705; Determinant, Adjoint and Inverse calculation  
&#x2705; Operator Overloaded  
&#x2705; Method documentation

## Before you use
- This library is not recommended for use in large projects. The algorithms I've used are very basic and inefficient for that. I might improve the algorithms in the future.
- I've used `unsigned char` for rows and columns of a Matrix object which limits their maximum value to `255`. Anything above that would be impractical considering `O(n³)` time complexity of both multiplication and recursive determinant algorithm.

## Usage
Can be used by including `Matrix.hpp` in you project. Also, remember to compile `Matrix.cpp` with other files. `Matrix.o` can be used alternatively.

## Operators
* ##### Addition
```ruby
  Matrix mat1(3, 2);
  Matrix mat2(3, 2);
  
  Matrix mat3 = mat1 + mat2; // Matrix
  Matrix mat4 = mat3 + 2.0f; // Scalar
  
  mat4 += mat3; // Matrix
  mat4 += 6.7f; // Scalar
```

* ##### Subtraction
```ruby
  Matrix mat1(3, 2);
  Matrix mat2(3, 2);
  
  Matrix mat3 = mat1 - mat2; // Matrix
  Matrix mat4 = mat3 - 6.9f; // Scalar
  
  mat4 -= mat3; // Matrix
  mat4 -= 7.0f;  // Scalar
```

* ##### Multiplication
```ruby
  Matrix mat1(3, 2);
  Matrix mat2(2, 5);
  
  Matrix mat3 = mat1 * mat2; // Matrix
  Matrix mat4 = mat3 * 0.5f; // Scalar
  
  mat4 *= Matrix::random(5, 3); // Matrix
  mat4 *= 4.9f;                 // Scalar
```

- ##### Miscellaneous
```cpp
	Matrix mat1 = Matrix::random(2, 3); // a random 3x2 matrix
    Matrix mat2 = Matrix::random(2, 3); // a random 2x3 matrix
    
    Matrix mat3 = mat1 * mat2.transpose(); // transpose and multiply
    mat3.print();                          // prints mat3 to stdout

    Matrix mat4 = Matrix::identity(4); // 4x4 identity matrix
    mat4 *= Matrix::random(4);
    
    float det = mat4.determinant(); // determinant

  	Matrix mat5 = mat4.adjoint();   // adjoint

    mat3(1,2) = 4.0f;               // sets [0][1] element = 4.0
    							    // same as mat.set(0,1,4.0f)

    float val = mat3.get(0,1);      // gets [0][1] element
    							    // same as mat.get(0,1)

    // NOTE: mat(i,j) and mat.get(i,j) are different.
	// mat.get(i,j) is 0 indexed while mat(i,j) is 1 indexed

    mat3 = mat3.inverse(); 				 // inverse
	char *inverseMat3 = mat3.toString(); // converts to string
```

###### developed by **@krishna2803**