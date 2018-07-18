#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <stdlib.h>
#include "file_handler.h"

Matrix *read_input_file(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }
    Matrix *matrix = read_matrix(file);
    fclose(file);
    return matrix;
}

void write_output_file(char *path, int **matrix, int rows, int cols) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }
    write_matrix(file, matrix, rows, cols);
    fclose(file);
}