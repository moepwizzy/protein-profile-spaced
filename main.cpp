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
#include "../custom-libsvm-wrapper/libsvm_wrapper.h"
#include "../threadpool/threadpool.h"

int main(int argc, char** argv) {
  command_line_arguments cl_args(argc, argv);
  profile_container main_container (cl_args.k, cl_args.l, cl_args.n);
  std::vector<class_problem*> cp_vector = generate_class_problems_from_table(
      cl_args.table_path, cl_args.dir_path, main_container);
  main_container.count_all_profiles(cl_args.number_of_threads);
  for(std::vector<class_problem*>::iterator problem_it = cp_vector.begin();
      problem_it != cp_vector.end(); ++problem_it) {
    libsvm problem;
    std::vector<profile*> data_points = (*problem_it)->get_positive_training();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem.addTrainSeq((*it)->get_representing_vector(),POS);
    data_points = (*problem_it)->get_negative_training();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem.addTrainSeq((*it)->get_representing_vector(),NEG);
    data_points = (*problem_it)->get_positive_testing();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem.addTrainSeq((*it)->get_representing_vector(),POS);
    data_points = (*problem_it)->get_negative_testing();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem.addTrainSeq((*it)->get_representing_vector(),NEG);
    if(!problem.prepare()) {
        print("prepare failed");
        exit(1);
    }
    if(!problem.train()) {
        print("train failed");
        exit(1);
    }
    std::cout<<(*problem_it)->get_id()<<": "<<problem.evaluate()<<std::endl;
  }
  return 1;
} 
