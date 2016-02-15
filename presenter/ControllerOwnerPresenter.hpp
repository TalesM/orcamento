#pragma once

#include <memory>

namespace orca
{
/**
 * @class ControllerOwnerPresenter
 * @author Tales
 * @date 15/02/2016
 * @file ControllerOwnerPresenter.hpp
 * @brief Base class for all unique_ptr owner classes
 */
template <typename CONTROLLER>
class ControllerOwnerPresenter
{
 public:
  using ControllerPointer = std::unique_ptr<CONTROLLER>;
  ControllerOwnerPresenter(ControllerPointer c) : a_controller(move(c)) {}
  /**
   * @brief Takes ownership of the controller
   * @param controller
   */
  void receive(std::unique_ptr<BudgetController> controller)
  {
    a_controller = std::move(controller);
    refresh();
  }

  /**
   * @brief Returns ownership of the controller
   * @return controller
   */
  std::unique_ptr<BudgetController> devolve() { return std::move(a_controller); }
 protected:
  /**
   * @brief Refresh from controller.
   */
  virtual void refresh() = 0;
  ControllerPointer a_controller;
};
}
