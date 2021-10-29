import numpy as np

n = 2048
a = np.random.randint(0,9,(n,n)).astype('uint8')
b = np.random.randint(0,9,(n,n)).astype('uint8')
c = a.dot(b)

print(n)
print('\n'.join(map(lambda b: ' '.join(map(str, b)), a)))
print(n)
print('\n'.join(map(lambda b: ' '.join(map(str, b)), b)))
print(n)
print('\n'.join(map(lambda b: ' '.join(map(str, b)), c)))