#include "MainController.hpp"
#include "MainPresenter.hpp"
#include "Manager.hpp"
#include "SplasherPresenter.hpp"

orca::MainPresenter::MainPresenter(Manager &manager, const std::string &file_path)
    : a_manager(manager), a_controller((file_path != "") ? a_manager.open(file_path) : nullptr)
{
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
}
