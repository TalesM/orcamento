#ifndef ORCA_CONTROLLER_EXECUTIONVIEW_HPP
#define ORCA_CONTROLLER_EXECUTIONVIEW_HPP

#include <functional>
#include <memory>
#include <string>
#include "Operation.hpp"

namespace orca
{
// Forward Decl;
class ExecutionController;
/**
 * @class ExecutionView
 * @author Tales
 * @date 14/02/2016
 * @file ExecutionView.hpp
 * @brief ExecutionView
 */
struct ExecutionView {
  unsigned code;
  std::string date;
  unsigned amount;
  Operation operation;
  std::string account;
  std::string estimate;
  std::string category;
  std::function<std::unique_ptr<ExecutionController>()> controller;
};
}

#endif  // ORCA_CONTROLLER_EXECUTIONVIEW_HPP
