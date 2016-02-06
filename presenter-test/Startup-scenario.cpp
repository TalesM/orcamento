#include <catch.hpp>

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

#include "Presenter.hpp"
using namespace orca;

SCENARIO("Application Startup", "[presenter]")
{
  GIVEN("A new main frame")
  {
    Presenter presenter;

    WHEN("Request Exit")
    {
      nana::timer timer;
      timer.interval(800);
      timer.elapse([&presenter]() { nana::API::exit(); });
      timer.start();

      THEN("Finishes ok")
      {
        presenter.execTimeout(1000, [](bool finishedOk) { REQUIRE(finishedOk); });
      }
    }
  }
}