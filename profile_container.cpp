#include "profile_container.h"

profile_container::profile_container(int k, int l, int n) : k(k), l(l), n(n) {
  patterns = std::vector<std::vector<int> >(n);
  for (patterns_vector_t::iterator it = patterns.begin();
      it != patterns.end(); ++it)
    *it = std::vector<int>();
  generate_patterns();
  addable = true;
#if (__cplusplus < 201103L)
  pthread_mutex_init(&mutex,NULL);
#endif
}

profile_container::~profile_container() {
  for(profile_map_t::iterator it = profiles.begin();
      it != profiles.end(); ++it)
    delete it->second;
}

bool profile_container::read_fasta_file(std::string path) {
  std::ifstream file(path.c_str());
  if (file.is_open()) {
    std::string line;
    std::string name;
    while(getline(file,line,'\n')) {
      if(line[0] == '>') {
        std::vector<std::string> tmp = split(line,' ');
        name = tmp[0];
        name.erase(0,1);
        fasta_map[name] = std::string("");
      } else {
        fasta_map[name] += line;
      }
    }
    file.close();
    return true;
  } else {
    return false;
  }
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
  map_t *tmp = arg->prof->count(*arg->pattern);
  for (map_t::iterator it = tmp->begin(); it != tmp->end(); ++it) {
    _lock_mutex(arg->mutex_ptr);
    (*arg->c_map)[it->first][arg->prof] += it->second;
    _unlock_mutex(arg->mutex_ptr);
  }
  delete tmp;
}
#endif
  
bool profile_container::count_all_profiles(int number_of_threads) {
  threadpool pool(number_of_threads);
  for (patterns_vector_t::iterator pat_it = patterns.begin();
      pat_it != patterns.end(); ++pat_it) {
    for (profile_map_t::iterator map_it = profiles.begin(); 
        map_it != profiles.end(); ++map_it) {
#if (__cplusplus >= 201103L)
      count_t *c_map = &count_map;
      profile *prof = map_it->second;
      std::vector<int> *pattern = &(*pat_it);
      mu_t *mutex_ptr = &mutex;
      pool.addThread([c_map, prof, pattern, mutex_ptr]() mutable {
        map_t *tmp = std::move(prof->count(*pattern));
        for (map_t::iterator it = tmp->begin(); it != tmp->end(); ++it) {
          _lock_mutex(mutex_ptr); 
          (*c_map)[it->first][prof] += it->second;
          _unlock_mutex(mutex_ptr);
        }
        delete tmp;
      });
#else
      pool.addThread(count_thread, 
        (void *) new thread_struct(&(*pat_it), &count_map, map_it->second, &mutex));
#endif
    }
    pool.wait();
  }
  for (profile_map_t::iterator prof_map_it = profiles.begin();
      prof_map_it != profiles.end(); ++prof_map_it) {
    for (count_t::iterator outer_it= count_map.begin();
        outer_it != count_map.end(); ++outer_it) {
      prof_map_it->second->add_to_representing_vector(
          outer_it->second[prof_map_it->second]);
    }
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
  for (std::size_t i = 0; i < patterns_string.size() && i < n; ++i)
    for (std::size_t j = 0; j < patterns_string.at(i).size(); ++j)
      if (patterns_string.at(i).at(j) == '1')
        patterns.at(i).push_back((int)j);
  if (patterns_string.size() < n)
    patterns.resize(patterns_string.size());
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
