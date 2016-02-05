#include "SplasherPresenter.hpp"
#include <nana/gui/filebox.hpp>

using namespace nana;

orca::SplasherPresenter::SplasherPresenter(Manager& manager):
  a_manager(manager),
  f_splasher(API::make_center(600, 400)),
  b_new(f_splasher, "New"),
  b_open(f_splasher, "Open"),
  placer(f_splasher)
{
  //placing
  placer.div("<main>");
  placer.field("main") << b_new << b_open;
  placer.collocate();
  
  //Event handling
  b_new.events().click([this](){
    filebox fb{f_splasher, false};
    fb.add_filter("Orca files", "*.orca");
    fb.add_filter("All files", "*.*");
    if(fb()){
      a_manager.open(fb.file());
      f_splasher.close();
      a_file_success = true;
    }
  });
  b_open.events().click([this](){
    filebox fb{f_splasher, true};
    fb.add_filter("Orca files", "*.orca");
    fb.add_filter("All files", "*.*");
    if(fb()){
      a_manager.open(fb.file());
      f_splasher.close();
      a_file_success = true;
    }
  });
}

void orca::SplasherPresenter::present()
{
  f_splasher.modality();
  if(a_file_success){
    if(a_success_handler){
      a_success_handler(nullptr);
    }
  } else if(a_cancel_handler) {
    a_cancel_handler();
  }
}
