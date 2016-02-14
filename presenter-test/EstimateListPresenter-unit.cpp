#include "common.hpp"
#include "EstimateListPresenter.hpp"

#include <nana/gui.hpp>
#include "EstimateController.hpp"
#include "stubs/EstimateControllerStub.hpp"
#include "stubs/BudgetControllerStub.hpp"

class EstimateListPresenterFixture
{
 protected:
  CallRecorder call_recorder;
  nana::form host{API::make_center(800, 600)};
  EstimateListPresenter estimatePresenter{host, make_unique<BudgetControllerStub>(call_recorder)};
};

SCENARIO_METHOD(EstimateListPresenterFixture, "EstimatePresenter created", "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("It is created")
    {
      cout << "Please, close the program." << endl;
      THEN("Call EstimateController.listEstimates()")
      {
        exec(host);
        REQUIRE(call_recorder.has("listEstimates"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter adds new estimate",
                "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User press Insert")
    {
      cout << "Please, press Insert, give it a name and close the program." << endl;
      THEN("Call EstimateController.insertEstimate()")
      {
        exec(host);
        REQUIRE(call_recorder.has("insertEstimate"));
        REQUIRE(call_recorder.has("setName"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter remove an estimate",
                "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User press Delete")
    {
      cout << "Please, select a estimate and press Delete and close the program." << endl;
      THEN("Call EstimateController.deleteEstimate()")
      {
        exec(host);
        REQUIRE(call_recorder.has("eraseEstimates"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter edit an estimate",
                "[estimate-list-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User edits an estimate.")
    {
      cout << "Please, click in an estimate and press [space], then edit the name and close both windows.";
      THEN("It calls EstimateController.setName()")
      {
        call_recorder.record.clear();
        exec(host);
        REQUIRE(call_recorder.has("setName"));
      }
    }
  }
}
// TODO: Integration with EstimateDetail
