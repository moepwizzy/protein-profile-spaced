#include "profile_container.h"

profile_container::profile_container(int k, int l, int n) : k(k), l(l), n(n) {
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

bool profile_container::count_all_profiles() {
  addable = false;
  for (std::vector<std::string>::iterator pat_it = patterns.begin();
      pat_it != patterns.end(); ++pat_it)
    for (profile_map_t::iterator map_it = profiles.begin();
        map_it != profiles.end(); ++map_it)
      map_it->second->count(*pat_it);
  return true;
}

void profile_container::generate_patterns() {
  std::cout<<"moep"<<std::endl;
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
      if (patterns_string.at(i).at(j) == 1)
        patterns.at(i).push_back(j);
  std::cout<<patterns.size()<<std::endl;
}

void profile_container::print_stuff() {
  for (profile_map_t::iterator it = profiles.begin(); it != profiles.end(); ++it) 
    std::cout<<it->first<<" "<<it->second->get_name()<<std::endl;
  std::cout<<patterns.size()<<std::endl;
  for (std::vector<std::string>::iterator it = patterns.begin();
      it != patterns.end(); ++it)
    std::cout<<*it<<std::endl;
}
