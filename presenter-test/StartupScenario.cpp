#include <catch.hpp>

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

#include "Presenter.hpp"

SCENARIO( "Application Startup", "[presenter]" ){
  GIVEN("A new main frame"){
    using namespace orca;
    Presenter presenter;
    
    WHEN("Request Exit"){
      bool executed = false;
      bool finished = false;
      
      nana::timer timer;
      timer.interval(800);
      timer.elapse([&executed](){
        REQUIRE_FALSE(executed);
        executed = true;
        nana::API::exit();
      });
      timer.start();
      presenter.execTimeout(1000, [&finished](bool finishedOk){
        finished = true;
        REQUIRE(finishedOk);
      });
      REQUIRE(executed);
      REQUIRE(finished);
    }
  }
}