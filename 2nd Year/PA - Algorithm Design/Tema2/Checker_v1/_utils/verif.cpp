/* Copyright 2018
 * Neatu Darius-Florentin <neatudarius@gmail.com>
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

struct tema {
	int length, points, deadline, init_pos;

	bool operator < (const tema& other) const {
		if (deadline != other.deadline)
			return deadline < other.deadline;
		else
			return init_pos < other.init_pos;
	}
};

void DIE(float points, const char *msg) {
	FILE *f;

	f = fopen("score.verif", "wt");
	fprintf(f, "%.1f", points);
	fclose(f);

	f = fopen("output.verif", "wt");
	fprintf(f, "%s", msg);
	fclose(f);

	exit(0);
}

void check_teme(float points) {
	FILE *file_in, *file_out, *file_ref;

	file_ref = fopen("res.ok", "rt");
	if (file_ref == NULL) {
		DIE(0, "Nu exista fisier de referinta");
	}

	file_in = fopen("teme.in", "rt");
	if (file_in == NULL) {
		DIE(0, "Nu exista fisier de input");
	}

	file_out = fopen("teme.out", "rt");
	if (file_out == NULL) {
		DIE(0, "Nu exista fisier de output");
	}

	int N, maxtime, M, sc, idx, i;
	int day = 0;
	tema work[1005];
	int vals[1005] = {0};
	char c[100];
	long long answer_out, answer_ref, score = 0;
	fscanf(file_in, "%d", &N);
	for (idx = 1; idx <= N; idx++) {
		fscanf(file_in, "%d %d %d", &work[idx].length, &work[idx].points,
			&work[idx].deadline);
		maxtime = max(maxtime, work[idx].deadline);
		work[idx].init_pos = idx;
	}
	fclose(file_in);

	fscanf(file_ref, "%lld", &answer_ref);
	fclose(file_ref);

	fscanf(file_out, "%lld %d", &answer_out, &M);

	if (answer_ref != answer_out) {
		char c[100];
		sprintf(c, "WA %lld vs %lld", answer_out, answer_ref);
		DIE(0, c);
	}

	for (i = 1; i <= M; i++) {
		fscanf(file_out, "%d ", &vals[i]);
		score += work[vals[i]].points;
		day += work[vals[i]].length;
		if (day > work[vals[i]].deadline) {
			sprintf(c, "WA ");
			DIE(0, c);
		}
	}
	fclose(file_out);
	if (score != answer_ref) {
		char c[100];
		sprintf(c, "WA %lld vs %lld", score, answer_ref);
		DIE(0, c);
	}
	DIE(points, "OK ");
}

int main(int argc, char **argv) {
	if (argc != 3) {
		DIE(0, "Usage ./verif problem_name test_points");
	}

	char name[100];
	strcpy(name, argv[1]);
	strcat(name, ".out");

	float points = atof(argv[2]);

	FILE *file_out = fopen(name, "rt"),
		 *file_ref = fopen("res.ok", "rt");

	if (file_ref == NULL) {
		DIE(0, "Nu exista fisierul de referinta");
	}

	if (file_out == NULL) {
		DIE(0, "Nu exista fisier de output");
	}

	if (!strcmp(argv[1], "teme")) {
		check_teme(points);
		return 0;
	}

	long long answer_out, answer_ref;
	while (fscanf(file_ref, "%lld", &answer_ref) == 1) {
		int ret = fscanf(file_out, "%lld", &answer_out);
		if (ret < 0) {
			DIE(0, "Fisierul de iesire nu contine un numar corespunzator de numere");
		}

		if (answer_ref != answer_out) {
			char c[100];

			#ifdef ONLINE_JUDGE
			sprintf(c, "WA ");
			#else
			sprintf(c, "WA %lld vs %lld", answer_out, answer_ref);
			#endif

			DIE(0, c);
		}
	}

	DIE(points, "OK ");

	return 0;
}
