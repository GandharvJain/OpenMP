#include <omp.h>
#include <bits/stdc++.h>
#define TRIALS 5
using namespace std;
  
int main(int argc, char* argv[]) {
	
	double start, end;
	int tid;
	ifstream f;
	f.open("in.txt");
	int n;
	f >> n;
	int *a = new int[n*n];
	int *b = new int[n*n];
	int *c = new int[n*n]{};


	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			f >> a[i * n + j];
	f >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			f >> b[i * n + j];

	double average = 0;

	for (int t = 0; t < TRIALS; ++t) {
		start = omp_get_wtime();

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				c[i * n + j] = 0;
				for (int k = 0; k < n; ++k) {
					c[i * n + j] += a[i * n + k] * b[k * n + j];
				}
			}
		}
		end = omp_get_wtime();
		
		average += end-start;
	}
	average /= TRIALS;


	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) {
	// 		cout << c[i * n + j] << " ";
	// 	}
	// 	cout << "\n";
	// }
	printf("Matrix size: %d x %d\n", n, n);
	printf("Average total time: %f seconds\n", average);
    
    return 0;
}
