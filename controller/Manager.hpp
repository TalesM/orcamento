#ifndef ORCA_MANAGER_HPP
#define ORCA_MANAGER_HPP

#include <functional>
#include <list>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>

namespace orca {

struct Planner {
public:
  virtual ~Planner() = default;
private:
  bool a_member;
  /* data */
};

class Manager {
private:
  using Initializer =
      std::function<std::unique_ptr<Planner>(const std::smatch &)>;
  struct InitializerData {
    std::regex a_regex;
    Initializer a_initializer;
    InitializerData(const std::string &pattern, Initializer initializer)
        : a_regex(pattern, std::regex_constants::icase |
                               std::regex_constants::ECMAScript),
          a_initializer(initializer) {}
  };
  std::list<InitializerData> a_initializers;

public:
  std::unique_ptr<Planner> open(const std::string &test);

  void register_filetype(const std::string &pattern, Initializer initializer) {
    a_initializers.emplace_back(pattern, initializer);
  }

  bool is_registered(const std::string &test) const;
};
} /* orca */

#endif /* end of include guard: ORCA_MANAGER_HPP */
