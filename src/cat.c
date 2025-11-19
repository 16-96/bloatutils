#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 16384

void stream_file(FILE *input, const char *filename) {
  char buffer[BUFFER_SIZE];
  size_t bytes_read;

  while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
    fwrite(buffer, 1, bytes_read, stdout);
  }

  if (ferror(input)) {
    fprintf(stderr, "bloat-cat: error reading '%s': %s\n", filename,
            strerror(errno));
  }
}

int main(int argc, char **argv) {
  if (argc == 1) {
    stream_file(stdin, "stdin");
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp;
    const char *fname = argv[i];

    if (strcmp(fname, "-") == 0) {
      stream_file(stdin, "stdin");
      continue;
    }

    fp = fopen(fname, "rb");
    if (!fp) {
      fprintf(stderr, "bloat-cat: could not find '%s'\n", fname);
      continue;
    }

    stream_file(fp, fname);
    fclose(fp);
  }

  return 0;
}
