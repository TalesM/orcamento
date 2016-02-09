#ifndef ORCA_PRESENTER_ESTIMATEPRESENTER_HPP
#define ORCA_PRESENTER_ESTIMATEPRESENTER_HPP

#include <memory>
#include <unordered_set>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/place.hpp>

#include "BudgetController.hpp"
#include "Presenter.hpp"  // Base class: Presenter

namespace orca
{

/**
 * @class EstimatePresenter
 * @author Tales
 * @date 08/02/2016
 * @file EstimatePresenter.hpp
 * @brief Presents the estimates view.
 */
class EstimateListPresenter : public Presenter
{
 public:
  EstimateListPresenter(nana::window wd, std::unique_ptr<BudgetController> controller);

  /**
   * @brief Creates a new estimate.
   */
  void newEstimate();
  /**
   * @brief Remove the given estimates
   */
  void deleteSelectedEstimates();

 private:
  void refresh();
  std::unique_ptr<BudgetController> a_controller;

  nana::listbox l_estimates;
  nana::place placer;
};
}

#endif  // ORCA_PRESENTER_ESTIMATEPRESENTER_HPP
