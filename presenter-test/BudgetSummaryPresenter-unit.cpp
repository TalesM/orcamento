#include "common.hpp"
#include "stubs/BudgetControllerStub.hpp"
#include "BudgetSummaryPresenter.hpp"

class BudgetSummaryFixture
{
 protected:
  CallRecorder call_recorder;
  nana::form host{API::make_center(800, 600)};
  nana::place placer { host };
  BudgetSummaryPresenter budgetDetailPresenter{host, make_unique<BudgetControllerStub>(call_recorder)};

  BudgetSummaryFixture()
  {
    placer.div("<main>");
    placer.field("main") << budgetDetailPresenter.window();
    placer.collocate();
  }
}; 

SCENARIO_METHOD(BudgetSummaryFixture, "BudgetDetailPresenter summary", "[budget-summary-presenter-class][presenter]")
{
  GIVEN("A BudgetSummaryPresenter correcly initialized")
  {
    WHEN("Summary tab is selected")
    {
      THEN("Show the summary")
      {
        UserInputChecker uic("", "the summary is shown");
        exec(host);
        REQUIRE(call_recorder.has("listEstimates"));
      }
    }
  }
}
