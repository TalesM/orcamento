#include "SplasherPresenter.hpp"

#include <nana/gui/filebox.hpp>
#include "MainController.hpp"
#include "Manager.hpp"

using namespace nana;

orca::SplasherPresenter::SplasherPresenter(Manager& manager)
    : a_manager(manager)
    , f_splasher(API::make_center(600, 400))
    , b_new(f_splasher, "New")
    , b_open(f_splasher, "Open")
    , b_cancel(f_splasher, "Cancel")
    , placer(f_splasher)
{
  // placing
  placer.div("<vert main arrange=[100,variable,50]>");
  placer.field("main") << b_new << b_open << b_cancel;
  placer.collocate();

  // Event handling
  b_new.events().click([this]() {  // TODO: Remove this redundancy.
    filebox fb{f_splasher, false};
    fb.add_filter("Orca files", "*.orca");
    fb.add_filter("All files", "*.*");
    if(fb()) {
      a_controller = a_manager.open(fb.file());
      f_splasher.close();
    }
  });
  b_open.events().click([this]() {
    filebox fb{f_splasher, true};
    fb.add_filter("Orca files", "*.orca");
    fb.add_filter("All files", "*.*");
    if(fb()) {
      a_controller = a_manager.open(fb.file());
      f_splasher.close();
    }
  });
  b_cancel.events().click([this]() { f_splasher.close(); });
}

orca::SplasherPresenter::~SplasherPresenter() = default;

void orca::SplasherPresenter::present()
{
  f_splasher.modality();
  if(a_controller != nullptr) {
    if(a_success_handler) {
      a_success_handler(move(a_controller));
    }
  } else if(a_cancel_handler) {
    a_cancel_handler();
  }
}
