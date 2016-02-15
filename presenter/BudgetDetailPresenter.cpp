#include "BudgetDetailPresenter.hpp"
#include <iostream>
#include <cmath>

using namespace nana;
using namespace std;

orca::BudgetDetailPresenter::BudgetDetailPresenter(nana::window wd, std::unique_ptr<BudgetController> controller)
    : BASE(move(controller)), a_estimates(wd, nullptr), a_executions(wd, nullptr), t_main(wd), l_summary(wd)
{
  t_main.append("Summary", l_summary, "summary");
  t_main.append("Estimates", a_estimates.window(), "estimates");
  t_main.append("Execution", a_executions.window(), "executions");
  t_main.activated(0);

  t_main.events().activated([this](auto& arg) {
    unique_ptr<BudgetController> controller;
    switch(a_currentControllerOwner) {
    case 0:
      controller = move(a_controller);
      break;
    case 1:
      controller = a_estimates.devolve();
      break;
    case 2:
      controller = a_executions.devolve();
      break;
    default:
      throw logic_error("Invalid tab");
    }
    a_currentControllerOwner = t_main.activated();
    switch(a_currentControllerOwner) {
    case 0:
      a_controller = move(controller);
      this->refresh();
      break;
    case 1:
      a_estimates.receive(move(controller));
      break;
    case 2:
      a_executions.receive(move(controller));
      break;
    default:
      throw logic_error("Invalid tab");
    }
  });
  l_summary.show_header(false);
  l_summary.append_header("Name");
  l_summary.append_header("Value");
  if(a_controller != nullptr){
    refresh();
  }
}

struct SummaryItem {
  string name;
  int value = 0;
};
// Overload the operator<< for oresolver to resolve the person type
listbox::oresolver& operator<<(listbox::oresolver& ores, const SummaryItem& item)
{
  return ores << item.name << item.value;
}

void orca::BudgetDetailPresenter::refresh()
{
  // Data
  enum ItensNumbers {
    INITIAL,
    CURRENT,
    EXECUTED,
  };
  SummaryItem incomes[] = {{"Initial Estimate"}, {"Current Estimate"}, {"Executed"}};
  SummaryItem expenses[] = {{"Initial Estimate"}, {"Current Estimate"}, {"Executed"}};
  SummaryItem totals[] = {{"Initial Estimate"}, {"Current Estimate"}, {"Executed"}};

  for(const EstimateView& view : a_controller->listEstimates()) {
    switch(view.operation) {
    case Operation::EXCHANGE:
      break;
    case Operation::EXPENSE:
      expenses[INITIAL].value += view.estimated;
      expenses[CURRENT].value += max(view.estimated, view.fulfilled);
      expenses[EXECUTED].value += view.fulfilled;
      break;
    case Operation::INCOME:
      incomes[INITIAL].value += view.estimated;
      incomes[CURRENT].value += max(view.estimated, view.fulfilled);
      incomes[EXECUTED].value += view.fulfilled;
      break;
    }
  }
  totals[INITIAL].value = incomes[INITIAL].value - expenses[INITIAL].value;
  totals[CURRENT].value = incomes[CURRENT].value - expenses[CURRENT].value;
  totals[EXECUTED].value = incomes[EXECUTED].value - expenses[EXECUTED].value;

  // View
  l_summary.clear();
  auto catIncome = l_summary["Income"];
  for(const SummaryItem& si : incomes) {
    catIncome.append(si);
  }
  auto catExpenses = l_summary["Expenses"];
  for(const SummaryItem& si : expenses) {
    catExpenses.append(si);
  }
  auto catTotal = l_summary["Total"];
  for(const SummaryItem& si : totals) {
    catTotal.append(si);
  }
}
