/* 
 * File:   main.cpp
 * Author: Marcus Boden
 *
 * Created on January 9, 2015,  11:00 AM
 *
 */

#include "misc.h"
#include <iostream>

int main(int argc, char** argv) {
  command_line_arguments test(argc, argv);
  std::cout<<test.k<<" "<<std::endl;
  std::cout<<test.l<<" "<<std::endl;
  std::cout<<test.n<<" "<<std::endl;
  std::cout<<test.table_path<<" "<<std::endl;
  std::cout<<test.fasta_path<<" "<<std::endl;
  std::cout<<test.number_of_threads<<" "<<std::endl;
  return 1;
}
