#ifndef PROFILE_H
#define PROFILE_H

#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <iostream>

#include "misc.h"

#if (__cplusplus >= 201103L)
#include <unordered_map>
typedef std::unordered_map<std::string,std::string> fasta_map_t;
#else
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<std::string,std::string> fasta_map_t;
#endif
typedef std::vector<double*>::iterator vector_it;
typedef std::map<unsigned int,double> map_t;

class profile {
  std::vector<double*> frequencies;
  const std::string name;
  std::string sequence;
  std::vector<double> representing_vector;
  bool valid; //atm some profs do not build correctly
 public:
  profile(std::string,std::string);
  ~profile();
  bool generate_from_fasta(fasta_map_t *);
  const std::string get_name();
  std::vector<double*> get_frequencies() {
    return frequencies;
  }
  std::vector<double> * get_representing_vector() {
    return &representing_vector;
  }
  void print_profile();
  map_t * count(std::vector<int>);
  inline void add_to_representing_vector(double number) {
    representing_vector.push_back(number);
  }
  bool is_valid() {return valid;}
};

#endif
