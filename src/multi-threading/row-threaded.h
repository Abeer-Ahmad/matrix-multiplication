#ifndef ROW_THREADED_H
#define ROW_THREADED_H

void run_row_threads(const int **A, const int **B, int **C, const int L, const int M, const int N);

void *compute_row(void *row);

#endif
