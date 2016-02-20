#ifndef ORCA_PRESENTER_MAINPRESENTER_HPP
#define ORCA_PRESENTER_MAINPRESENTER_HPP

#include <experimental/optional>
#include <functional>
#include <memory>

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/tabbar.hpp>

#include "BudgetSummaryPresenter.hpp"
#include "EstimateListPresenter.hpp"
#include "ExecutionListPresenter.hpp"
#include "FormPresenter.hpp"

namespace orca
{
// Forward Declaration
class BudgetController;
class MainController;
class Manager;

/**
 * @class MainPresenter
 * @author Tales
 * @date 06/02/2016
 * @file MainPresenter.hpp
 * @brief Owns the app main frame
 */
class MainPresenter : public FormPresenter
{
  using LoadErrorCallback = function<void()>;
  using LoadSuccessCallback = function<void(MainController &)>;
  enum Tab { SUMMARY, ESTIMATE, EXECUTION };

 public:
  MainPresenter(Manager &manager, const std::string &file_path = "");
  MainPresenter(const MainPresenter &) = delete;
  MainPresenter(MainPresenter &&) = delete;
  ~MainPresenter();
  MainPresenter &operator=(const MainPresenter &) = delete;
  MainPresenter &operator=(MainPresenter &&) = delete;

  experimental::optional<reference_wrapper<MainController>> controller() const
  {
    if(a_controller) {
      return experimental::make_optional(ref(*a_controller));
    } else {
      return experimental::nullopt;
    }
  }
  /**
   * @brief Callback for when the file loading error
   * @param callback the callback
   *
   * The nullptr is generally because user canceling. The Presenter requires a MainController to run, so it
   * will continue to use the older one or just exit after the callback in case there was none.
   */
  void onLoadError(LoadErrorCallback callback) { a_load_error_callback = callback; }
  LoadErrorCallback onLoadError() const { return a_load_error_callback; }
  /**
   * @brief Callback for when a file is loaded successfully.
   * @param callback Receives the new MainController as an unique_ptr.
   */
  void onLoadSuccess(LoadSuccessCallback callback) { a_load_success_callback = callback; }
  LoadSuccessCallback onLoadSuccess() const { return a_load_success_callback; }
  /**
   * @brief Shows
   */
  void present() override;

  void close();

 protected:
  void activate(Tab tab);
  std::unique_ptr<BudgetController> popBudgetController(Tab tab);
  void pushBudgetController(Tab tab, std::unique_ptr<BudgetController>controller);
  void insertExecution();
  void editExecution();
  void deleteExecution();

 private:
  void refreshBudgetList();
  void createMenu();
  void createLayout();

  LoadErrorCallback a_load_error_callback;
  LoadSuccessCallback a_load_success_callback;
  Manager &a_manager;
  unique_ptr<MainController> a_controller;
  Tab a_currentControllerOwner = SUMMARY;

  // UI
  nana::form f_main;
  nana::listbox l_budgets;

  nana::tabbar<std::string> t_main;
  BudgetSummaryPresenter a_budgetDetail;
  EstimateListPresenter a_estimates;
  ExecutionListPresenter a_executions;
  nana::menubar mb_main;
  nana::place placer;
};
}

#endif  // ORCA_PRESENTER_MAINPRESENTER_HPP
