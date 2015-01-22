#include "misc.h"

static int verbose_flag;
command_line_arguments::command_line_arguments(int argc, char **argv) {
  int c = 0, option_index = 0;
  k = -1, n = -1, l = -1, number_of_threads = 1;
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
        fasta_path = std::string(optarg);
        break;
      case 't':
        table_path = std::string(optarg);
        break;
      case 'd':
        dir_path = std::string(optarg);
        break;
      case '?':
        std::cerr<<"something went wrong, encountered ?"<<std::endl;
        exit(1);
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
  if (k == -1 || n == -1 || l == -1 ||
      table_path.size() == 0 || 
      dir_path.size() == 0 ) {
    std::cout<<"usage: program -k # -l # -n # "<<
      "-t path_to_casttable -d profile_dir [-f fasta_file] "<<
      "[--threads #]"<<std::endl;
    exit(1);
  }
} 

int aa_to_int (const char aa) {
  std::string alphabet("ACDEFGHIKLMNPQRSTVWY");
  return alphabet.find((char) toupper(aa));
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
