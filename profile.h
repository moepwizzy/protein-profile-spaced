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

typedef std::vector<double*>::iterator vector_it;
typedef std::map<unsigned int,double> map_t;

class profile {
  std::vector<double*> frequencies;
  const std::string name;
  std::string sequence;
  bool valid; //atm some profs do not build correctly
 public:
  profile(std::string,std::string);
  ~profile();
  const std::string get_name();
  std::vector<double*> get_frequencies();
  void print_profile();
  map_t count(std::vector<int>);
  bool is_valid() {return valid;};
};

#endif
