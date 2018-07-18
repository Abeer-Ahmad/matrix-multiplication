#ifndef ELEMENT_THREADED_H
#define ELEMENT_THREADED_H

typedef struct {
    int row;
    int col;
} Coordinates;

void run_element_threads(const int **A, const int **B, int **C, const int L, const int M, const int N);

void *compute_element(void *coordinates);

#endif
