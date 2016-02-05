#include <catch.hpp>
#include "SplasherPresenter.hpp"

#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

constexpr auto USER_TIMEOUT = 60000u;

using namespace std;
using namespace orca;

inline void checkFinishedOk(bool finishedOk){
  REQUIRE(finishedOk);
}

TEST_CASE("PresenterSplasher exiting", "[presenter][splasher-presenter-class]") {
  Manager manager;
  SplasherPresenter splasher{manager};
  cout << "Click at 'X' button." << endl;
  
  bool cancelled = false;
  splasher.onCancel([&cancelled](){
    cancelled = true;
  });
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  REQUIRE(cancelled);
}

TEST_CASE("PresenterSplasher new", "[presenter][splasher-presenter-class]") {
  Manager manager;
  bool opened = false;
  string file;
  manager.register_filetype(".*", [&opened, &file](auto p)->std::unique_ptr<Planner>{
    opened = true;
    file = p[0];
    cout << "'Opened' the file: " << file << endl;
    return nullptr;
  });
  
  SplasherPresenter splasher{manager};
  
  bool cancelled = false;
  splasher.onCancel([&cancelled](){
    cancelled = true;
  });
  bool success = false;
  splasher.onSuccess([&success](std::unique_ptr<Planner>){
    success = true;
  });
  
  cout << "Click at 'New' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  REQUIRE(opened);
  REQUIRE(success);
  REQUIRE_FALSE(cancelled);
}