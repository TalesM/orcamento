#include "EstimateListPresenter.hpp"

#include <iostream>
#include <unordered_set>
#include <set>

#include <nana/gui.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>

#include "EstimateController.hpp"
#include "EstimateListPresenter.hpp"

using namespace std;
using namespace nana;
using namespace orca;

// Overload the operator<< for oresolver to resolve the person type
listbox::oresolver& operator<<(listbox::oresolver& ores, const EstimateView& view)
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
  return ores << view.name << view.category << operation << view.estimated << view.fulfilled << view.dueDay
              << (view.done ? "Yes" : "No");
}

orca::EstimateListPresenter::EstimateListPresenter(nana::window wd, std::unique_ptr<BudgetController> controller)
    : l_estimates{wd, "Test"}, a_controller{move(controller)}, placer{wd}
{
  // Defining the list
  l_estimates.move({0, 0, 300, 200});
  l_estimates.events().key_press([this](const arg_keyboard& arg) {
    switch(arg.key) {
    case keyboard::os_insert:  // INSERT
      if(arg.ctrl == true and arg.shift == false) {
        this->newEstimate();
      }
      break;
    case keyboard::os_del:  // REMOVE
      if(arg.ctrl == true and arg.shift == false) {
        this->deleteSelectedEstimates();
      }
      break;
    }
  });
  const char* headers[] = {"name", "category", "operation", "estimated", "fulfilled", "dueDay", "done"};
  for(auto header : headers) {
    l_estimates.append_header(header);
  }

  // layout
  placer.div("<main>");
  placer.field("main") << l_estimates;
  placer.collocate();

  refresh();
}

void orca::EstimateListPresenter::refresh()
{
  if(a_controller) {
    auto cat0 = l_estimates.at(0);
    l_estimates.auto_draw(false);
    for(const EstimateView& view : a_controller->listEstimates()) {
      const ValueChangeCallback callback = [this](auto&& pos) {
        unique_ptr<EstimateController> c = a_controller->selectEstimate("ddd");
        c->setName("eee");
      };
      cat0.append(view).value(callback);
    }
    l_estimates.auto_draw(true);
  }
}

void orca::EstimateListPresenter::newEstimate()
{
  EstimateView view = {
    name : "New One",
    category : "CAT",
  };
  a_controller->insertEstimate(view);
  auto cat0 = l_estimates.at(0);
  cat0.append(view);
}

void orca::EstimateListPresenter::deleteSelectedEstimates()
{
  auto selection = l_estimates.selected();
  if(selection.size() == 0) {
    return;
  }
  unordered_set<string> estimateNames;
  set<size_t> estimatesPos;
  for(auto&& item : selection) {
    auto estimate = l_estimates.at(item);
    estimateNames.insert(estimate.text(0));
    estimatesPos.insert(item.item);
  }
  msgbox mb{l_estimates.parent(), "Confirmation", msgbox::yes_no};
  mb.icon(mb.icon_question);
  if(estimateNames.size() == 1) {
    mb << "Are you sure you want to delete '" << *estimateNames.begin() << "'?";
  } else {
    mb << "Are you sure you want to delete the " << estimateNames.size() << " estimates selected?";
  }
  if(mb.show() == mb.pick_yes) {
    a_controller->eraseEstimates(estimateNames);
    for(auto it = estimatesPos.rbegin(); it != estimatesPos.rend(); ++it) {
      l_estimates.erase(l_estimates.at(listbox::index_pair{0u, *it}));
    }
  }
}
