#ifndef MATRIX_READER_H
#define MATRIX_READER_H

#include <stdio.h>

typedef struct {
    int rows;
    int cols;
    int **content;
} Matrix;

Matrix *read_matrix(FILE *file);

void write_matrix(FILE *file, int **matrix, int rows, int cols);

#endif
