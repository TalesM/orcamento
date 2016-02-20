#include "ExecutionDetailPresenter.hpp"

using namespace nana;
using namespace orca;

orca::ExecutionDetailPresenter::ExecutionDetailPresenter(const ExecutionView& view) : ExecutionDetailPresenter(nullptr)
{
  reset(view);
}

orca::ExecutionDetailPresenter::ExecutionDetailPresenter(nana::window wd)
    : f_main(wd)
    , l_code(f_main)
    , t_code(f_main)
    , l_date(f_main)
    , t_date(f_main)
    , l_amount(f_main)
    , t_amount(f_main)
    , l_operation(f_main)
    , c_operation(f_main)
    , l_account(f_main)
    , c_account(f_main)
    , l_estimate(f_main)
    , c_estimate(f_main)
    , l_category(f_main)
    , c_category(f_main)
    , placer(f_main)
{
  // Labels
  l_code.caption("Code");
  l_date.caption("Date");
  l_amount.caption("Amount");
  l_operation.caption("Operation");
  l_account.caption("Account");
  l_estimate.caption("Estimate");
  l_category.caption("Category");

  // Settings.
  t_code.editable(false);
  t_date.multi_lines(false);
  c_operation.editable(false);
  t_amount.multi_lines(false);
  c_operation.push_back("INCOME");
  c_operation.push_back("EXPENSE");
  c_operation.push_back("TRANSFERENCE");
  c_account.editable(false);
  c_estimate.editable(false);
  c_category.editable(false);
  // Tab
  API::tabstop(t_code);
  API::eat_tabstop(t_code, false);
  API::tabstop(t_date);
  API::eat_tabstop(t_date, false);
  API::tabstop(c_operation);
  API::tabstop(t_amount);
  API::eat_tabstop(t_amount, false);
  API::tabstop(c_operation);
  API::tabstop(c_account); 
  API::tabstop(c_estimate);
  API::tabstop(c_category);

  // Events
  t_date.events().focus([this](auto&& arg) {
    auto newValue = t_date.caption();
    if(not arg.getting and a_view.date != newValue) {
      a_view.date = newValue;
      a_controller->setDate(newValue);
    }
  });
  t_amount.events().focus([this](auto&& arg) {
    auto newValue = unsigned(t_amount.to_int());
    if(not arg.getting and a_view.amount != newValue) {
      a_view.amount = newValue;
      a_controller->setAmount(newValue);
    }
  });
  c_operation.events().focus([this](auto&& arg) {
    auto newValue = Operation(c_operation.option() + 1);
    if(not arg.getting and a_view.operation != newValue) {
      a_view.operation = newValue;
      a_controller->setOperation(newValue);
    }
  });
  c_account.events().focus([this](auto&& arg) {
    auto newValue = c_account.text(c_account.option());
    if(not arg.getting and a_view.account != newValue) {
      a_view.account = newValue;
      a_controller->setAccount(newValue);
    }
  });
  c_estimate.events().focus([this](auto&& arg) {
    auto newValue = c_estimate.text(c_estimate.option());
    if(not arg.getting and a_view.estimate != newValue) {
      a_view.estimate = newValue;
      a_controller->setEstimate(newValue);
    }
  });
  c_category.events().focus([this](auto&& arg) {
    auto newValue = c_category.text(c_category.option());
    if(not arg.getting and a_view.category != newValue) {
      a_view.category = newValue;
      a_controller->setCategory(newValue);
    }
  });

  // Layout
  placer.div("<main grid=[2,7]>");
  placer.field("main") << l_code << t_code << l_date << t_date << l_amount << t_amount << l_operation << c_operation
                       << l_account << c_account << l_estimate << c_estimate << l_category << c_category;
  placer.collocate();

}

void orca::ExecutionDetailPresenter::present() { f_main.modality(); }
void orca::ExecutionDetailPresenter::reset(const ExecutionView& view)
{
  a_view = view;
  a_controller = view.controller();
  t_code.from(int(view.code));
  t_date.caption(view.date);
  t_amount.from(int(view.amount));
  switch(view.operation) {
  case Operation::INCOME:
    c_operation.option(0);
    break;
  case Operation::EXPENSE:
    c_operation.option(1);
    break;
  case Operation::EXCHANGE:
    c_operation.option(2);
    break;
  }
  c_account.push_back(view.account);
  c_account.option(0);
  c_estimate.push_back(view.estimate);
  c_estimate.option(0);
  c_category.push_back(view.category);
  c_category.option(0);
}

ExecutionView orca::ExecutionDetailPresenter::get() { return a_view; }
