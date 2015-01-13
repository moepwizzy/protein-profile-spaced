#ifndef PROFILE_H
#define PROFILE_H

#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "misc.h"

typedef std::vector<double*>::iterator vector_it;
typedef std::map<unsigned int,unsigned int> map_t;

class profile {
  std::vector<double*> frequencies;
  const std::string name;
  std::string sequence;
 public:
  profile(std::string,char*);
  ~profile();
  const std::string get_name();
  std::vector<double*> get_frequencies();
  void print_profile();
  map_t count();
};

#endif
