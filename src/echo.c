#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    write(STDOUT_FILENO, "\n", 1);
    return 0;
  }

  int i = 1;
  bool print_newline = true;

  if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0') {
    print_newline = false;
    i++;

    if (i == argc)
      return 0;
  }

  char *batch_start = argv[i];
  char *current = argv[i];

  for (; i < argc - 1; i++) {
    size_t len = strlen(argv[i]);
    char *next = argv[i + 1];

    if (__builtin_expect(argv[i] + len + 1 == next, 1)) {
      argv[i][len] = ' ';
    } else {
      write(STDOUT_FILENO, batch_start, (argv[i] + len) - batch_start);
      write(STDOUT_FILENO, " ", 1);
      batch_start = next;
    }
  }

  size_t last_len = strlen(argv[argc - 1]);

  if (print_newline) {
    argv[argc - 1][last_len] = '\n';
    write(STDOUT_FILENO, batch_start,
          (argv[argc - 1] + last_len + 1) - batch_start);
  } else {
    write(STDOUT_FILENO, batch_start,
          (argv[argc - 1] + last_len) - batch_start);
  }

  return 0;
}