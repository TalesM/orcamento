#ifndef ORCA_CONTROLLER_BUDGETCONTROLLER_HPP
#define ORCA_CONTROLLER_BUDGETCONTROLLER_HPP

#include <string>
#include <unordered_set>
#include "EstimateView.hpp"
#include "ExecutionView.hpp"

namespace orca
{
// forward
class EstimateController;

/**
 * @class BudgetController
 * @author Tales
 * @date 08/02/2016
 * @file EstimateListPresenter.hpp
 * @brief Control budget level operations.
 */
struct BudgetController {
  ///@name EstimateMethods
  ///@{
  /**
   * @brief Returns a instantaneous view of all estimates of present budget.
   */
  virtual std::vector<EstimateView> listEstimates() const = 0;
  /**
   * @brief Create a new estimate. The actual creating can be deferred.
   */
  virtual EstimateView insertEstimate() = 0;
  /**
   * @brief Erase all the given estimates
   */
  virtual void eraseEstimates(const std::unordered_set<std::string> &) = 0;
  /**
   * @brief Get estimate by name
   * @param name
   */
  virtual EstimateView getEstimateByName(const std::string &name) = 0;

  ///@}
  ///@name ExecutionMethods
  ///@{
  /**
   * @brief Returns a instantaneous view of all execution of present budget.
   */
  virtual std::vector<ExecutionView> listExecutions() const = 0;
  /**
   * @brief Create a new execution. The actual creating can be deferred.
   */
  virtual ExecutionView insertExecution() = 0;
  /**
   * @brief Erase all given execution codes
   */
  virtual void eraseExecutions(const std::unordered_set<std::string> &) = 0;
  ///@}
};
} /* orca */

#endif /* end of include guard: ORCA_CONTROLLER_BUDGETCONTROLLER_HPP */
