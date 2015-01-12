#ifndef MISC_H
#define MISC_H

#include <iostream>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>

struct command_line_arguments {
  int k, l, n, number_of_threads;
  char *table_path, *fasta_path;
  command_line_arguments(int, char **);
};

#endif
