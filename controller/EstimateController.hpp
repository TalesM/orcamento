#ifndef ORCA_CONTROLLER_ESTIMATECONTROLLER_HPP
#define ORCA_CONTROLLER_ESTIMATECONTROLLER_HPP

#include <string>

namespace orca
{
/**
*@class EstimateController
*@author Tales
*@date 09/02/2016
*@file EstimateListPresenter.hpp
*@brief Control estimate leve operations.
*/
struct EstimateController {
  /**
   * @brief Set the name
   * @param newName
   */
  virtual void setName(const std::string &newName) = 0;
};
}

#endif  // ORCA_CONTROLLER_ESTIMATECONTROLLER_HPP
