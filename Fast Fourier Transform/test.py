from sympy import fft
import numpy as np
import sys
import pyfftw
import time
n = int(sys.argv[1])
decimal = 2
a = np.random.randint(1, 99, size=(n)).astype('uint8')

start_time = time.time()
transform = pyfftw.interfaces.scipy_fftpack.fft(a, n)

print("%s\n" % (time.time() - start_time))

print(n)
print(' '.join(map(str, a)))
if n <= 16:
	r = transform.real
	i = transform.imag
	transform = [tuple([round(r[j], 3), round(-1*i[j], 3)]) for j in range(len(transform))]
	print("\nPython FFT:")
	print(*transform)
