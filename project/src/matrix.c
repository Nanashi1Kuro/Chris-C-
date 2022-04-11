#include "matrix.h"

Matrix* create_matrix_from_file(const char* path_file){
    Matrix matrix;
    FILE* from_create = fopen(path_file, "r+");
    fscanf("%i%i", matrix.rows, matrix.cols);
    matrix.pointer_of_matrix = (double**)calloc(matrix.cols, sizeof(double*));
    for(int i = 0; i < matrix.rows; i++ ){
        matrix.pointer_of_matrix[i] = calloc(matrix.rows, sizeof(double));
        for(int j = 0; j < matrix.cols; j++){
            matrix.pointer_of_matrix[i][j] = scanf("%d", 2, from_create);
        }
    }
    return &matrix;
}

Matrix* create_matrix(size_t rows, size_t cols){
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    matrix.pointer_of_matrix = (double**)calloc(matrix.cols, sizeof(double*));
    for(int i = 0; i < matrix.rows; i++ ){
        matrix.pointer_of_matrix[i] = calloc(matrix.rows, sizeof(double));
        for(int j = 0; j < matrix.cols; j++){
            scanf_s("%d", matrix.pointer_of_matrix[i][j]);
        }
    }
    return &matrix;
}

void free_matrix(Matrix* matrix){
    for(int i = 0; i < matrix->rows; i++ ){
        free(matrix->pointer_of_matrix[i]);
    }
    free(matrix->pointer_of_matrix);
}


int get_rows(const Matrix* matrix, size_t* rows){
    * rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols){
    * cols = matrix->cols;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val){
    * val = matrix->pointer_of_matrix[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val){
    matrix->pointer_of_matrix[row][col] = val;
    return 0;
}

//Math operations
Matrix* mul_scalar(const Matrix* matrix, double val){
    Matrix* mul_scalar_matrix = create_matrix(matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            mul_scalar_matrix->pointer_of_matrix[i][j] *= val; 
        }
    }
    return mul_scalar_matrix;    
}

Matrix* transp(const Matrix* matrix){
    Matrix* trancp_matrix = create_matrix(matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            matrix->pointer_of_matrix[i][j] = trancp_matrix->pointer_of_matrix[j][i];
        }
    }
    return trancp_matrix;
}

double math_sum(double l, double r){
    return l + r;
}
double math_sub(double l, double r){
    return l - r;
}
double math_mul(double l, double r){
    return l*r;
}

Matrix* sum(const Matrix* l, const Matrix* r){
    if (l->cols == r->cols && l->rows == r->rows){
        Matrix* sum_matrix = create_matrix(l->rows, l->cols);
            for (int i = 0; i < l->rows; i++){
                for(int j = 0; j < l->cols; j++){
                    sum_matrix->pointer_of_matrix[i][j] = math_sum(l->pointer_of_matrix[i][j], r->pointer_of_matrix[i][j]);
                }
            }
        return sum_matrix;   
    }
    return NULL;
}
Matrix* sub(const Matrix* l, const Matrix* r){
    if (l->cols == r->cols && l->rows == r->rows){
        Matrix* sub_matrix = create_matrix(l->rows, l->cols);
            for (int i = 0; i < l->rows; i++){
                for(int j = 0; j < l->cols; j++){
                    sub_matrix->pointer_of_matrix[i][j] = math_sub(l->pointer_of_matrix[i][j], r->pointer_of_matrix[i][j]);
                }
            }
        return sub_matrix;   
    }
    return NULL;
}
Matrix* mul(const Matrix* l, const Matrix* r){
    if(l->rows == r->cols){
        Matrix* mul_matrix = create_matrix(l->rows, r->cols);
            for (int i = 0; i < r->cols; i++){
                for(int j = 0; j < l->rows; j++){
                    mul_matrix->pointer_of_matrix[i][j] = math_mul(l->pointer_of_matrix[i][j], r->pointer_of_matrix[i][j]);
            }
        }
        return mul_matrix; 
    }
    return NULL;
}

// Extra operations
void swap(double *a, double *b){
    double t = *a;
    *a = *b;
    *b = t;
}

void swapLine(int* line1, int* line2, int number_of_line){
    for (int i = 0; i < number_of_line; i++){
        swap(line1[i], line2[i]);
    }
}

Matrix* delLine(const Matrix* matrix, int position){
    Matrix* matrix_with_delLine = create_matrix(matrix->rows - 1, matrix->cols);
    for (int i = position; i < matrix->rows - 1; i++){
        swapLine(matrix->pointer_of_matrix[i],matrix->pointer_of_matrix[i+1], matrix->cols);
    }
    for (int i = 0; i > matrix->rows - 1; i++){
        for(int j = 0; j > matrix->cols; j++){
            matrix->pointer_of_matrix[i][j] = matrix_with_delLine->pointer_of_matrix[i][j];
        }
    }
    return matrix_with_delLine;
}

Matrix* delSt(const Matrix* matrix, int position){
    Matrix* matrix_with_delSt = create_matrix(matrix->rows, matrix->cols - 1);
    for (int i = 0; i < matrix->rows; i++){
        for (int j = position; j < matrix->cols - 1; j++){
            swap(&(matrix->pointer_of_matrix[i][j]), &(matrix->pointer_of_matrix[i][j + 1]));
        }
    }
    for (int i = 0; i > matrix->rows; i++){
        for(int j = 0; j > matrix->cols - 1; j++){
            matrix->pointer_of_matrix[i][j] = matrix_with_delSt->pointer_of_matrix[i][j];
        }
    }
    return matrix_with_delSt;

}

double power(double base, int power) {
    double result = 1;
    for (int i = 1; i <= power; ++i)
        result *= base;
    return result;
}

int det(const Matrix* matrix, double* val){
    if(matrix->rows == matrix->cols){
        * val = math_det(matrix);
        return 0;
    }
    return -1;
}

double math_det(const Matrix* matrix){
    double num_det = 0;
    if(matrix->cols == 0){
        return matrix->pointer_of_matrix[0][0];
    }
    if(matrix->cols == 1){
        double l = math_mul(matrix->pointer_of_matrix[0][0], matrix->pointer_of_matrix[0][1]);
        double r = math_mul(matrix->pointer_of_matrix[0][1], matrix->pointer_of_matrix[1][0]);
        num_det = math_sub(l, r);
        return num_det;
    }
    if(matrix->cols > 1){
        for(int j = 0; j < matrix->cols; j++){
            Matrix* temp_matrix = create_matrix(matrix->rows, matrix->cols);
            temp_matrix = delLine(temp_matrix, 0);
            temp_matrix = delSt(temp_matrix, j);
            num_det += power(-1, 1+j)* math_mul(matrix->pointer_of_matrix[1][j], math_det(temp_matrix));
        }
        return num_det;
    }
    return num_det;
}


Matrix* adj(const Matrix* matrix){
    Matrix* adj_matrix = create_matrix(matrix->rows, matrix->cols);
    for (int i = 0; i < adj_matrix->cols; i++){
        for(int j = 0; j < adj_matrix->rows; j++){
            Matrix* temp_minor_matrix = create_matrix(matrix->rows, matrix->cols);
            temp_minor_matrix = delLine(temp_minor_matrix, i);
            temp_minor_matrix = delSt(temp_minor_matrix, j);
            double minor = math_det(temp_minor_matrix);
            adj_matrix->pointer_of_matrix[i][j] = math_mul(power(-1, i+j), minor);
        }
    }
    return adj_matrix;
}

Matrix* inv(const Matrix* matrix){
    Matrix* inv_matrix = create_matrix(matrix->rows, matrix->cols);
    double det = math_det(inv_matrix);
    Matrix* adj_matrix = adj(inv_matrix);
    return mul_scalar(adj_matrix, det);
}
