#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char buf[1000],               // buffer used for reading from the file
      original[1000][1000],     // original text, line by line
      result[1000][1000];       // text obtained after applying operations
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i;

  if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }

  // Open input file for reading
  FILE *input_file = fopen(argv[2], "r");

  if (input_file == NULL) {
    fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
  }

  // Read data in file line by line
  while (fgets(buf, 1000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

  fclose(input_file);

  /*
   * TODO apply operations in operation_string (argv[1]) one by one and save
   * the result in the 'result' matrix.
   *
   * Replace this comment and the next piece of code with your solution.
   */
  for (i = 0; i < original_line_count; i++) {
    strcpy(result[i], original[i]);
  }
  result_line_count = original_line_count;

  // Open output file for writing
  FILE *output_file = fopen(argv[3], "w");

  if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
  }

  // Write result in output file
  for (i = 0; i < result_line_count; i++) {
    fputs(result[i], output_file);
  }

  fclose(output_file);
}
