#include <catch.hpp>
#include "MainPresenter.hpp"

#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

#include "Manager.hpp"

constexpr auto USER_TIMEOUT = 60000u;

using namespace std;
using namespace orca;

inline void checkFinishedOk(bool finishedOk) { REQUIRE(finishedOk); }
SCENARIO("MainPresenter startup", "[presenter][main-presenter-class]")
{
  GIVEN("A main presenter with no file")
  {
    Manager manager;
    MainPresenter splasher{manager};

    WHEN("User cancels splasher")
    {
      cout << "Click at 'Cancel' button." << endl;

      THEN("Finishes Application") { REQUIRE(true); }
    }
  }
}
