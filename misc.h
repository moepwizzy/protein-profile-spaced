#ifndef MISC_H
#define MISC_H

#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>

typedef std::vector<std::string> string_vector_t;

struct command_line_arguments {
  int k, l, n, number_of_threads;
  std::string table_path, fasta_path, dir_path;
  command_line_arguments(int, char **);
};

int aa_to_int(const char);
string_vector_t split(const std::string,const char);
int power(int,int);
template <typename T>
void print(T text, bool nl = true) {
  nl ? std::cout<<text<<std::endl : std::cout<<text<<std::flush;
}

#endif
