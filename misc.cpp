#include "misc.h"

command_line_arguments::command_line_arguments(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
//    char *param = argv[i];
//    while(*param != '\0')
//      std::cout<<*param++;
    std::cout<<argv[i]<<std::endl;
  }
}
  
