import numpy as np
from thewalrus import hafnian as haf

iters = 10000
ns = range(1, 10)
ks = range(1, 10)

output_filename = "numerical_approx_fourth_moment.csv"


def write_to_file(n, k, iters, avg, std):
	with open(output_filename, "a") as f:
		print(f"{n},{k},{iters},{avg},{std}", file=f)



def random_gaussian_matrix(rows, cols):
	return (
		np.random.normal(0, 1/np.sqrt(2), (rows, cols))
		+ 1.j * np.random.normal(0, 1/np.sqrt(2), (rows, cols))
	)



write_to_file("n", "k", "iters", "avg", "std")

for n in ns:
	for k in ks:
		print(f"Starting n = {n}, k = {k}")
		samples = []
		for _ in range(iters):
			X = random_gaussian_matrix(k, 2*n)
			samples.append(np.abs(haf(X.T @ X)) ** 4)

		write_to_file(n, k, iters, np.mean(samples), np.std(samples))


