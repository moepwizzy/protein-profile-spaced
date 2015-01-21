#ifndef CLASS_PROBLEM_H
#define CLASS_PROBLEM_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "misc.h"
#include "profile.h"
#include "profile_container.h"

class class_problem {
  std::string id;
  std::vector<profile*> instances [5];
  bool no_more_instances;
 public:
  class_problem(std::string);
  bool add_instance(profile*,int);
  void instances_added();
  std::vector<profile*> get_positive_training() {
    return instances[1];
  }
  std::vector<profile*> get_negative_training() {
    return instances[2];
  }
  std::vector<profile*> get_positive_testing() {
    return instances[3];
  }
  std::vector<profile*> get_negative_testing() {
    return instances[4];
  }
  std::string get_id() { return id; }
};

std::vector<class_problem*> generate_class_problems_from_table(
    std::string, std::string, profile_container&);

#endif
