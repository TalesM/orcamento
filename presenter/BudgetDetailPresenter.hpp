#pragma once

#include <memory>
#include <nana/gui/basis.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include "BudgetController.hpp"
#include "BudgetView.hpp"
#include "EstimateListPresenter.hpp"
#include "ExecutionListPresenter.hpp"
#include "ControllerOwnerPresenter.hpp"

namespace orca
{
/**
 * @class BudgetDetailPresenter
 * @author Tales
 * @date 14/02/2016
 * @file BudgetDetailPresenter.hpp
 * @brief The tab control on main.
 */
class BudgetDetailPresenter : public ControllerOwnerPresenter<BudgetController>
{
  using BASE = ControllerOwnerPresenter<BudgetController>;

 public:
  /**
   * @brief Ctor
   * @param wd
   * @param controller
   * @deprecated
   */
  BudgetDetailPresenter(nana::window wd, std::unique_ptr<BudgetController> controller);
  /**
   * @brief Ctor
   * @param wd
   * @param view
   */
  BudgetDetailPresenter(nana::window wd, const BudgetView &view) : BudgetDetailPresenter(wd, view.controller()) {}
  nana::window window() const { return t_main; }
  std::vector<nana::window> tabs() const { return {l_summary, a_estimates.window(), a_executions.window()}; }
 protected:
  void refresh() override;

 private:
  size_t a_currentControllerOwner = 0;
  EstimateListPresenter a_estimates;
  ExecutionListPresenter a_executions;

  nana::tabbar<std::string> t_main;
  nana::listbox l_summary;
};
}
