#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
using std::string;
using std::cout;


string prepend_tab(string s);

int main(int argc, char *argv[]) {
  if (argc == 1) return 1;

  string binpath = argv[1];
  string testspath;
  if (argc == 3)
    testspath = argv[2];
  else {
    int binname_beg_pos = binpath.find_last_of("/") + 1;
    int binname_end_pos = binpath.find_last_of(".");
    int hyphen_pos = binpath.find_last_of("-");
    if (hyphen_pos > binname_beg_pos) 
      binname_end_pos = hyphen_pos;
    int binname_len = binname_end_pos - binname_beg_pos;
    testspath = binpath.substr(binname_beg_pos, binname_len) + ".test";
  }
  // std::cout << binpath << " " << testspath << "\n";

  if (!freopen(testspath.c_str(), "r", stdin)) {
    std::cerr << "there is no such file" << std::endl;
    return 1;
  }

  int test_n = 0;
  int line_n = 0;
  int last_test_p = 1;
  string in = "in.txt";
  string out = "out.txt";
  string syscall = "./" + binpath + " < " + in + " > " + out;

  string line;
  std::stringstream buffer;
  while (std::getline(std::cin, line)) {
    line_n++;
    if (line == "===") {
      test_n++;
      std::ofstream ofs{in};
      ofs << buffer.str();
      ofs.close();
      system(syscall.c_str());
      buffer.str("");
      continue;
    }
    if (line == "---") {
    check_res:
      std::ifstream res_ifs{out};
      std::stringstream ans;
      ans << res_ifs.rdbuf();
      if (buffer.str() != ans.str()) {
        cout << test_n << ". FAIL";
        cout << "\t" << testspath << ":" << last_test_p << std::endl;
        cout << "=======\n";
        string fmt = prepend_tab(ans.str());
        cout << fmt;
      } else {
        cout << test_n << ". OK" << std::endl;
      }
      buffer.str("");
      last_test_p = line_n + 1;
      continue;
    }
    buffer << line << '\n';
  }
  if (buffer.tellp() != std::streampos(0)) goto check_res;
}

string prepend_tab(string s) {
  int size = s.size() * 2;
  char *cstr = (char *)malloc(size * sizeof(char));
  int j = 0;
  cstr[j++] = '\t';
  for (size_t i = 0; i < s.size(); i++, j++) {
    cstr[j] = s[i];
    if (s[i] == '\n' && i != s.size() - 1) cstr[++j] = '\t';
  }
  string res(cstr);
  free(cstr);
  return res;
}
