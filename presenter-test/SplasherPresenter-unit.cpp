#include <catch.hpp>

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

#include "SplasherPresenter.hpp"
using namespace orca;

TEST_CASE("PresenterSplasher exiting", "[presenter][splasher-presenter-class]") {
  SplasherPresenter splasher;
  splasher.execTimeout(1000, [](bool finishedOk){
    REQUIRE(finishedOk);
  });
}