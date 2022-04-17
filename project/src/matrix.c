#include "matrix.h"

Matrix* create_matrix_from_file(const char* path_file) {
    Matrix* matrix;
    matrix = (Matrix*)calloc(1, sizeof(Matrix));
    FILE* from_create = fopen(path_file, "r+");
    fscanf(from_create, "%zu%zu", &matrix->rows, &matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            fscanf(from_create, "%lf", &matrix->pointer_of_matrix[i][j]);
        }
    }
    fclose(from_create);
    return matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* matrix;
    matrix = (Matrix*)calloc(1, sizeof(Matrix));
    matrix->cols = cols;
    matrix->rows = rows;
    for (size_t i = 0; i < LEN; i++) {
        for (size_t j = 0; j < LEN; j++) {
            matrix->pointer_of_matrix[i][j] = 0;
        }
    }
    return matrix;
}

Matrix* copy_matrix_function(const Matrix* matrix, size_t rows, size_t cols) {
    Matrix* copy_matrix;
    copy_matrix = (Matrix*)calloc(1, sizeof(Matrix));
    copy_matrix->cols = cols;
    copy_matrix->rows = rows;
    for (size_t i = 0; i < LEN; i++) {
        for (size_t j = 0; j < LEN; j++) {
            copy_matrix->pointer_of_matrix[i][j] = matrix->pointer_of_matrix[i][j];
        }
    }
    return copy_matrix;
}

void free_matrix(Matrix* matrix) {
    free(matrix);
}


int get_rows(const Matrix* matrix, size_t* rows) {
    * rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    * cols = matrix->cols;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    * val = matrix->pointer_of_matrix[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix->pointer_of_matrix[row][col] = val;
    return 0;
}

// Custom Math

int custom_power(int base, int power) {
    int result = 1;
    for (int i = 1; i <= power; ++i)
        result *= base;
    return result;
}

double math_sum(double l, double r) {
    return l + r;
}
double math_sub(double l, double r) {
    return l - r;
}
double math_mul(double l, double r) {
    return l*r;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    Matrix* mul_scalar_matrix = copy_matrix_function(matrix, matrix->rows, matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            mul_scalar_matrix->pointer_of_matrix[i][j] *= val;
        }
    }
    return mul_scalar_matrix;
}

Matrix* transp(const Matrix* matrix) {
    Matrix* transp_matrix = create_matrix(matrix->cols, matrix->rows);
    for (size_t i = 0; i < matrix->cols; i++) {
        for (size_t j = 0; j < matrix->rows; j++) {
            transp_matrix->pointer_of_matrix[i][j] = matrix->pointer_of_matrix[j][i];
        }
    }
    return transp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l->cols == r->cols && l->rows == r->rows) {
        Matrix* sum_matrix = copy_matrix_function(l, l->rows, l->cols);
            for (size_t i = 0; i < l->rows; i++) {
                for (size_t j = 0; j < l->cols; j++) {
                    sum_matrix->pointer_of_matrix[i][j]
                        = math_sum(l->pointer_of_matrix[i][j], r->pointer_of_matrix[i][j]);
                }
            }
        return sum_matrix;
    }
    return NULL;
}
Matrix* sub(const Matrix* l, const Matrix* r) {
    if (l->cols == r->cols && l->rows == r->rows) {
        Matrix* sub_matrix = copy_matrix_function(l, l->rows, l->cols);
            for (size_t i = 0; i < l->rows; i++) {
                for (size_t j = 0; j < l->cols; j++) {
                    sub_matrix->pointer_of_matrix[i][j]
                    = math_sub(l->pointer_of_matrix[i][j], r->pointer_of_matrix[i][j]);
                }
            }
        return sub_matrix;
    }
    return NULL;
}
Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l->rows == r->cols) {
        Matrix* mul_matrix = create_matrix(l->rows, r->cols);
            for (size_t i = 0; i < l->rows; i++) {
                for (size_t j = 0; j < r->cols; j++) {
                    for (size_t n = 0; n < r->rows; n++)
                        mul_matrix->pointer_of_matrix[i][j] +=
                            math_mul(l->pointer_of_matrix[i][n], r->pointer_of_matrix[n][j]);
            }
        }
        return mul_matrix;
    }
    return NULL;
}

// Extra operations

int det(const Matrix* matrix, double* val) {
    if (matrix->rows == matrix->cols) {
        *val = math_det(matrix, matrix->cols);
        return 0;
    }
    return -1;
}

Matrix* adj(const Matrix* matrix) {
    Matrix* adj_matrix = copy_matrix_function(matrix, matrix->rows, matrix->cols);
    for (size_t i = 0; i < adj_matrix->cols; i++) {
        for (size_t j = 0; j < adj_matrix->rows; j++) {
            Matrix* temp_minor_matrix = copy_matrix_function(adj_matrix, adj_matrix->rows, adj_matrix->cols);
            temp_minor_matrix = del_LineAndSt(matrix, temp_minor_matrix, i, j, adj_matrix->cols);
            adj_matrix->pointer_of_matrix[j][i] =
                math_mul(custom_power(-1, i+j), math_det(temp_minor_matrix, adj_matrix->cols - 1));
            free(temp_minor_matrix);
        }
    }
    return adj_matrix;
}

Matrix* inv(const Matrix* matrix) {
    Matrix* inv_matrix = copy_matrix_function(matrix, matrix->rows, matrix->cols);
    Matrix* adj_matrix = adj(inv_matrix);
    double num_det = math_det(inv_matrix, inv_matrix->cols);
    if (inv_matrix->rows == 1) {
        inv_matrix->pointer_of_matrix[0][0] = 1/inv_matrix->pointer_of_matrix[0][0];
        free(adj_matrix);
        return inv_matrix;
    }
    Matrix* mul_inv_matrix = mul_scalar(adj_matrix, 1/num_det);
    free(inv_matrix);
    free(adj_matrix);
    return mul_inv_matrix;
}

Matrix* del_LineAndSt(const Matrix* matrix, Matrix* temp_matrix,
    size_t pos_of_line, size_t pos_of_st, size_t dimension) {
    size_t ki, kj;
    size_t i = 0;
    for (ki = 0; ki < dimension - 1; ki++) {
        if (ki == pos_of_line) {
            i = 1;
        }
        size_t j = 0;
        for (kj = 0; kj< dimension - 1; kj++) {
            if (kj == pos_of_st) {
                j = 1;
            }
            temp_matrix->pointer_of_matrix[ki][kj] = matrix->pointer_of_matrix[ki + i][kj + j];
        }
    }
    return temp_matrix;
}

double math_det(const Matrix* matrix, size_t dimension) {
    double num_det = 0;
    if (dimension == 1) {
        num_det += matrix->pointer_of_matrix[0][0];
        return num_det;
    }
    if (dimension == 2) {
        double l = math_mul(matrix->pointer_of_matrix[0][0], matrix->pointer_of_matrix[1][1]);
        double r = math_mul(matrix->pointer_of_matrix[0][1], matrix->pointer_of_matrix[1][0]);
        num_det += math_sub(l, r);
        return num_det;
    }
    if (dimension > 2) {
        int power = 1;
        for (size_t i = 0; i < dimension; i++) {
            Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
            temp_matrix = del_LineAndSt(matrix, temp_matrix, i, 0, dimension);
            num_det += power*
                math_mul(matrix->pointer_of_matrix[i][0], math_det(temp_matrix, dimension - 1));
            free(temp_matrix);
            power = -power;
        }
        return num_det;
    }
    return 0;
}
