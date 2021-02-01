def main():
	n = int(input("N = "))
	if (n < 2):
		print("sugi pl")
		exit(-1)
	w = [[1, 1], [1, -1]]
	i = 2
	while i < n:
		wn = []
		for j in range(i):
			wn.append(w[j] + w[j])
		for j in range(i):
			aux = [-x for x in w[j]]
			wn.append(w[j] + aux)
		w = wn
		i *= 2
	print(f"w = {w}\n")
	query = []
	for i in range(n):
		inp = input(f"Station {i} (0/1/s) : ")
		if inp == "s":
			query.append(0)
		else:
			x = int(inp)
			if x == 0:
				query.append(-1)
			else:
				query.append(1)
	print(f"query = {query}\n")
	sol = n * [0]
	for i in range(n):
		sol[i] = sum([w[i][j] * query[j] for j in range(n)])
	print(sol)

if __name__ == '__main__':
	main()