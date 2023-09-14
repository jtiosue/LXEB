import matplotlib.pyplot as plt
from scipy.special import factorial2
import csv
import matplotlib.colors as mcolors
from matplotlib import rc
import numpy as np

plt.rcParams.update(plt.rcParamsDefault) 
plt.rcParams['text.usetex'] = True
plt.rcParams.update({'axes.titlesize':25, 'axes.labelsize':25, 'legend.fontsize':18,'xtick.labelsize':18,'ytick.labelsize':18})
plt.rcParams['mathtext.fontset'] = 'stix'
plt.rcParams['font.family'] = 'STIXGeneral'
plt.rcParams['text.latex.preamble'] = r'\usepackage{amsfonts}'

COLORS = list(mcolors.TABLEAU_COLORS.keys())


numerical_data = {}
ns = set()
# with open("../Cpp/fourth_moment_approx_mean_std.csv") as f:
with open("numerical_approx_fourth_moment.csv") as f:
    for row in csv.DictReader(f, delimiter=','):
    	numerical_data[(int(row['n']), int(row['k']))] = (
    		int(row['iters']), float(row['avg']), float(row['std'])
    		# int(row['iters']), float(row['avg'])
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
plt.xlabel(r'$k$')
plt.ylabel(r'$\mathbb{E}_X \textrm{Haf}[X^T X]^4$')
plt.title("Numerical Approximation vs. Computed Values for Second Moment")


for i, n in enumerate(ns):
	ks = sorted(set(x[1] for x in numerical_data if x[0] == n))

	plt.plot(
		ks, [compute(n, k) for k in ks], 
		"-", color=COLORS[i],
		label=r"$n = %d$; computed" % n
	)
	plt.errorbar(
		ks, [numerical_data[n, k][1] for k in ks], 
		[numerical_data[n, k][2] / np.sqrt(numerical_data[n, 1][0]) for k in ks],
		# [numerical_data[n, k][2] for k in ks],
		linestyle=":", color=COLORS[i],
		label=r"$n = %d$; numerical ($%d$ iters)" % (n, numerical_data[n, 1][0])
	)

plt.legend(fontsize=14)

plt.yscale("log")

f.set_size_inches(18.5, 10.5)
f.savefig("plot.pdf")
plt.close()
