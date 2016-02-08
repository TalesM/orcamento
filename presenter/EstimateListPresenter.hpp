#ifndef ORCA_PRESENTER_ESTIMATEPRESENTER_HPP
#define ORCA_PRESENTER_ESTIMATEPRESENTER_HPP

#include <memory>
#include <unordered_set>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/place.hpp>
#include "Presenter.hpp"  // Base class: Presenter

namespace orca
{
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

/**
 * @class BudgetController
 * @author Tales
 * @date 08/02/2016
 * @file EstimateListPresenter.hpp
 * @brief
 */
struct BudgetController {
  virtual std::vector<EstimateView> listEstimates() const = 0;
  virtual void insertEstimate(const EstimateView &) = 0;
  virtual void eraseEstimates(const std::unordered_set<std::string> &) = 0;
};
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
