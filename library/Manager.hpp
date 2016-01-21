#ifndef ORCA_MANAGER_HPP
#define ORCA_MANAGER_HPP

#include <stdexcept>

namespace orca {
class Manager {
private:
  /* data */
public:
  void open(const char *s) {
    throw std::logic_error("No File Type registered.");
  }

  void register_filetype(const char *identifier,
                         std::function<void()> initializer) {
    /**/
  }
};
} /* orca */

#endif /* end of include guard: ORCA_MANAGER_HPP */
