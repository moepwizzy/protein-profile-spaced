#ifndef PROFILE_H
#define PROFILE_H

#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

typedef std::vector<std::pair<char,double>*> freq_prof; 

class profile {
  freq_prof frequencies;
  profile(char *path);
  ~profile();
 public:
  freq_prof get_frequencies();
};

#endif
