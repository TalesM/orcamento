#ifndef ORCA_CONTROLLER_MAINPRESENTER_HPP
#define ORCA_CONTROLLER_MAINPRESENTER_HPP

#include <string>
#include <stdexcept>
#include <vector>

namespace orca
{
using namespace std;
/**
 * @class MainController
 * @author Tales
 * @date 07/02/2016
 * @file MainController.hpp
 * @brief Interface to main controller
 */
class MainController
{
 public:
  MainController() {}
  virtual ~MainController() {}
  /**
   * @brief Request the budgets available, in chronological order.
   * @return the budgets names.
   */
  virtual vector<string> listBudgets() const { return {}; }
  /**
   * @brief Persists the all changes.
   *
   * @throw std::runtime_error if it can persist.
   */
  virtual void flush() {}
  /**
   * @brief Create a new budget starting at exactly where the last one ended.
   * @return the budget unique name (gennerally in the format yyyy-mm).
   *
   * @throw std::logic_error if this file type does not support budget insertion
   * @throw std::runtime_error if the budget could not be inserted due some external
   *    error. For example an IO problem. The reason should be informed in the what()
   *    method.
   */
  virtual string pushBudget() { throw logic_error("Not implemented"); }
  /**
   * @brief Remove the last budget.
   *
   * @throw std::logic_error if this file type does not support budget insertion
   * @throw std::runtime_error if it is supported but could not be done (Eg There
   *    is active estimates). The reason should be informed in the what() method.
   */
  virtual void popBudget() { throw logic_error("Not implemented"); }
};
}

#endif  // ORCA_CONTROLLER_MAINPRESENTER_HPP
