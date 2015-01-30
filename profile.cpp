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
      frq_t *frq = new frq_t[20];
      for (unsigned int i = 2; i < segment_list.size(); ++i)
        frq[i-2] = std::make_pair(i-2,atof(segment_list.at(i).c_str()));
      frequencies.push_back(frq);
    }
    valid = true;
    file.close();
//    sort();
  } else {
    static int err_count = 0;
    std::cerr<<"File "<<fullpath<<" not found. No: "<<err_count++<<std::endl;
    valid = false;
  }
}

profile::~profile() {
  for (vector_it it = frequencies.begin(); it != frequencies.end(); ++it)
    delete [] *it;
}

bool profile::generate_from_fasta(fasta_map_t * fasta_map) {
  if (fasta_map->count(name) == 0)
    return valid = false;
  sequence = (*fasta_map)[name];
  for (std::string::iterator it = sequence.begin(); 
      it != sequence.end(); ++it) {
    frq_t *frq = new frq_t[20];
    for (unsigned int i = 0; i < 20; ++i)
      frq[i] = std::make_pair(i,0);
    if(aa_to_int(*it) > 0)
      frq[aa_to_int(*it)] = std::make_pair(aa_to_int(*it),1);
    frequencies.push_back(frq);
  }
//  sort();
  return valid = true;
}

const std::string profile::get_name() {
  return name;
}

inline bool sort_comp(const frq_t &a, const frq_t &b) {
  return a.second>b.second;
}
void profile::sort() {
  for (vector_it it = frequencies.begin(); it != frequencies.end(); ++it) {
    std::sort(*it, *it + 20, sort_comp);
  }
}

void profile::print_profile() {
  for (vector_it it = frequencies.begin(); it != frequencies.end(); ++it) {
    for (int i = 0; i < 20; i++)
      std::cout<<(*it)[i].second<<"\t";
    std::cout<<std::endl;
  }
}

map_t * profile::count(std::vector<int> pattern) {
  map_t *count_map = new map_t();
  for (std::size_t i = 0; i < frequencies.size() - pattern.back(); ++i) {
    std::list<frq_t *> rec_list;
    for (std::size_t j = 0; j < pattern.size(); ++j) {
      rec_list.push_back(frequencies[i+pattern[j]]);
    }
    std::vector<frq_t> probs = recursive_count(rec_list, -1);
    //abort();
    for (std::size_t j = 0; j < probs.size(); ++j) {
      (*count_map)[probs[j].first] = probs[j].second;
    }
  }
  return count_map;
}

std::vector<frq_t> profile::recursive_count(std::list<frq_t *> frqs, double limit) {
  std::vector<frq_t> out;
  frq_t * frq = frqs.front();
  for (int i = 0; i<20;++i)
    std::cout<<frq[i].first<<"->"<<frq[i].second<<std::endl;
  frqs.pop_front();
  std::vector<frq_t> tmp;
  if (frqs.size() > 0) {
    tmp = recursive_count(frqs, limit);
  } else {
    tmp.push_back(std::make_pair(0,1));
  }
  for (int i = 0; i < 20; ++i) {
    if (frq[i].second > limit) {
      for (std::size_t j = 0; j < tmp.size(); ++j) {
        //print(power(frq[i].first,frqs.size()+1), false);
        //print(" ", false);
        //print(tmp[j].first);
        out.push_back(
            std::make_pair(power(frq[i].first,frqs.size()+1) + tmp[j].first, 
              tmp[j].second * frq[i].second));
      }
    }
  }
  return out;
}

//map_t * profile::count(std::vector<int> pattern) {
//  map_t *count_map = new map_t();
//  for (std::size_t i = 0; i < frequencies.size() - pattern.back(); ++i) {
//    for (int j = 0; j < power(20,pattern.size()); ++j) {
//      int word = j;
//      double word_probability = 1;
//      for (std::vector<int>::iterator it = pattern.begin();
//          it != pattern.end() ; ++it) {
//        int amino_acid = word % 20;
//        word_probability *= frequencies.at(i+*it)[amino_acid];
//        word /= 20;
//      }
//      (*count_map)[j] += word_probability;
//    }
//  }
//  return count_map;
//}
