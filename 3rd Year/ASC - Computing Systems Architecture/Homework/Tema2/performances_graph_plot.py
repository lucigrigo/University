# Grigore Lucian-Florin - ASC Tema 2
import sys
import matplotlib.pyplot as plt

PERF_FILE = 'performances.txt'

def main():
	dims = []
	neopt_p = []
	blas_p = []
	opt_p = []

	with open(PERF_FILE, 'r') as input_perf:
		# 1. neopt performance
		s = input_perf.readline()
		n = int(input_perf.readline())
		for i in range(n):
			line = input_perf.readline().split(' ')
			d = int(line[0])
			x = float(line[1])
			dims.append(d)
			neopt_p.append(x)

		# 2. blas performance
		s = input_perf.readline()
		n = int(input_perf.readline())
		for i in range(n):
			line = input_perf.readline().split(' ')
			x = float(line[1])
			blas_p.append(x)

		# 3. opt performance
		s = input_perf.readline()
		n = int(input_perf.readline())
		for i in range(n):
			line = input_perf.readline().split(' ')
			x = float(line[1])
			opt_p.append(x)

	plt.plot(dims, neopt_p, label = 'NEOPT')
	plt.plot(dims, blas_p, label = 'BLAS')
	plt.plot(dims, opt_p, label = 'OPT_M')

	plt.xlabel('Side size of matrix (N)')
	plt.ylabel('Time elapsed (s)')

	plt.grid()
	plt.legend()
	plt.show()

if __name__ == '__main__':
	main()
