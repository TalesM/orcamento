#ifndef ORCA_MANAGER_HPP
#define ORCA_MANAGER_HPP

#include <functional>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>

namespace orca {

struct Planner {
private:
  bool a_member;
  /* data */
};

class Manager {
private:
  std::list<std::string> a_initializers;

public:
  void *open(const std::string &test);

  void
  register_filetype(const std::string &pattern,
                    std::function<std::unique_ptr<Planner>()> initializer) {
    a_initializers.emplace_back(pattern);
  }

  bool is_registered(const std::string &pattern) const { return true; }
};
} /* orca */

#endif /* end of include guard: ORCA_MANAGER_HPP */
