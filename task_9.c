#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix {
    double **buffer;
    size_t rows;
    size_t columns;
} matrix;

void free_buffer(double **buffer, size_t rows){
    for(size_t i = 0; i < rows; ++i){
        free(buffer[i]);
    }
    free(buffer);
}

int create_matrix(matrix* mx, int read_values){
    if(!mx){
        return FAILURE; // *
    }
    double **buffer = (double**)malloc(mx->rows * sizeof(double *));
    if(!buffer){
        return FAILURE;
    } 
    for(size_t i = 0; i < mx->rows; ++i){
        buffer[i] = (double*)malloc(mx->columns * sizeof(double));
        if(!buffer[i]){
            free_buffer(buffer, i);
            return FAILURE;
        }
        if(read_values){
            for(size_t j = 0; j < mx->columns; ++j){
            scanf("%lf", &buffer[i][j]); // *(buffer + i)
            }
        }
        
    }
    mx->buffer = buffer;
    return SUCCESS;
}

int add_matrix(matrix* first_mx, matrix* second_mx, matrix* result_mx){
    if(!first_mx || !second_mx || first_mx->rows != second_mx->rows || 
    first_mx->columns != second_mx->columns){
        return FAILURE;
    }
    result_mx->rows = first_mx->rows;
    result_mx->columns = first_mx->columns;
    if(!result_mx || !create_matrix(result_mx, 0)){
        return FAILURE;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        for(size_t j = 0; j < first_mx->columns; ++j){
            result_mx->buffer[i][j] = first_mx->buffer[i][j] + second_mx->buffer[i][j];
        }
    }
    return SUCCESS;
}

int sub_matrix(matrix* first_mx, matrix* second_mx, matrix* result_mx){
    if(!first_mx || !second_mx || first_mx->rows != second_mx->rows || 
    first_mx->columns != second_mx->columns){
        return FAILURE;
    }
    result_mx->rows = first_mx->rows;
    result_mx->columns = first_mx->columns;
    if(!result_mx || !create_matrix(result_mx, 0)){
        return FAILURE;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        for(size_t j = 0; j < first_mx->columns; ++j){
            result_mx->buffer[i][j] = first_mx->buffer[i][j] - second_mx->buffer[i][j];
        }
    }
    return SUCCESS;
}

int mult_matrix(matrix* first_mx, matrix* second_mx, matrix* result_mx){
    if(!first_mx || !second_mx || first_mx->columns != second_mx->rows){
        return FAILURE;
    }
    result_mx->rows = first_mx->rows;
    result_mx->columns = second_mx->columns;
    if(!result_mx || !create_matrix(result_mx, 0)){
        return FAILURE;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        for(size_t j = 0; j < second_mx->columns; ++j){
            result_mx->buffer[i][j] = 0;
            for(size_t k = 0; k < first_mx->columns; ++k){
                result_mx->buffer[i][j] += first_mx->buffer[i][k] * second_mx->buffer[k][j];
            }
        }
    }
    return SUCCESS;
}

int transpose_mx(matrix* first_mx, matrix* result_mx){
    if(!first_mx){
        return FAILURE;
    }
    result_mx->rows = first_mx->columns;
    result_mx->columns = first_mx->rows;
    if(!result_mx || !create_matrix(result_mx, 0)){
        return FAILURE;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        for(size_t j = 0; j < first_mx->columns; ++j){
            result_mx->buffer[j][i] = first_mx->buffer[i][j];
        }
    }
    return SUCCESS;
}

int mult_number(matrix* first_mx, double number, matrix* result_mx){
    if(!first_mx){
        return FAILURE;
    }
    result_mx->rows = first_mx->rows;
    result_mx->columns = first_mx->columns;
    if(!result_mx || !create_matrix(result_mx, 0)){
        return FAILURE;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        for(size_t j = 0; j < first_mx->columns; ++j){
            result_mx->buffer[i][j] = first_mx->buffer[i][j] * number;
        }
    }
    return SUCCESS;
}

int eq_matrix(matrix* first_mx, matrix* second_mx, int* result){
    if(!first_mx || !second_mx){
        return FAILURE;
    }
    if(first_mx->rows != second_mx->rows || 
    first_mx->columns != second_mx->columns){
        *result = 0;
        return SUCCESS;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        for(size_t j = 0; j < first_mx->columns; ++j){
            if(first_mx->buffer[i][j] != second_mx->buffer[i][j]){
                *result = 0;
                return SUCCESS;
            }
        }
    }
    *result = 1;
    return SUCCESS;
}

int calc_complements(matrix* first_mx, matrix* result_mx){
    
}

matrix* get_mx(matrix* first_mx, size_t row, size_t columns){
    if(!first_mx){
        return FAILURE;
    }
    matrix* result_mx = (matrix*)malloc(sizeof(matrix));
    if(!result_mx){
        return NULL;
    }
    result_mx->rows = first_mx->rows - 1;
    result_mx->columns = first_mx->columns - 1;
    if(!create_matrix(&result_mx, 0)){
        return NULL;
    }
    for(size_t i = 0; i < first_mx->rows; ++i){
        if(i < row){
            for(size_t j = 0; j < first_mx->columns; ++j){
                if(j < columns){
                    result_mx->buffer[i][j] = first_mx->buffer[i][j];
                } 
                else if(j > columns){
                    result_mx->buffer[i][j - 1] = first_mx->buffer[i][j];
                }
                
            }
        } else if(i > row){
            for(size_t j = 0; j < first_mx->columns; ++j){
                if(j < columns){
                    result_mx->buffer[i - 1][j] = first_mx->buffer[i][j];
                } else if(j > columns){
                    result_mx->buffer[i - 1][j] = first_mx->buffer[i][j];
                }
                
            }
        }
        
    }
    return result_mx;

}

int determinant(matrix* first_mx, double *result){
    if(!first_mx){
        return FAILURE;
    }
    if(first_mx->rows != first_mx->columns){
        return FAILURE;
    }
    if(first_mx->rows == 1){
        *result = first_mx->buffer[0][0];
        return SUCCESS;
    } else {
        double determinant = 0;
        for(size_t i = 0; i < first_mx->columns; ++i){
            if(first_mx->buffer[0][i] != 0){
                determinant += first_mx->buffer[0][i] * determinant(get_mx(first_mx, ))
            }
        }

    }

}

int inverse_matrix(matrix* first_mx, matrix* result_mx){

}

void delete_matrix(matrix *mx){
    free_buffer(mx->buffer, mx->rows);
}

void print_matrix(matrix *mx){
    for(size_t i = 0; i < mx->rows; ++i){
        for(size_t j = 0; j < mx->columns; ++j){
            printf("%.2lf ", mx->buffer[i][j]);
        }
        printf("\n");
    }
}
int main(){
    int read_values = 1;
    int result = 0;
    //double number = 2.0;
    size_t rows, columns;
    scanf("%zu %zu", &rows, &columns);
    matrix* first_mx = (matrix*)malloc(sizeof(matrix));
    matrix* second_mx = (matrix*)malloc(sizeof(matrix));
    matrix* result_mx = (matrix*)malloc(sizeof(matrix));
    first_mx->rows = rows;
    first_mx->columns = columns;
    second_mx->rows = rows;
    second_mx->columns = columns;
    result_mx->rows = rows;
    result_mx->columns = columns;
    if(create_matrix(first_mx, read_values) == FAILURE || create_matrix(second_mx, read_values) == FAILURE
    /*|| create_matrix(result_mx, 0) == FAILURE*/){
        return -1;
    } 
   // add_matrix(first_mx, second_mx, result_mx);
    //mult_matrix(first_mx, second_mx, result_mx);
    //transpose_mx(first_mx, result_mx);
    //mult_number(first_mx, number, result_mx);
    eq_matrix(first_mx, second_mx, &result);
    //print_matrix(result_mx);
    printf("%d\n", result);
}