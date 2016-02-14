#ifndef ORCA_CONTROLLER_ESTIMATEVIEW_HPP
#define ORCA_CONTROLLER_ESTIMATEVIEW_HPP

#include <functional>
#include <memory>
#include <string>
#include "Operation.hpp"

namespace orca
{
// forward
class EstimateController;

/**
 * @class EstimateView
 * @author Tales
 * @date 08/02/2016
 * @file EstimateListPresenter.hpp
 * @brief
 */
struct EstimateView {
  std::string name;
  std::string category;
  Operation operation;
  unsigned estimated;
  unsigned fulfilled;
  short dueDay;
  bool done;
  const std::function<std::shared_ptr<EstimateController>()> controller;
};
}

#endif /* end of include guard: ORCA_CONTROLLER_ESTIMATEVIEW_HPP */
