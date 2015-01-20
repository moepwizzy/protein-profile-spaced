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
#include "../threadpool/threadpool.h"

typedef std::vector<std::vector<int> > patterns_vector_t;
#if (__cplusplus >= 201103L)
typedef std::unordered_map<std::string, profile*> profile_map_t;
typedef std::unordered_map<profile*, double> count_internal_t;
typedef std::unordered_map<unsigned int, count_internal_t> count_t;
#else
typedef std::tr1::unordered_map<std::string, profile*> profile_map_t;
typedef std::tr1::unordered_map<profile*, double> count_internal_t;
typedef std::tr1::unordered_map<unsigned int, count_internal_t> count_t;

struct thread_struct {
  std::vector<int> *pattern;
  map_t *map;
  profile *prof;
  thread_struct(std::vector<int> *pattern, map_t *m, profile *p) 
    : pattern(pattern), map(m), prof(p) {};
};
#endif

class profile_container {
  const unsigned int k,l,n;
  bool addable;
  profile_map_t profiles;
  count_t count_map;
  patterns_vector_t patterns;
  void generate_patterns();
 public:
  profile_container(int,int,int);
  ~profile_container();
  bool add_profile(profile*);
  profile* get_profile(std::string);
  bool count_all_profiles(int);
  void print_stuff();
};

#endif
