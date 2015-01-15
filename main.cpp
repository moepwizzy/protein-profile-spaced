/* 
 * File:   main.cpp
 * Author: Marcus Boden
 *
 * Created on January 9, 2015,  11:00 AM
 *
 */

#include <iostream>
#include "misc.h"
#include "profile.h"
#include "profile_container.h"
#include "class_problem.h"

int main(int argc, char** argv) {
  command_line_arguments cl_args(argc, argv);
  profile_container main_container (cl_args.k, cl_args.l, cl_args.n);
  std::vector<class_problem*> cp_vector = generate_class_problems_from_table(
      cl_args.table_path, cl_args.dir_path, main_container);
  main_container.print_stuff();
  main_container.count_all_profiles();
  return 1;
}   
