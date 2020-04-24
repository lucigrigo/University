/* Copyright 2018
 * Neatu Darius-Florentin <neatudarius@gmail.com>
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;


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
