#ifndef MISC_H
#define MISC_H

#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>

typedef std::vector<std::string> string_vector_t;

struct command_line_arguments {
  int k, l, n, number_of_threads;
  char *table_path, *fasta_path, *dir_path;
  command_line_arguments(int, char **);
};

string_vector_t split(const std::string,const char);
int power(int,int);

#endif
