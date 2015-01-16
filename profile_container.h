#ifndef PROFILE_CONTAINER_H
#define PROFILE_CONTAINER_H

#if (__cplusplus >= 201103L)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <string>
#include <vector>
#include <algorithm> //random shuffle
#include <cstdlib> //srand
#include <ctime> //time
#include <iostream>

#include "profile.h"

#if (__cplusplus >= 201103L)
typedef std::unordered_map<std::string, profile*> profile_map_t;
typedef std::unordered_map<int, std::unordered_map<profile*,int> > count_t;
#else
typedef std::tr1::unordered_map<std::string, profile*> profile_map_t;
typedef std::tr1::unordered_map<int, std::unordered_map<profile*,int> > count_t;
#endif
typedef std::vector<std::vector<int> > patterns_vector_t;

class profile_container {
  const unsigned int k,l,n;
  bool addable;
  profile_map_t profiles;
  patterns_vector_t patterns;
  void generate_patterns();
 public:
  profile_container(int,int,int);
  ~profile_container();
  bool add_profile(profile*);
  profile* get_profile(std::string);
  bool count_all_profiles();
  void print_stuff();
};

#endif
