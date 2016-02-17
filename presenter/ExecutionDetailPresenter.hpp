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

  void present() override;

  void reset(const ExecutionView &view);
  ExecutionView get();

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
