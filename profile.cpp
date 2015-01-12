#include "profile.h"

profile::profile(char *name) {
  std::ifstream file(name);
  if (file.is_open()) {
    std::string line;
    while(getline(file, line)) {
      std::cout<<line<<std::endl;
    }
  }
}
