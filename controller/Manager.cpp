#include "Manager.hpp"
#include <algorithm>

namespace orca {
using namespace std;

std::unique_ptr<MainController> Manager::open(const std::string &test) {
  if (a_initializers.size() == 0) {
    throw std::logic_error("No File Type registered.");
  }
  smatch match;
  auto predicate = [&test, &match](auto &re) {
    return regex_match(test, match, re.a_regex);
  };
  auto initializer =
      find_if(a_initializers.begin(), a_initializers.end(), predicate);
  if (initializer == a_initializers.end()) {
    throw std::runtime_error("Files does not match any recognizable type.");
  }
  return initializer->a_initializer(match);
}

bool Manager::is_registered(const std::string &test) const {
  if (a_initializers.size() == 0 or
      find_if(a_initializers.begin(), a_initializers.end(), [test](auto &re) {
        return regex_match(test, re.a_regex);
      }) == a_initializers.end()) {
    return false;
  }
  return true;
}

} /* orca */
