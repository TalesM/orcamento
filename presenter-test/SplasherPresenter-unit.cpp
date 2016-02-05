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

static string result = "";
static auto nullStubRegister = [](auto p) -> std::unique_ptr<Planner> {
  result = p[0];
  return nullptr;
};

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
  manager.register_filetype(".*", nullStubRegister);
  
  SplasherPresenter splasher{manager};
  
  bool cancelled = false;
  splasher.onCancel([&cancelled](){cancelled = true;});
  bool success = false;
  splasher.onSuccess([&success](std::unique_ptr<Planner>){
    success = true;
  });
  
  cout << "Click at 'New' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  cout << "'Created' file " << result << endl;
  REQUIRE(result != "");
  REQUIRE(success);
  REQUIRE_FALSE(cancelled);
}

TEST_CASE("PresenterSplasher open", "[presenter][splasher-presenter-class]") {
  Manager manager;
  manager.register_filetype(".*", nullStubRegister);
  
  SplasherPresenter splasher{manager};
  
  bool cancelled = false;
  splasher.onCancel([&cancelled](){cancelled = true;});
  bool success = false;
  splasher.onSuccess([&success](std::unique_ptr<Planner>){
    success = true;
  });
  
  cout << "Click at 'Open' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  cout << "'Opened' file " << result << endl;
  REQUIRE(result != "");
  REQUIRE(success);
  REQUIRE_FALSE(cancelled);
}