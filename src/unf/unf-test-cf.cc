#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "normalizer.hh"

bool cf_test(const std::vector<std::string>& ary, UNF::Normalizer& norm, int entry_id) {
  const char *correct = ary[1].c_str();
  const char *target = norm.nfkc_cf(ary[0].c_str());
  int test = strcmp(correct, target);
  if(test != 0) {
    std::cerr << "Failed(" << entry_id << "): NFKC_CF" << std::endl;
    std::cerr << " `" << ary[0] << "`\t -> `" << target
              << "`\t (expected: `" << correct << "`)" << std::endl;
    return false;
  }
  return true;
}

/**
 * main
 */
int main(int argc, char** argv) {
  if(argc != 1) {
    std::cerr << "Usage: unf-test-cf" << std::endl;
    return 1;
  }

  UNF::Normalizer norm;

  unsigned cnt=0;
  std::vector<std::string> ary;
  std::string line;
  while(std::getline(std::cin, line)) {
    if(ary.size()==2) {
      cnt++;
      if(cf_test(ary, norm, cnt)==false)
	return 1;
      ary.clear();
    } else {
      ary.push_back(line);
    }
  }
  if(ary.size()==2) {
    cnt++;
    if(cf_test(ary, norm, cnt)==false)
      return 1;
  }

  std::cerr << "All tests passed!: " << cnt << " entries" << std::endl << std::endl;
  return 0;
}
