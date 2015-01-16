#include "profile.h"

profile::profile(std::string name, std::string path) : name(name) {
  std::string fullpath(path+name+std::string(".frp"));
  std::ifstream file(fullpath.c_str());
  if (file.is_open()) {
    std::string line;
    getline(file, line);
    while(getline(file, line)) {
      std::vector<std::string> segment_list = split(line, '\t');
      sequence += segment_list.at(1);
      double *frq = new double[20];
      for (unsigned int i = 2; i < segment_list.size(); ++i)
        frq[i-2] = atof(segment_list.at(i).c_str());
      frequencies.push_back(frq);
    }
    valid = true;
  } else {
    std::cerr<<"File "<<fullpath<<" not found"<<std::endl;
    valid = false;
  }
}

profile::~profile() {
  for (vector_it it = frequencies.begin(); it != frequencies.end(); ++it)
    delete [] *it;
}

const std::string profile::get_name() {
  return name;
}

void profile::print_profile() {
  for (vector_it it = frequencies.begin(); it != frequencies.end(); ++it) {
    for (int i = 0; i < 20; i++)
      std::cout<<(*it)[i]<<"\t";
    std::cout<<std::endl;
  }
}

map_t profile::count(std::vector<int> pattern) {
  map_t count_map;
  for (std::size_t i = 0; i < frequencies.size() - pattern.back(); ++i) {
    for (int j = 0; j < power(20,pattern.size()); ++j) {
      int word = j;
      double word_probability = 1;
      for (std::vector<int>::iterator it = pattern.begin();
          it != pattern.end() ; ++it) {
        int amino_acid = word % 20;
        word_probability *= frequencies.at(i+*it)[amino_acid];
        word /= 20;
      }
      count_map[j] += word_probability;
  }
  return count_map;
}
