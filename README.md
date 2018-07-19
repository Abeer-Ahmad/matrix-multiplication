# matrix-multiplication
A parallelized version of matrix multiplication via multi-threading.
## Overview
The input to the program is two matrices A(x\*y) and B(y\*z) that are read from corresponding files, while he output is a matrix C(x\*z) that is written to an output file. 

A parallelized version of matrix multiplication can be done using one of the following two methods:
1. A thread computes each row in the output C matrix.
2. A thread computes each element in the output C matrix.  

Both implementations are compared according to:
1. Number of thread created.
2. Execution time needed.
## How to Run
- The program is executed -after running the Makefile- as: ./matmult Mat1 Mat2 MatOut, where Mat1 and Mat2 are the names of the files to read the first and second matrices, respectively, and MatOut is the name of the file to write the output matrix. If nothing is entered, the default is a.txt and b.txt, for input A and B, respectively, and c.out for the output matrix.
- Number of rows and columns of the input matrices are found in the first line of the file, in the form ”row=x col=y”, where each row is in a separate line, with tab-separated columns.
- Resulting matrix is written to an output file.
- Number of threads created as well as time needed for each method is printed on the 'stdout', and also streamed into 2 output files named 'RowThreadedOutput' and 'ElementThreadedOutput'.
