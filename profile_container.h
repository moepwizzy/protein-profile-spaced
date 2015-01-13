#ifndef PROFILE_CONTAINER_H
#define PROFILE_CONTAINER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm> //random shuffle
#include <cstdlib> //srand
#include <ctime> //time

#include "profile.h"

typedef std::unordered_map<std::string,profile*> profile_map_t;
typedef std::unordered_map<int,std::unordered_map<profile*,int>> count_t;

class profile_container {
  const unsigned int k,l,n;
  bool addable;
  profile_map_t profiles;
  std::vector<std::string> patterns;
  void generate_patterns();
 public:
  profile_container(int,int,int);
  ~profile_container();
  bool add_profile(profile*);
  profile* get_profile(std::string);
  bool count_all_profiles();
};

#endif