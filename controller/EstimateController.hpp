#ifndef ORCA_CONTROLLER_ESTIMATECONTROLLER_HPP
#define ORCA_CONTROLLER_ESTIMATECONTROLLER_HPP

#include <string>
#include "EstimateView.hpp"

namespace orca
{
/**
*@class EstimateController
*@author Tales
*@date 09/02/2016
*@file EstimateListPresenter.hpp
*@brief Control estimate level operations.
*/
struct EstimateController {
  /**
   * @brief Change the name.
   * @param newName
   * @throw std::runtime_error if the name was taken by another estimate in same budget.
   */
  virtual void setName(const std::string &newName) = 0;
  /**
   * @brief Change category.
   * @param newCategory
   * @throw std::runtime_error if the category did not exists.
   */
  virtual void setCategory(const std::string &newCategory) = 0;
  /**
   * @brief Changes operation.
   * @param operation
   */
  virtual void setOperation(const Operation &operation) = 0;
  /**
   * @brief Change the estimated value.
   * @param value
   */
  virtual void setEstimated(unsigned value) = 0;
  /**
   * @brief Change the due day
   * @param value
   * throw runtime_error if the value is outside [1,31].
   */
  virtual void setDueDay(short value) = 0;
  /**
   * @brief Changes done flag.
   * @param value
   */
  virtual void setDone(bool value) = 0;
};
}

#endif  // ORCA_CONTROLLER_ESTIMATECONTROLLER_HPP
