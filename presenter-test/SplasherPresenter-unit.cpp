#include <catch.hpp>
#include "SplasherPresenter.hpp"

#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

constexpr auto USER_TIMEOUT = 5000u;

using namespace std;
using namespace orca;

TEST_CASE("PresenterSplasher exiting", "[presenter][splasher-presenter-class]") {
  SplasherPresenter splasher;
  cout << "Click at 'X' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, [](bool finishedOk){
    REQUIRE(finishedOk);
  });
}

TEST_CASE("PresenterSplasher new", "[presenter][splasher-presenter-class]") {
  SplasherPresenter splasher;
  cout << "Click at 'New' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, [](bool finishedOk){
    REQUIRE(finishedOk);
  });
}