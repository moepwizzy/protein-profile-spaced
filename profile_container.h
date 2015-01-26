#ifndef PROFILE_CONTAINER_H
#define PROFILE_CONTAINER_H

#if (__cplusplus >= 201103L)
#include <unordered_map>
#include <mutex>
#else
#include <tr1/unordered_map>
#include <pthread.h>
#endif
#include <string>
#include <vector>
#include <algorithm> //random shuffle
#include <cstdlib> //srand
#include <ctime> //time
#include <iostream>

#include "profile.h"
#include "../threadpool/threadpool.h"
#include "misc.h"

typedef std::vector<std::vector<int> > patterns_vector_t;
#if (__cplusplus >= 201103L)
typedef std::unordered_map<std::string, profile*> profile_map_t;
typedef std::unordered_map<profile*, double> count_internal_t;
typedef std::unordered_map<unsigned int, count_internal_t> count_t;
typedef std::unordered_map<std::string,std::string> fasta_map_t;
typedef std::mutex mu_t;
inline void _lock_mutex(mu_t *m) {
  m->lock();
}
inline void _unlock_mutex(mu_t *m) {
  m->unlock();
}
#else
typedef std::tr1::unordered_map<std::string, profile*> profile_map_t;
typedef std::tr1::unordered_map<profile*, double> count_internal_t;
typedef std::tr1::unordered_map<unsigned int, count_internal_t> count_t;
typedef std::tr1::unordered_map<std::string,std::string> fasta_map_t;
typedef pthread_mutex_t mu_t;

struct thread_struct {
  std::vector<int> *pattern;
  count_t *c_map;
  profile *prof;
  mu_t *mutex_ptr;
  thread_struct(std::vector<int> *pattern, count_t *m, profile *p, mu_t *mu) 
    : pattern(pattern), c_map(m), prof(p), mutex_ptr(mu) {};
};

inline void _lock_mutex(mu_t *m) {
  pthread_mutex_lock(m);
}
inline void _unlock_mutex(mu_t *m) {
  pthread_mutex_unlock(m);
}
#endif

class profile_container {
  const unsigned int k,l,n;
  bool addable;
  profile_map_t profiles;
  count_t count_map;
  patterns_vector_t patterns;
  void generate_patterns();
  mu_t mutex;
  fasta_map_t fasta_map;
 public:
  profile_container(int,int,int);
  ~profile_container();
  bool read_fasta_file(std::string);
  bool add_profile(profile*);
  profile* get_profile(std::string);
  bool count_all_profiles(int);
  void print_stuff();
};

#endif
