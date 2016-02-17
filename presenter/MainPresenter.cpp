#include "MainController.hpp"

#include <nana/gui/filebox.hpp>
#include <nana/gui/widgets/menu.hpp>
#include "MainPresenter.hpp"
#include "Manager.hpp"
#include "SplasherPresenter.hpp"

using namespace nana;

orca::MainPresenter::~MainPresenter() = default;

orca::MainPresenter::MainPresenter(Manager &manager, const std::string &file_path)
    : a_manager(manager)
    , a_controller((file_path != "") ? a_manager.open(file_path) : nullptr)
    , a_budgetDetail(f_main, nullptr)
    , f_main(API::make_center(800, 600))
    , l_budgets(f_main)
    , mb_main(f_main)
    , placer(f_main)
{
  // Main widgets
  f_main.caption("OrcaMento");
  l_budgets.append_header("Budgets");
  l_budgets.show_header(false);
  l_budgets.events().selected([this](auto &&arg) {
    if(arg.selected) {
      a_budgetDetail.receive(a_controller->getBudget(arg.item.text(0)).controller());
    }  // Maybe put an else to devolve?
  });

  createMenu();

  createLayout();
}

void orca::MainPresenter::createMenu()
{
  menu &fileMenu = mb_main.push_back("&File");
  fileMenu.append("&New", [this](auto &&) {
    filebox fb(f_main, false);
    fb.add_filter("Orca files", "*.orca");
    fb.add_filter("Any files", "*.*");
    if(fb()) {
      auto newController = a_manager.open(fb.file());
      if(newController) {
        a_controller = move(newController);
        this->refreshBudgetList();
      }
    }
  });
  fileMenu.append("&Open", [this](auto &&) {
    filebox fb(f_main, true);
    fb.add_filter("Orca files", "*.orca");
    fb.add_filter("Any files", "*.*");
    if(fb()) {
      auto newController = a_manager.open(fb.file());
      if(newController) {
        a_controller = move(newController);
        this->refreshBudgetList();
      }
    }
  });
  fileMenu.append("&Save", [this](auto &&) { a_controller->flush(); });
  fileMenu.append_splitter();
  fileMenu.append("E&xit", [this](auto &&) { f_main.close(); });
  
  menu &budgetMenu = mb_main.push_back("&Budget");
  budgetMenu.append("&New", [this](auto &&) {
    auto b = this->a_controller->pushBudget();
    l_budgets.at(0).append(b);
  });
  budgetMenu.append("Delete &Last", [this](auto &&) {
    auto qtd_budgets = l_budgets.at(0).size();
    if(qtd_budgets == 0) {
      return;
    }
    msgbox mb{f_main, "Confirm", msgbox::yes_no};
    mb.icon(mb.icon_question);
    auto last_item = l_budgets.at(listbox::index_pair{0, qtd_budgets - 1});
    mb << "Are you sure you want to delete the budget '" << last_item.text(0) << "'?";
    if(mb.show() == msgbox::pick_yes) {
      a_controller->popBudget();
      l_budgets.erase(last_item);
    }
  });
  
  mb_main.push_back("E&stimate");
  
  menu &executionMenu = mb_main.push_back("E&xecution");
  executionMenu.append("&New", [this](auto &&){
    a_budgetDetail.insertExecution();
  });
  executionMenu.append("&Edit Selected");
  executionMenu.append("&Delete Selected");
}

void orca::MainPresenter::createLayout()
{
  stringstream ss;
  ss << "vert <menu weight=" << mb_main.size().height << "> <<budgets weight=20%>|<vertical <weight=20 tabs><body>>>";
  placer.div(ss.str().c_str());
  placer.field("menu") << mb_main;
  placer.field("budgets") << l_budgets;
  placer.field("tabs") << a_budgetDetail.window();
  for(auto &&tab : a_budgetDetail.tabs()) {
    placer.field("body").fasten(tab);
  }
  placer.collocate();

  if(a_controller) {
    refreshBudgetList();
  }
}

void orca::MainPresenter::present()
{
  f_main.show();
  if(not a_controller) {
    SplasherPresenter splasher{a_manager};
    splasher.onCancel([this]() {
      if(a_load_error_callback) {
        a_load_error_callback();
      }
      f_main.close();
    });
    splasher.onSuccess([this](auto &&controller) {
      if(a_load_success_callback) {
        a_load_success_callback(*controller);
      }
      a_controller = move(controller);
      this->refreshBudgetList();
    });
    splasher.present();
  }
}

void orca::MainPresenter::refreshBudgetList()
{
  l_budgets.clear();
  l_budgets.auto_draw(false);
  auto cat = l_budgets.at(0);
  for(auto &&budget : a_controller->listBudgets()) {
    cat.append(budget);
  }
  l_budgets.auto_draw(true);
  auto last_item = cat.at(cat.size() - 1);
  last_item.select(true);
  a_budgetDetail.receive(a_controller->getBudget(last_item.text(0)).controller());
}

void orca::MainPresenter::close() { f_main.close(); }