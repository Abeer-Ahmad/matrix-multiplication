#include <stdlib.h>
#include "matrix_formatter.h"

void set_matrix_struct(Matrix *matrix, char *line);
void set_dimensions(Matrix *matrix, char *line);
int **allocate_matrix(int rows, int cols);
void read_row(int **matrix, char *line, int cols, int i);

Matrix *read_matrix(FILE *file) {
    Matrix *matrix = malloc(sizeof (Matrix));
    size_t max_bytes = 1000; // arbitrary number, getline() will do the realloc() all by itself
    char *line = (char *)malloc(max_bytes);
    getline(&line, &max_bytes, file); // read the first line describing the matrix dimensions
    set_matrix_struct(matrix, line);
    int i = 0;
    while (getline(&line, &max_bytes, file) != -1) // EOF reached
        read_row(matrix->content, line, matrix->cols, i++);
    free(line);
    return matrix;
}

void write_matrix(FILE *file, int **matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols - 1; j++)
            fprintf(file, "%d\t", matrix[i][j]);
        fprintf(file, "%d\n", matrix[i][j]);
    }
}

void set_matrix_struct(Matrix *matrix, char *line) {
    set_dimensions(matrix, line);
    matrix->content = allocate_matrix(matrix->rows, matrix->cols);
}

void set_dimensions(Matrix *matrix, char *line) {
    char *p = line + 4; // skipping the "row="
    matrix->rows = strtol(p, &p, 0); // now p points to the ' '
    p += 5; // skipping the " col="
    matrix->cols = strtol(p, &p, 0);
}

int **allocate_matrix(int rows, int cols) {
    int **matrix = (int **) malloc(rows * cols * sizeof (int));
    for (int i = 0; i < rows; i++)
        matrix[i] = malloc(cols * sizeof (int));
    return matrix;
}

void read_row(int **matrix, char *line, int cols, int i) {
    char *p = line;
    for (int j = 0; j < cols; ++j)
        matrix[i][j] = strtol(p, &p, 0);
}