#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
typedef complex<long double> cmplx;
long double pi = acos(-1);

vector<vector<cmplx>> w_R;		//log_2(n) rows, max columns = n
void w_r_init(int n, int inverse) {
	for (int j = 1; j <= n; j*=2) {
		vector<cmplx> w_R_j;
		long double theta = 2*pi/j*(inverse ? -1 : 1);
		cmplx w(cos(theta), sin(theta)), w_k(1, 0);
		for (int k = 0; k < j; ++k) {
			w_R_j.push_back(w_k);
			w_k *= w;
		}
		w_R.push_back(w_R_j);
	}
}

void fft_recursive(vector<cmplx> & a){
	
	int n = a.size();
	if (n == 1)
		return;
	int log_n = log2(n);

	vector<cmplx> a_even(n/2), a_odd(n/2);
	for (int i = 0; i < n/2; ++i) {
		a_even[i] = a[2*i];
		a_odd[i] = a[2*i+1];
	}

	fft_recursive(a_even);
	fft_recursive(a_odd);
	
	for (int i = 0; i < n/2; ++i) {
		//w_R = exp((+/-)2*pi*i/n)
		cmplx t = w_R[log_n][i]*a_odd[i];
		a[i] = a_even[i] + t;
		a[i + n/2] = a_even[i] - t;
	}
}

void ifft_recursive(vector<cmplx> &a){
	int n = a.size();
	w_r_init(n, 1);
	fft_recursive(a);
	for (int i = 0; i < n; ++i)
		a[i] /= n;
}

int bitRev(int in, int log_n) {
	int out = 0;
	while (log_n--) {
		out <<= 1;
		out |= in & 1;
		in >>= 1;
	}
	return out;
}

void bitRevPermute(vector<cmplx> &a) {
	int n = a.size();
	int log_n = log2(n);
	for (int i = 0; i < n; ++i) {
		int j = bitRev(i, log_n);
		if (j > i) {
			cmplx temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
}

void fft_iterative(vector<cmplx> &a, int inverse) {
	bitRevPermute(a);
	int n = a.size();

	vector<vector<cmplx>> w_I;
	for (int j = 1; j <= n; j*=2) {
		vector<cmplx> w_I_j;
		long double theta = 2*pi/j*(inverse ? -1 : 1);
		cmplx w(cos(theta), sin(theta)), w_k(1, 0);
		for (int k = 0; k < j; ++k) {
			w_I_j.push_back(w_k);
			w_k *= w;
		}
		w_I.push_back(w_I_j);
	}
	for (int m = 2, log_m = 1; m <= n; m*=2, log_m++) {
		for (int i = 0; i < n; i+=m) {

			for (int j = 0; j < m/2; ++j) {
				cmplx t1 = a[i+j], t2 = w_I[log_m][j]*a[i+j+m/2];
				a[i+j] = t1 + t2;
				a[i+j+m/2] = t1 - t2;
			}
		}
	}
}

void ifft_iterative(vector<cmplx> &a){
	fft_iterative(a, 1);
	int n = a.size();
	for (int i = 0; i < n; ++i)
		a[i] /= n;
}

void print(const vector<cmplx> & v, string message, bool imag) {
	cout /*<< fixed*/ << setprecision(9) << message << "\n";
	for (int i = 0; i < v.size(); ++i) {
		if (imag)
			cout << "(" << v[i].real() << ", " << v[i].imag() << ")" << " ";
		else
			cout << v[i].real() << " ";
	}
	cout << "\n";
}

void check(const vector<cmplx> &a, const vector<cmplx> &b) {
	double epsilon = 0.00001;
	for (int i = 0; i < a.size(); ++i) {
		cmplx temp = a[i]-b[i];
		if (temp.real() > epsilon || temp.imag() > epsilon) {
			cout << "\nArrays don't match" << "\n" << a[i] << " " << b[i] << "\n";
			return;
		}
	}
	cout << "\nArrays match" << "\n";
}

int main()
{
	ifstream f;
	f.open("in.txt");
	double runtimePy; f >> runtimePy;
	
	int n; f >> n;
	vector<cmplx> a(n);
	for (int i = 0; i < n; ++i)
		f >> a[i];
	vector<cmplx> b(a.begin(), a.end());

	double runtimeR_FFT, runtimeR_IFFT, runtimeI_FFT, runtimeI_IFFT;

	runtimeR_FFT = omp_get_wtime();
	// w_r_init(n, 0);
	// fft_recursive(a);
	runtimeR_FFT = omp_get_wtime() - runtimeR_FFT;
	// print(a, "Recursive FFT: ", true);

	w_R.clear();

	runtimeR_IFFT = omp_get_wtime();
	// ifft_recursive(a);
	runtimeR_IFFT = omp_get_wtime() - runtimeR_IFFT;
	// print(a, "Recursive Inverse-FFT: ", false);

	runtimeI_FFT = omp_get_wtime();
	fft_iterative(a, 0);
	runtimeI_FFT = omp_get_wtime() - runtimeI_FFT;
	// print(a, "Iterative FFT: ", true);

	runtimeI_IFFT = omp_get_wtime();
	ifft_iterative(a);
	runtimeI_IFFT = omp_get_wtime() - runtimeI_IFFT;
	// print(a, "Iterative Inverse-FFT: ", false);

	check(a, b);
	cout << "\nRuntime :-" << fixed << "\n";
	cout << "Python FFT            :" << runtimePy << "\n";
	cout << "Recursive FFT         :" << runtimeR_FFT << "\n";
	cout << "Recursive Inverse FFT :" << runtimeR_IFFT << "\n";
	cout << "Iterative FFT         :" << runtimeI_FFT << "\n";
	cout << "Iterative Inverse FFT :" << runtimeI_IFFT << "\n";
	return 0;
}

// Run with:
// g++ fft_series.cpp -o fft_series.o -fopenmp && python3 test.py 4 > in.txt && cat in.txt && ./fft_series.o