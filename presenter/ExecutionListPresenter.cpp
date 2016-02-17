#include "ExecutionListPresenter.hpp"
#include <nana/gui.hpp>

using namespace nana;
using namespace orca;
using namespace std;

// Overload the operator<< for oresolver to resolve the person type
listbox::oresolver& operator<<(listbox::oresolver& ores, const ExecutionView& view)
{
  const char* operation = "Unknown";
  switch(view.operation) {
  case Operation::INCOME:
    operation = "INCOME";
    break;
  case Operation::EXPENSE:
    operation = "EXPENSE";
    break;
  case Operation::EXCHANGE:
    operation = "EXCHANGE";
    break;
  }
  return ores << view.code << view.date << view.amount << operation << view.account << view.estimate << view.category;
}

orca::ExecutionListPresenter::ExecutionListPresenter(nana::window wd, std::unique_ptr<BudgetController> controller)
    : l_executions(wd), placer(wd), BASE(move(controller))
{
  // Setting up
  static const char* attributes[] = {"Code", "Date", "Amount", "Operation", "Account", "Estimate", "Category"};
  for(auto&& attribute : attributes) {
    l_executions.append_header(attribute);
  }

  // Events
  l_executions.events().key_press([this](auto&& ev) {
    switch(ev.key) {
    case keyboard::os_insert:
      this->insertExecution();
      break;
    case keyboard::os_del:
      this->deleteSelectedExecutions();
      break;
    }
  });

  // Styling
  placer.div("<main>");
  placer.field("main") << l_executions;
  placer.collocate();

  if(a_controller){
    refresh();
  }
}

void orca::ExecutionListPresenter::refresh()
{
  l_executions.clear();
  auto cat0 = l_executions.at(0);
  for(const ExecutionView& v : a_controller->listExecutions()) {
    cat0.append(v);
  }
}

void orca::ExecutionListPresenter::insertExecution()
{
  ExecutionView view = a_controller->insertExecution();
  //Call the handler, to give it the opportunity to edit it. If it does not throw everything should be ok.
  if(a_editHandler) a_editHandler(view);
  l_executions.at(0).append(view);
}

void orca::ExecutionListPresenter::deleteSelectedExecutions()
{
  auto selected = l_executions.selected();
  auto size = selected.size();
  if(size == 0) {
    return;
  }
  string msg = (size == 1) ? "Are you sure you want to delete the selected execution?" :
                             "Are you sure you want to delete the selecteds executions?";
  auto mbox = msgbox(l_executions.parent(), "Confirm Action", msgbox::yes_no).icon(msgbox::icon_question) << msg;
  if(mbox.show() != msgbox::pick_yes) {
    return;
  }
  unordered_set<string> codes;
  codes.reserve(selected.size());
  for(auto it = selected.rbegin(); it != selected.rend(); ++it) {
    auto item = l_executions.at(*it);
    codes.insert(item.text(0));
    l_executions.erase(item);
  }
  a_controller->eraseExecutions(codes);
}
