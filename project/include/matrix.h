#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stddef.h>
#include <stdio.h>
#include "malloc.h"


typedef struct Matrix {
    int rows;
    int cols;
    double** pointer_of_matrix;
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

//Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);

double math_sum(double l, double r);
double math_sub(double l, double r);
double math_mul(double l, double r);

Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

void swap(double *a, double *b);
void swapLine(int* line1, int* line2, int number_of_line);
Matrix* delLine(const Matrix* matrix, int position);
Matrix* delSt(const Matrix* matrix, int position);
double power(double base, int power);
int det(const Matrix* matrix, double* val);
double math_det(const Matrix* matrix);

#endif //_MATRIX_H_
