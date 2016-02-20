#pragma once

#include <memory>
#include <nana/gui/basis.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include "BudgetController.hpp"
#include "BudgetView.hpp"
#include "ControllerOwnerPresenter.hpp"

namespace orca
{
/**
 * @class BudgetSummaryPresenter
 * @author Tales
 * @date 14/02/2016
 * @file BudgetDetailPresenter.hpp
 * @brief Controls the summary
 */
class BudgetSummaryPresenter : public ControllerOwnerPresenter<BudgetController>
{
  using BASE = ControllerOwnerPresenter<BudgetController>;

 public:
  /**
   * @brief Ctor
   * @param wd
   * @param controller
   * @deprecated
   */
  BudgetSummaryPresenter(nana::window wd, std::unique_ptr<BudgetController> controller);
  /**
   * @brief Ctor
   * @param wd
   * @param view
   */
  BudgetSummaryPresenter(nana::window wd, const BudgetView &view) : BudgetSummaryPresenter(wd, view.controller()) {}
  nana::window window() const { return l_summary; }

 protected:
  void refresh() override;

 private:
  nana::listbox l_summary;
};
}
