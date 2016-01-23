#include "Manager.hpp"
#include <algorithm>

namespace orca {
using namespace std;

void Manager::open(const std::string &test) {
  if (a_initializers.size() == 0) {
    throw std::logic_error("No File Type registered.");
  } else if (find(a_initializers.begin(), a_initializers.end(), test) ==
             a_initializers.end()) {
    throw std::runtime_error("Files does not match any recognizable type.");
  }
}
} /* orca */
