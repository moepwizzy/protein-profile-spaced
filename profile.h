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
#include <algorithm> //sort
#include <list>

#include "misc.h"

#if (__cplusplus >= 201103L)
#include <unordered_map>
typedef std::unordered_map<std::string,std::string> fasta_map_t;
#else
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<std::string,std::string> fasta_map_t;
#endif
typedef std::map<unsigned int,double> map_t;
typedef std::pair<int,double> frq_t;
typedef std::vector<frq_t*>::iterator vector_it;

class profile {
  std::vector<frq_t *> frequencies;
  const std::string name;
  std::string sequence;
  std::vector<double> representing_vector;
  bool valid; //atm some profs do not build correctly
  void sort();
  std::vector<frq_t> recursive_count(std::list<frq_t *>, double);
 public:
  profile(std::string,std::string);
  ~profile();
  bool generate_from_fasta(fasta_map_t *);
  const std::string get_name();
  std::vector<frq_t *> get_frequencies() {
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
