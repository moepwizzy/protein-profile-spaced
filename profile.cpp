#include "profile.h"

profile::profile(std::string name,char *path) : name(name) {
  std::string fullpath(path+name);
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
  } else {
    std::cerr<<"File "<<fullpath<<" not found"<<std::endl;
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

map_t count() {
  map_t moep;
  return moep;
}  
