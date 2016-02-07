#include "MainPresenter.hpp"
#include "Manager.hpp"
#include "SplasherPresenter.hpp"

orca::MainPresenter::MainPresenter(Manager &manager) : a_manager(manager) {}
void orca::MainPresenter::present()
{
  SplasherPresenter splasher{a_manager};
  splasher.onCancel([this]() { a_load_error_callback(); });
  splasher.onSuccess([this](auto &&controller) {
    a_load_success_callback(*controller);
    a_controller = move(controller);
  });
  splasher.present();
}
