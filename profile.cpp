#include "profile.h"

profile::profile(std::string name,char *path) : name(name) {
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

map_t profile::count(const std::string pattern) {
  map_t count_map;
  for (std::size_t i = 0; i < frequencies.size() - pattern.back() + 1 ; ++i) {
    std::vector<double> position_vector (power(20,pattern.size()),0); 
    for (int j = 0; j < power(20,pattern.size()); ++j) {
      int word = j;
      double word_probability = 1;
      for (std::size_t k = 0; k < pattern.size(); ++k) {
        int amino_acid = word % 20;
        word_probability *= frequencies.at(i+(pattern.at(k)-'0'))[amino_acid];
        word /= 20;
      }
      position_vector.at(word) = word_probability;
    }
    for (std::size_t j = 0; j < position_vector.size(); ++j)
      count_map[j]=position_vector.at(j);
  }
  return count_map;
}
