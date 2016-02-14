#ifndef ORCA_PRESENTER_EXECUTIONLISTPRESENTER_HPP
#define ORCA_PRESENTER_EXECUTIONLISTPRESENTER_HPP

#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include "BudgetController.hpp"

namespace orca
{
/**
 * @class ExecutionListPresenter
 * @author Tales
 * @date 14/02/2016
 * @file ExecutionListPresenter.hpp
 * @brief Shows the execution list.
 */
class ExecutionListPresenter
{
 public:
  /**
   * @brief Ctor
   * @param wd
   * @param controller
   */
  ExecutionListPresenter(nana::window wd, std::unique_ptr<BudgetController> controller);

  /**
   * @brief Insert a new execution.
   */
  void insertExecution();
  
  /**
   * @brief Remove selected executions.
   */
  void deleteSelectedExecutions();

 private:
  void refresh();
  std::unique_ptr<BudgetController> a_controller;

  nana::listbox l_executions;
  nana::place placer;
};
}

#endif  // ORCA_PRESENTER_EXECUTIONLISTPRESENTER_HPP
