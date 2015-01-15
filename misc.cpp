#include "misc.h"

static int verbose_flag;
command_line_arguments::command_line_arguments(int argc, char **argv) {
  int c = 0, option_index = 0;
  struct option long_options[] = {
    {"verbose", no_argument, &verbose_flag, 1},
    {"threads", required_argument, 0, 'a'}
  };
  while ((c = getopt_long(argc, argv, "f:k:l:n:t:d:",
        long_options, &option_index)) != -1) {
    switch (c) {
      case 'a':
        number_of_threads = atoi(optarg);
        break;
      case 'k':
        k = atoi(optarg);
        break;
      case 'l':
        l = atoi(optarg);
        break;
      case 'n':
        n = atoi(optarg);
        break;
      case 'f':
        fasta_path = optarg;
        break;
      case 't':
        table_path = optarg;
        break;
      case 'd':
        dir_path = optarg;
        break;
      case '?':
        std::cerr<<"something went wrong, encountered ?"<<std::endl;
        break;
      default:
        abort();
    }
  }
  if (optind < argc) {
    std::cerr<<"non-option ARGV-elements (ignored):";
    while(optind < argc)
      std::cerr<<" "<<argv[optind++];
    std::cerr<<std::endl;
  }
} 

std::vector<std::string> split(const std::string line,const char delim) {
  std::stringstream s_stream(line);
  std::string segment;
  string_vector_t segment_list;
  while(getline(s_stream, segment, delim))
    segment_list.push_back(segment);
  return segment_list;
}

int power (int base, int exponent) {
  return exponent == 1 ? base : base * power(base, exponent - 1);
}
