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
  
  return true;
}

void profile_container::generate_patterns() {
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
    patterns.push_back(s);
  } while (std::next_permutation(patt.begin(), patt.end()));
  srand(time(0));
  std::random_shuffle(patterns.begin(), patterns.end());
  if (n < patterns.size()) {
    patterns.resize(n);
  }
}
