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
  virtual std::vector<EstimateView> listEstimates() const = 0;
  virtual void insertEstimate(const EstimateView &) = 0;
  virtual void eraseEstimates(const std::unordered_set<std::string> &) = 0;
  virtual std::unique_ptr<EstimateController> selectEstimate(const std::string &) = 0;
};
} /* orca */

#endif /* end of include guard: ORCA_CONTROLLER_BUDGETCONTROLLER_HPP */
