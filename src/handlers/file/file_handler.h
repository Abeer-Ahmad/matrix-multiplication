#include "../matrix/matrix_formatter.h"

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

Matrix *read_input_file(char *path);

void write_output_file(char *path, int **matrix, int rows, int cols);

#endif
