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

struct train_struct {
  libsvm *problem;
  std::vector<double> *results;
  int problem_number;
  train_struct(libsvm *p, std::vector<double> *r, int n) 
    : problem(p), results(r), problem_number(n) {}; 
};

void thread_train (void * prob_ptr) {
  train_struct *tr_str = (train_struct *) prob_ptr;
  libsvm *problem = tr_str->problem;
  if(!problem->prepare()) {
      print("prepare failed");
      exit(1);
  }
  if(!problem->train()) {
      print("train failed");
      exit(1);
  }
  double result = problem->evaluate();
  (*tr_str->results)[tr_str->problem_number] = result < 0.5 ? 1 - result : result; 
  print((*tr_str->results)[tr_str->problem_number]);
  delete problem;
}

int main(int argc, char** argv) {
  command_line_arguments cl_args(argc, argv);
  profile_container main_container (cl_args.k, cl_args.l, cl_args.n);
  main_container.read_fasta_file(cl_args.fasta_path);
  std::vector<class_problem*> cp_vector = generate_class_problems_from_table(
      cl_args.table_path, cl_args.dir_path, main_container);
  main_container.count_all_profiles(cl_args.number_of_threads);
  threadpool pool (cl_args.number_of_threads);
  std::vector<double> results (cp_vector.size(),-1);
  for(unsigned int i = 0; i < cp_vector.size(); ++i) {
    libsvm *problem = new libsvm;
    std::vector<profile*> data_points = cp_vector[i]->get_positive_training();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem->addTrainSeq((*it)->get_representing_vector(),POS);
    data_points = cp_vector[i]->get_negative_training();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem->addTrainSeq((*it)->get_representing_vector(),NEG);
    data_points = cp_vector[i]->get_positive_testing();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem->addTestSeq((*it)->get_representing_vector(),POS);
    data_points = cp_vector[i]->get_negative_testing();
    for (std::vector<profile*>::iterator it = data_points.begin();
        it != data_points.end(); ++it)
      problem->addTestSeq((*it)->get_representing_vector(),NEG);
    pool.addThread(thread_train, 
        (void *) new train_struct(problem, &results, i));
  }
  pool.wait();
  double avg_roc = 0;
  for (std::size_t i = 0; i < results.size(); ++i)
    avg_roc += results[i];
  print(avg_roc/results.size());
  return 1;
} 
