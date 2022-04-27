#include "matrix.h"
#include "exceptions.h"

namespace prep {

    explicit Matrix::Matrix(size_t rows = 0, size_t cols = 0) {
        this->pointer_of_matrix = new double*[this->rows];
        this->cols = cols;
        this->rows = rows;
        for (size_t i = 0; i < rows; i++) {
            this->pointer_of_matrix[i] = new double[cols];
            for (size_t j = 0; j < cols; j++) {
                this->pointer_of_matrix[i][j] = 0;
            }
        }
    }

    explicit Matrix::Matrix(std::istream& is) {
        pointer_of_matrix = new double*[rows];
        is >> rows;
        is >> cols;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                is >> pointer_of_matrix[i][j];
            }
        }
    }

    Matrix::Matrix(const Matrix& rhs) = default;
    Matrix::Matrix& operator=(const Matrix& rhs) = default;

    Matrix::~Matrix() {
        for(size_t i = 0; i < rows; i++) {
            delete [] pointer_of_matrix[i];
        }
        delete [] pointer_of_matrix;
    }

    size_t Matrix::getRows() const{
        return this->rows;
    }

    size_t Matrix::getCols() const{
        return this->cols;
    }

    double Matrix::operator()(size_t i, size_t j) const{
        return this->pointer_of_matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j){
        return this->pointer_of_matrix[i][j];
    }

    bool Matrix::operator==(const Matrix& rhs) const{
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                if (this->pointer_of_matrix[i][j] != rhs(i,j)){
                    return 0;
                }
            }
        }
        return 1;
    }

    bool Matrix::operator!=(const Matrix& rhs) const{
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                if (this->pointer_of_matrix[i][j] != rhs(i,j)){
                    return 1;
                }
            }
        }
        return 0;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const{
        Matrix temp = Matrix();
        size_t r_cols = rhs.getCols();
        size_t r_rows = rhs.getRows();
        if (r_cols == this->cols && this->rows == r_rows) {
            for (size_t i = 0; i < r_rows; i++) {
                for (size_t j = 0; j < r_cols; j++) {
                    temp.pointer_of_matrix[i][j] = this->pointer_of_matrix[i][j] + rhs(i,j);
                }
            }
            return temp;
        }
    }

    
    Matrix Matrix::operator-(const Matrix& rhs) const{
       Matrix temp = Matrix();
        size_t r_cols = rhs.getCols();
        size_t r_rows = rhs.getRows();
        if (r_cols == this->cols && this->rows == r_rows) {
            for (size_t i = 0; i < r_rows; i++) {
                for (size_t j = 0; j < r_cols; j++) {
                    temp.pointer_of_matrix[i][j] = this->pointer_of_matrix[i][j] - rhs(i,j);
                }
            }
            return temp;
        } 
    }

    Matrix Matrix::operator*(const Matrix& rhs) const{
        Matrix temp = Matrix();
        size_t r_cols = rhs.getCols();
        size_t r_rows = rhs.getRows();
        if (r_cols == this->cols && this->rows == r_rows) {
            for (size_t i = 0; i < r_rows; i++) {
                for (size_t j = 0; j < r_cols; j++) {
                    temp.pointer_of_matrix[i][j] = this->pointer_of_matrix[i][j] * rhs(i,j);
                }
            }
            return temp;
        }   
    }

    Matrix Matrix::operator*(double val) const{
        Matrix temp = Matrix();
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                temp.pointer_of_matrix[i][j] *= val;
            }
        }
        return temp;
    }

    Matrix Matrix::transp() const{
        Matrix temp = Matrix();
        for (size_t i = 0; i < this->cols; i++) {
            for (size_t j = 0; j < this->rows; j++) {
                temp.pointer_of_matrix[i][j] = this->pointer_of_matrix[j][i];
            }
        }
        return temp;
    }
    double Matrix::det() const;
    Matrix Matrix::adj() const;
    Matrix Matrix::inv() const;

}





// Extra operations

/*int det(const Matrix* matrix, double* val) {
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
}*/