#ifndef ORCA_CONTROLLER_MAINPRESENTER_HPP
#define ORCA_CONTROLLER_MAINPRESENTER_HPP

#include <string>
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
  virtual vector<string> listBudgets() const {return {};}
  
  /**
   * @brief Persists the all changes.
   * 
   * @throw std::runtime_error if it can persist.
   */
  virtual void flush(){}
};
}

#endif  // ORCA_CONTROLLER_MAINPRESENTER_HPP
