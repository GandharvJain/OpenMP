Run with:
```console
python3 testcase.py > in.txt && g++ matrix_mul_parallel.cpp -o matrix_mul_parallel.o -fopenmp && ./matrix_mul_parallel.o
```
or
```console
python3 testcase.py > in.txt && g++ matrix_mul_series.cpp -o matrix_mul_series.o -fopenmp && ./matrix_mul_series.o
```
* testcase.py: Create 2 random n*n matrices and find their product
* matrix_mul_series.cpp: series version of matrix multiplication with average time over 100 trials
* matrix_mul_parallel.cpp: Parallel version of matrix multiplication with average time over 100 trials
