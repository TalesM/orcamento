#pragma once
#include <functional>
#include <memory>
#include <string>

namespace orca
{
// forward
class BudgetController;

/**
 * @class BudgetView
 * @author Tales
 * @date 16/02/2016
 * @file BudgetView.hpp
 * @brief A view from the current budget
 */
struct BudgetView {
  std::string name;
  /// It probably should come pre-filled by the controller.
  const std::function<std::unique_ptr<BudgetController>()> controller;
};
}
