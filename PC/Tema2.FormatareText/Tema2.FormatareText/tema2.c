#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int main(int argc, char *argv[]) {

    FILE *ffile;
    int num;
    char buf[MAX],
            original[MAX][MAX],
            result[MAX][MAX];
    int original_line_count = 0,
            result_line_count = 0,
            i;

    if (argc != 4) {
        fprintf(stderr, "Usage : %s operations_string input_file output_file\n",
                argv[0]);
        return -1;
    }

    ffile = fopen(argv[2], "r");

    if (ffile == NULL) {
        fprintf(stderr, "File \"%s\" not found \n", argv[2]);
        return -2;
    }

    while (fgets(buf, MAX, ffile)) {
        strcpy(original[original_line_count], buf);
        original_line_count++;
    }

    for (i = 0; i < original_line_count; i++) {
        //      fprintf()
    }

    fclose(ffile);

    return 0;
}
