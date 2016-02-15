#ifndef ORCA_PRESENTER_ESTIMATEPRESENTER_HPP
#define ORCA_PRESENTER_ESTIMATEPRESENTER_HPP

#include <memory>
#include <unordered_set>
#include <nana/gui/widgets/listbox.hpp>

#include "BudgetController.hpp"
#include "ControllerOwnerPresenter.hpp"

namespace orca
{

/**
 * @class EstimatePresenter
 * @author Tales
 * @date 08/02/2016
 * @file EstimatePresenter.hpp
 * @brief Presents the estimates view.
 */
class EstimateListPresenter : public ControllerOwnerPresenter<BudgetController>
{
  using BASE = ControllerOwnerPresenter<BudgetController>;

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
  
  /**
   * @brief Edit the selected estimate
   */
  void editSelectedEstimate();
  
  /**
   * @brief The window
   * @return 
   */
  nana::window window() const { return l_estimates; }


 private:
  void refresh();
  nana::listbox l_estimates;
};
}

#endif  // ORCA_PRESENTER_ESTIMATEPRESENTER_HPP
