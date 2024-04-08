#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using std::string;

/*
  Allows to create several versions of the solution by postfixing 
  after a hyphen while keeping the testsfile with the same name: 
    dfs-iter.py
    dfs-rec.py
    dfs.test
*/
string get_testspath(int argc, char *argv[]) {
  if (argc == 3) 
    return argv[2];
  string binpath = argv[1];
  int binname_beg_pos = binpath.find_last_of("/") + 1;
  int binname_end_pos = binpath.find_last_of(".");
  int hyphen_pos = binpath.find_last_of("-");
  if (hyphen_pos > binname_beg_pos) 
    binname_end_pos = hyphen_pos;
  int binname_len = binname_end_pos - binname_beg_pos;
  return binpath.substr(binname_beg_pos, binname_len) + ".test";
}

string rstripws(string line) {
  auto end_it = line.rbegin();
  while (std::isspace(*end_it)) ++end_it;
  return std::string(line.begin(), end_it.base());
}

string add_indentation(string s) {
  string fmt = s;
  for (size_t i = 0; i < fmt.size() - 1; i++) {
    if (fmt[i] == '\n') i++;
    fmt.insert(i, "\t");
  }
  return fmt;
}

const string test_in = "test_in.txt";
const string test_out = "test_out.txt";
const string key_input = "---";
const string key_solution = "===";

int main(int argc, char *argv[]) {
  if (argc == 1) return 1;

  string binpath = argv[1];
  string testspath = get_testspath(argc, argv);
  if (!freopen(testspath.c_str(), "r", stdin)) {
    std::cerr << "there is no such file: " << testspath << std::endl;
    return 1;
  }

  int test_n = 0;
  int line_n = 0;
  int last_test_pointer = 1;
  string syscall = "./" + binpath + " < " + test_in + " > " + test_out;

  string line;
  std::stringstream buffer;
  while (std::getline(std::cin, line)) {
    line = rstripws(line);
    line_n++;
    if (line == key_solution) {
      test_n++;
      std::ofstream ofs{test_in};
      ofs << buffer.str();
      ofs.close();
      system(syscall.c_str());
      buffer.str("");
      continue;
    }
    if (line == key_input) {
    check_res:
      std::ifstream res_ifs{test_out};
      std::stringstream ans;
      ans << res_ifs.rdbuf();
      using std::cout;
      if (buffer.str() == ans.str())
        cout << test_n << ". OK" << std::endl;
      else {
        cout << test_n << ". FAIL";
        cout << "\t" << testspath << ":" << last_test_pointer << std::endl;
        cout << "=======\n";
        cout << add_indentation(ans.str());
      } 
      buffer.str("");
      last_test_pointer = line_n + 1;
      continue;
    }
    buffer << line << '\n';
  }
  if (buffer.tellp() != std::streampos(0)) goto check_res;
}
