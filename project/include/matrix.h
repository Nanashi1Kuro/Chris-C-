#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 100

typedef struct Matrix {
    size_t rows;
    size_t cols;
    double pointer_of_matrix[LEN][LEN];
} Matrix;


// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
void free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Custom Math operations
int custom_power(int base, int power);
double math_sum(double l, double r);
double math_sub(double l, double r);
double math_mul(double l, double r);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);
Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

Matrix* del_LineAndSt(const Matrix* matrix, Matrix* temp_matrix,
    size_t pos_of_line, size_t pos_of_st, size_t dimension);
double math_det(const Matrix* matrix, size_t dimension);

#endif  // PROJECT_INCLUDE_MATRIX_H_
