#include "element_threaded.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int **M1, **M2; // M1, M2 are the two input matrices.
int **M3; // M3 is the output matrix
int m; // M1 is l × m, M2 is m × n

Coordinates *set_coordinates(int i, int j);

void run_element_threads(const int **A, const int **B, int **C, const int L, const int M, const int N) {
    M1 = A;
    M2 = B;
    M3 = C;
    m = M;
    pthread_t element_thread[L][N];
    for (int i = 0; i < L; i++) // create threads
        for (int j = 0; j < N; j++)
            if (pthread_create(&element_thread[i][j], NULL, compute_element, (void *) set_coordinates(i, j))) {
                printf("COULD NOT CREATE AN ELEMENT THREAD!\n");
                exit(1);
            }
    for (int i = 0; i < L; i++) // wait for all threads to terminate
        for (int j = 0; j < N; j++)
            pthread_join(element_thread[i][j], NULL);
}

void *compute_element(void *coordinates) {
    Coordinates *co = (Coordinates *) coordinates;
    int row = co->row, col = co->col;
    for (int i = 0; i < m; i++)
        M3[row][col] += M1[row][i] * M2[i][col];
    free(co);
}

/*
 * Creates a struct of coordinates of the specific element to e computed
 * to be passed as one parameter in "pthread_create" to "compute_element"
 */
Coordinates *set_coordinates(int i, int j) {
    Coordinates *coordinates = malloc(sizeof(Coordinates));
    coordinates->row = i;
    coordinates->col = j;
    return coordinates;
}