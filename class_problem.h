#ifndef CLASS_PROBLEM_H
#define CLASS_PROBLEM_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "misc.h"
#include "profile.h"

class class_problem {
  std::string id;
  std::vector<profile*> instances [5];
  bool no_more_instances;
 public:
  class_problem(std::string);
  bool add_instance(profile*,int);
  void instances_added();
};

std::vector<class_problem*> generate_class_problems_from_table(char*, char*);

#endif
