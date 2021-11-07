Run with:
```console
g++ fft_parallel.cpp -o fft_parallel.o -fopenmp && python3 test.py 4 > in.txt && cat in.txt && ./fft_parallel.o
```
or
```console
g++ fft_series.cpp -o fft_series.o -fopenmp && python3 test.py 4 > in.txt && cat in.txt && ./fft_series.o
```
where 4 is the number of elements in the array.
* fft_series.cpp: Sequential code (Iterative and Recursive) for FFT and inverse-FFT with execution times.
* fft_parallel.cpp: Parallel code (Iterative) for FFT and inverse-FFT with average execution time.
* test.py: Generate random array (as input for above programs) and its fft (for verification) using library function.
