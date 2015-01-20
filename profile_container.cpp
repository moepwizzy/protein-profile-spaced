#include "profile_container.h"

profile_container::profile_container(int k, int l, int n) : k(k), l(l), n(n) {
  patterns = std::vector<std::vector<int> >(n);
  for (patterns_vector_t::iterator it = patterns.begin();
      it != patterns.end(); ++it)
    *it = std::vector<int>();
  generate_patterns();
  addable = true;
}

profile_container::~profile_container() {
  for(profile_map_t::iterator it = profiles.begin();
      it != profiles.end(); ++it)
    delete it->second;
}


bool profile_container::add_profile(profile *prof) {
  if (!addable || profiles.count(prof->get_name()) > 0)
    return false;
  profiles[prof->get_name()] = prof;
  return true;
}

profile* profile_container::get_profile(std::string name) {
  profile_map_t::iterator it = profiles.find(name);
  return it->second;
}

#if (__cplusplus >= 201103L)
#else
void count_thread(void * arg_ptr) {
  thread_struct *arg = (thread_struct *) arg_ptr;
  arg->map = arg->prof->count(*arg->pattern);
}
#endif
  
bool profile_container::count_all_profiles(int number_of_threads) {
  threadpool pool(number_of_threads);
  for (patterns_vector_t::iterator pat_it = patterns.begin();
      pat_it != patterns.end(); ++pat_it)
    for (profile_map_t::iterator map_it = profiles.begin(); 
        map_it != profiles.end(); ++map_it) {
      map_t *tmp;
      profile *tmp_prof = map_it->second;
      std::vector<int> *pattern = &(*pat_it);
#if (__cplusplus >= 201103L)
      pool.addThread([tmp, tmp_prof, pattern]() mutable {
          tmp = std::move(tmp_prof->count(*pattern));
      });
#else
      pool.addThread(count_thread, 
        (void *) new thread_struct(pattern, tmp, tmp_prof));
#endif
      for (map_t::iterator it = tmp->begin(); it != tmp->end(); ++it)
        if (count_map.count(it->first) == 0)
          count_map[it->first][map_it->second] += it->second;
      delete [] tmp;
    }
  return true;
}

void profile_container::generate_patterns() {
  std::vector<std::string> patterns_string;
  std::string patt = "";
  for (unsigned int i = 0; i < l; i++) {
    patt += "0";
  }
  for (unsigned int i = 0; i < k-2; i++) {
    patt += "1";
  }
  do {
    std::string s(patt.begin(), patt.end());
    s = "1"+s+"1";
    patterns_string.push_back(s);
  } while (std::next_permutation(patt.begin(), patt.end()));
  srand(time(0));
  std::random_shuffle(patterns_string.begin(), patterns_string.end());
  if (n < patterns_string.size()) {
    patterns_string.resize(n);
  }
  for (std::size_t i = 0; i < patterns_string.size(); ++i)
    for (std::size_t j = 0; j < patterns_string.at(i).size(); ++j)
      if (patterns_string.at(i).at(j) == '1')
        patterns.at(i).push_back((int)j);
}

void profile_container::print_stuff() {
  for (profile_map_t::iterator it = profiles.begin(); it != profiles.end(); ++it) 
    std::cout<<it->first<<" "<<it->second->get_name()<<std::endl;
  std::cout<<patterns.size()<<std::endl;
  for (patterns_vector_t::iterator it = patterns.begin();
      it != patterns.end(); ++it)
    for (std::size_t i = 0; i < it->size(); ++i)
      it->size()-1 == i? std::cout<<it->at(i)<<std::endl : std::cout<<it->at(i);
}
