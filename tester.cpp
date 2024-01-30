#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

std::string string_insert_tab(std::string s);

int main(int argc, char *argv[]) {
  if (argc == 1) return 1;

  std::string bin = argv[1];

  std::string tests;
  int file_s = bin.find_last_of("/") + 1;
  int file_e = bin.find_last_of(".");
  if (argc == 2) {
    tests = bin.substr(file_s, file_e - file_s) + ".test";
  } else
    tests = argv[2];

  // std::cout << bin << " " << tests << "\n";

  if (!freopen(tests.c_str(), "r", stdin)) {
    std::cerr << "there is no such file" << std::endl;
    return 1;
  }

  unsigned int test_n = 0;
  unsigned int line_n = 0;
  unsigned int last_test_line_n = 1;
  std::string in = "in.txt";
  std::string out = "out.txt";
  std::string syscall = "./" + bin;

  std::string line;
  std::stringstream buffer;
  while (std::getline(std::cin, line)) {
    line_n++;
    if (line.compare("===") == 0) {
      test_n++;
      std::ofstream ofs(in);
      ofs << buffer.str();
      ofs.close();
      system(syscall.c_str());
      buffer.str("");
      continue;
    }
    if (line.compare("---") == 0) {
    check_res:
      std::ifstream ifs(out);
      std::stringstream ans;
      ans << ifs.rdbuf();
      if (buffer.str() != ans.str()) {
        std::cout << test_n << ". FAIL";
        std::cout << "\t" << tests << ":" << last_test_line_n << std::endl;
        std::cout << "=======\n";
        std::string fmt = string_insert_tab(ans.str());
        std::cout << fmt;
      } else {
        std::cout << test_n << ". OK" << std::endl;
      }
      buffer.str("");
      last_test_line_n = line_n + 1;
      continue;
    }
    buffer << line << '\n';
  }
  if (buffer.tellp() != std::streampos(0)) goto check_res;
}

std::string string_insert_tab(std::string s) {
  int size = s.size() * 2;
  char *cstr = (char *)malloc(size * sizeof(char));
  int j = 0;
  cstr[j++] = '\t';
  for (int i = 0; i < s.size(); i++, j++) {
    cstr[j] = s[i];
    if (s[i] == '\n' && i != s.size() - 1) cstr[++j] = '\t';
  }
  std::string res(cstr);
  free(cstr);
  return res;
}
