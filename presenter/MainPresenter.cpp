#include "MainController.hpp"

#include <nana/gui/filebox.hpp>
#include <nana/gui/widgets/menu.hpp>
#include "MainPresenter.hpp"
#include "Manager.hpp"
#include "SplasherPresenter.hpp"

orca::MainPresenter::MainPresenter(Manager &manager, const std::string &file_path)
    : a_manager(manager)
    , a_controller((file_path != "") ? a_manager.open(file_path) : nullptr)
    , l_budgets(f_main)
    , mb_main(f_main)
    , placer(f_main)
{
  // Main widgets
  f_main.caption("OrcaMento");
  l_budgets.append_header("Budgets");
  l_budgets.show_header(false);

  // Menu
  nana::menu &fileMenu = mb_main.push_back("&File");
  fileMenu.append("&New", [this](auto &&) {
    nana::filebox fb(f_main, false);
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
    nana::filebox fb(f_main, true);
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
  fileMenu.append("&Save", [this](auto &&) {
    a_controller->flush();
  });
  fileMenu.append_splitter();
  fileMenu.append("E&xit", [this](auto &&) { f_main.close(); });

  // Layout
  stringstream ss;
  ss << "<vert <menu weight=" << mb_main.size().height << "> <main>>";
  placer.div(ss.str().c_str());
  placer.field("menu") << mb_main;
  placer.field("main") << l_budgets;
  placer.collocate();
}

void orca::MainPresenter::present()
{
  if(not a_controller) {
    SplasherPresenter splasher{a_manager};
    splasher.onCancel([this]() { a_load_error_callback(); });
    splasher.onSuccess([this](auto &&controller) {
      a_load_success_callback(*controller);
      a_controller = move(controller);
    });
    splasher.present();
  }
  f_main.show();
  refreshBudgetList();
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
}
