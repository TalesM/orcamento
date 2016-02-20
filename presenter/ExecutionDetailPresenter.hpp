#pragma once
#include <nana/gui.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include "FormPresenter.hpp"
#include "ExecutionController.hpp"
#include "ExecutionView.hpp"

namespace orca
{
/**
 * @class ExecutionDetailPresenter
 * @author Tales
 * @date 16/02/2016
 * @file ExecutionDetailPresenter.hpp
 * @brief The execution editor
 */
class ExecutionDetailPresenter : public FormPresenter
{
 public:
  ExecutionDetailPresenter(const ExecutionView &view);
  ExecutionDetailPresenter(nana::window wd);

  void present() override;

  void reset(const ExecutionView &view);
  ExecutionView get();

  /**
   * @brief Update the accounts
   * @param begin iterator to first member
   * @param end iterator to first past last member
   * @tparam INPUT_ITER Any input iterator class whose value is convertible to string.
   */
  template <typename INPUT_ITER>
  void accounts(INPUT_ITER begin, INPUT_ITER end)
  {
    while(begin != end) {
      c_account.push_back(*(begin++));
    }
  }
  
    /**
   * @brief Update the categories
   * @param begin iterator to first member
   * @param end iterator to first past last member
   * @tparam INPUT_ITER Any input iterator class whose value is convertible to string.
   */
  template <typename INPUT_ITER>
  void categories(INPUT_ITER begin, INPUT_ITER end)
  {
    while(begin != end) {
      c_category.push_back(*(begin++));
    }
  }
  
    /**
   * @brief Update the estimates
   * @param begin iterator to first member
   * @param end iterator to first past last member
   * @tparam INPUT_ITER Any input iterator class whose value is convertible to string.
   */
  template <typename INPUT_ITER>
  void estimates(INPUT_ITER begin, INPUT_ITER end)
  {
    while(begin != end) {
      c_estimate.push_back(*(begin++));
    }
  }

 private:
  // Controller:
  ExecutionView a_view;
  std::unique_ptr<ExecutionController> a_controller;

  // The form
  nana::form f_main;
  nana::label l_code;
  nana::textbox t_code;
  nana::label l_date;
  nana::textbox t_date;
  nana::label l_amount;
  nana::textbox t_amount;
  nana::label l_operation;
  nana::combox c_operation;
  nana::label l_account;
  nana::combox c_account;
  nana::label l_estimate;
  nana::combox c_estimate;
  nana::label l_category;
  nana::combox c_category;

  // The layout
  nana::place placer;
};
}
