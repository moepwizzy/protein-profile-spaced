#include "class_problem.h"

class_problem::class_problem(std::string id_s) {
  id = id_s;
  no_more_instances = false;
}

bool class_problem::add_instance(profile *prof, int label) {
  if (no_more_instances || label < 0 || label > 5) {
    std::cerr<<"Instance "<<prof->get_name()<<" could not be added to "
      <<id<<std::endl;
    return false;
  }
  instances[label].push_back(prof);
  return true;
}

void class_problem::instances_added() {
  no_more_instances = true;
}

std::vector<class_problem*> generate_class_problems_from_table(
    std::string table_p, std::string dir,
    std::string fasta_p, profile_container &profiles) {
  std::ifstream file(table_p.c_str());
  std::string line;
  std::vector<class_problem*> problem_vector;
// First line: IDs of class_problems
  getline(file, line);
  string_vector_t split_line = split(line, ' ');
  split_line.erase(split_line.begin());
  for (string_vector_t::iterator it = split_line.begin();
      it != split_line.end(); ++it)
    problem_vector.push_back(new class_problem(*it));
// One profile per line, add to class_problems according to label
  while(getline(file, line)) {
    split_line = split(line, ' ');
    profile *current_profile = new profile(split_line.front(), dir);
    if (current_profile->is_valid() || 
        current_profile->generate_from_fasta(fasta_p) ) {
      profiles.add_profile(current_profile);
      split_line.erase(split_line.begin());
      for (std::size_t i = 0; i < problem_vector.size(); ++i)
        problem_vector.at(i)->add_instance(current_profile,
            atoi(split_line.at(i).c_str()));
    } else {
      std::cerr<<"could not generate Profile for "<<
        current_profile->get_name()<<std::endl;
      delete current_profile;
    }
  }
  for (std::vector<class_problem*>::iterator it = problem_vector.begin();
      it != problem_vector.end(); ++it)
    (*it)->instances_added();
  return problem_vector;
}
