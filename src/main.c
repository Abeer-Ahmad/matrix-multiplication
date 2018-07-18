#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "multi-threading/row-threaded.h"
#include "multi-threading/element_threaded.h"
#include "handlers/file/file_handler.h"

int **A, **B, **C; // where A, B are the input matrices, and C is the output matrix
int L, M, N; // A is L×M, B is M×N -> C is L×N
char *output_file;
struct timeval start, stop;

void set_A(char *path);

void set_B(char *path);

void allocate_output_matrix();

void reset_output_matrix();

int main(int argc, char *argv[]) {
    if (argc == 4) { // all files provided -including program name-
        set_A(argv[1]);
        set_B(argv[2]);
        output_file = argv[3];
    } else { // use default files
        set_A("a.txt");
        set_B("b.txt");
        output_file = "c.txt";
    }
    allocate_output_matrix();
    reset_output_matrix();

    gettimeofday(&start, NULL); // start stopwatch
    run_row_threads(A, B, C, L, M, N);
    gettimeofday(&stop, NULL); // stop
    write_output_file("RowThreadedOutput.txt", C, L, N);
    printf("Number of threads created in the \"Thread per Row\" method = %d\n", L);
    printf("Time taken in seconds =  %lu\n", stop.tv_sec - start.tv_sec);
    printf("Time taken in microseconds = %lu\n\n", stop.tv_usec - start.tv_usec);

    reset_output_matrix();

    gettimeofday(&start, NULL); // start stopwatch
    run_element_threads(A, B, C, L, M, N);
    gettimeofday(&stop, NULL); // stop
    write_output_file("ElementThreadedOutput.txt", C, L, N);
    printf("Number of threads created in the \"Thread per Element\" method = %d\n", L * N);
    printf("Time taken in seconds =  %lu\n", stop.tv_sec - start.tv_sec);
    printf("Time taken in microseconds = %lu\n\n", stop.tv_usec - start.tv_usec);

    write_output_file(output_file, C, L, N); // writes the multiplication output to the given file

    return (0);
}

void set_A(char *path) {
    Matrix *matrix = read_input_file(path);
    A = matrix->content;
    L = matrix->rows;
    M = matrix->cols;
}

void set_B(char *path) {
    Matrix *matrix = read_input_file(path);
    B = matrix->content;
    N = matrix->cols;
}

void allocate_output_matrix() {
    C = (int **) malloc(L * N * sizeof(int));
    for (int i = 0; i < L; ++i)
        C[i] = malloc(N * sizeof(int));
}

void reset_output_matrix() {
    for (int i = 0; i < L; ++i)
        for (int j = 0; j < N; ++j)
            C[i][j] = 0;
}