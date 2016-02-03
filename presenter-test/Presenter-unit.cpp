#include <catch.hpp>

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

#include "Presenter.hpp"
using namespace orca;

TEST_CASE("Presenter exiting on timeout", "[presenter][presenter-class]") {
  Presenter presenter;
  bool executed = false, finished = false;

  nana::timer timer;
  timer.interval(500);
  timer.elapse([&executed, &finished]() {
    REQUIRE_FALSE(finished);
    executed = true;
  });
  timer.start();
  presenter.execTimeout(1000, [&finished](bool finishedOk) {
    finished = true;
    REQUIRE_FALSE(finishedOk);
  });
  REQUIRE(executed);
  REQUIRE(finished);
}

TEST_CASE("Presenter exiting normally", "[presenter][presenter-class]") {
  Presenter presenter;
  bool finished = false;

  nana::timer timer;
  timer.interval(800);
  timer.elapse([]() {
    nana::API::exit();
  });
  timer.start();
  presenter.execTimeout(1000, [&finished](bool finishedOk) {
    finished = true;
    REQUIRE(finishedOk);
  });
  REQUIRE(finished);
}
