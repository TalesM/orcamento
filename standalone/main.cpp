#include <iostream>
#include <MainControllerSqlite0_5.hpp>
#include <MainPresenter.hpp>
#include <Manager.hpp>

using namespace std;
using namespace orca;

int main()
{
  Manager manager;
  manager.register_filetype(".*\\.orca", [](auto &&value) -> unique_ptr<MainController>{
    return make_unique<MainControllerSqlite0_5>(value[0]);
  });
  MainPresenter main_presenter{manager};
  main_presenter.present();
  nana::exec();
}