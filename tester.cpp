#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
#include <iomanip>
#include <sstream>

using std::string;


/**
 * Allows to create several versions of the solution by postfixing 
 * after a hyphen while keeping the testsfile with the same name: 
 *   dfs-iter.py
 *   dfs-rec.py
 *   dfs.test
*/
string get_testspath(int argc, char *argv[]) {
  if (argc == 3) 
    return argv[2];
  string bin_path = argv[1];
  int binname_beg_pos = bin_path.find_last_of("/") + 1;
  int binname_end_pos = bin_path.find_last_of(".");
  int hyphen_pos = bin_path.find_last_of("-");
  if (hyphen_pos > binname_beg_pos) 
    binname_end_pos = hyphen_pos;
  int binname_len = binname_end_pos - binname_beg_pos;
  return bin_path.substr(binname_beg_pos, binname_len) + ".test";
}

string rstripws(string line) {
  auto end_it = line.rbegin();
  while (std::isspace(*end_it)) ++end_it;
  return std::string(line.begin(), end_it.base());
}

string keep_escapes(std::string_view line) {
  string fmt = line.data();
  for (size_t i = 0; i < fmt.size(); i++) {
    char ch = fmt[i];
    switch (ch) {
      case '\n': fmt.replace(i, 2, "\\n"); i++; break;
      case '\t': fmt.replace(i, 2, "\\n"); i++; break;
    }
  }
  return fmt;
}

string add_indentation(string s) {
  string fmt = "\t" + s;
  for (size_t i = 1; i < fmt.size() - 1; i++)
    if (fmt[i] == '\n') {
      i++;
      fmt.insert(i, "\t");
    }
  return fmt;
}

const string test_in = "in.txt";
const string test_out = "out.txt";
const string key_input = "---";
const string key_solution = "===";

int main(int argc, char *argv[]) {
  if (argc == 1) return 1;

  const string bin_path = argv[1];
  const string tests_path = get_testspath(argc, argv);
  if (!freopen(tests_path.c_str(), "r", stdin)) {
    std::cerr << "there is no such file: " << tests_path << std::endl;
    return 1;
  }
  const string syscall = "./" + bin_path + " < " + test_in + " > " + test_out;

  int test_n = 0;
  int line_n = 0;
  int last_test_pointer = 1;
  string line, line_next;
  std::stringstream buffer;

  std::getline(std::cin, line);
  while (!std::cin.eof()) {
    line = rstripws(line);
    line_n++;

    if (line != key_input && line != key_solution)
      buffer << line << '\n';
    
    if (line == key_solution) {
      test_n++;
      std::ofstream ofs{test_in};
      ofs << buffer.str();
      ofs.close();
      system(syscall.c_str());
      buffer.str("");
    }
    
    std::getline(std::cin, line_next);

    if (line == key_input || std::cin.eof()) {
      std::ifstream res_ifs{test_out};
      std::stringstream ans;
      ans << res_ifs.rdbuf();
      using std::cout;
#ifdef DEBUGGING
      std::cerr << "ref:\n" << std::quoted(keep_escapes(buffer.str())) << '\n';
      std::cerr << "res:\n" << std::quoted(keep_escapes(ans.str())) << '\n';
#endif
      if (buffer.str() == ans.str())
        cout << test_n << ". OK" << std::endl;
      else {
        cout << test_n << ". FAIL";
        cout << "\t" << tests_path << ":" << last_test_pointer << std::endl;
        cout << "=======\n";
        cout << add_indentation(ans.str());
      } 
      buffer.str("");
      last_test_pointer = line_n + 1;
    }
    
    line = line_next;
  }
}
