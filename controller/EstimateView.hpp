#ifndef ORCA_CONTROLLER_ESTIMATEVIEW_HPP
#define ORCA_CONTROLLER_ESTIMATEVIEW_HPP

#include <string>
namespace orca {
/**
 * @brief Define the possible operations you can estimate.
 */
enum class Operation {
  INCOME = 1,
  EXPENSE = 2,
  EXCHANGE = 3,
};

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
};
}

#endif /* end of include guard: ORCA_CONTROLLER_ESTIMATEVIEW_HPP */
