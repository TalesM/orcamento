#ifndef ORCA_CONTROLLER_BUDGETCONTROLLER_HPP
#define ORCA_CONTROLLER_BUDGETCONTROLLER_HPP

#include "EstimateView.hpp"

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
};
} /* orca */

#endif /* end of include guard: ORCA_CONTROLLER_BUDGETCONTROLLER_HPP */
