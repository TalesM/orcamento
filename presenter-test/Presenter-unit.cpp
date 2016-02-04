#include <catch.hpp>
#include "Presenter.hpp"

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/wvl.hpp>

using namespace orca;

struct MockPresenter: public Presenter{
  nana::form fm;
  
  void present() override{
    fm.show();
  }
};

TEST_CASE("Presenter exiting on timeout", "[presenter][presenter-class]") {
  MockPresenter presenter;
  bool executed = false, finished = false;
  auto timer = presenter.schedule(500, [&executed, &finished]() {
    REQUIRE_FALSE(finished);
    executed = true;
  });
  
  CAPTURE( executed );
  executed = false;
  presenter.execTimeout(1000, [&finished](bool finishedOk) {
    finished = true;
    REQUIRE_FALSE(finishedOk);
  });
  REQUIRE(executed);
  REQUIRE(finished);
}

TEST_CASE("Presenter exiting normally", "[presenter][presenter-class]") {
  MockPresenter presenter;
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

TEST_CASE("Presenter throws at present", "[presenter][presenter-class]"){
  Presenter presenter;
  REQUIRE_THROWS_AS(presenter.execTimeout(1, [](bool){}), std::logic_error);
}
//TODO: Present method should be abstract
