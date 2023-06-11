import matplotlib.pyplot as plt
from scipy.special import factorial2
import csv
import matplotlib.colors as mcolors

COLORS = list(mcolors.TABLEAU_COLORS.keys())


numerical_data = {}
ns = set()
with open("../cpp-code/fourth_moment_approx_mean_std.csv") as f:
    for row in csv.DictReader(f, delimiter=','):
    	numerical_data[(int(row['n']), int(row['k']))] = (
    		int(row['iters']), float(row['mean']), float(row['std'])
    	)
    	ns.add(int(row['n']))

g = {}
with open("../Julia/computedG.csv") as f:
	for line in f:
		l = [int(x) for x in line.split(',')]
		if l[1:4] == [0, 0, 0]:
			g[l[0]] = l[4:]

def compute(n, k):
	return factorial2(2*n-1, exact=True) * sum(g[n][i] * k**i for i in range(len(g[n])))

f = plt.figure()
plt.xlabel('k')
plt.ylabel('Haf[X^T X]^4')
plt.title("Numerical approx vs computed values")


for i, n in enumerate(ns):
	ks = sorted(set(x[1] for x in numerical_data if x[0] == n))

	plt.semilogy(
		ks, [compute(n, k) for k in ks], 
		"-", color=COLORS[i],
		label=f"n = {n}; computed"
	)
	plt.semilogy(
		ks, [numerical_data[n, k][1] for k in ks], 
		":", color=COLORS[i],
		label=f"n = {n}; numerical ({numerical_data[n, 1][0]} iters)"
	)

plt.legend()

f.set_size_inches(18.5, 10.5)
f.savefig("plot.pdf")
plt.close()
