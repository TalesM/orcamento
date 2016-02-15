#include "common.hpp"
#include "stubs/BudgetControllerStub.hpp"
#include "BudgetDetailPresenter.hpp"

class BudgetDetailFixture
{
 protected:
  CallRecorder call_recorder;
  nana::form host{API::make_center(800, 600)};
  nana::place placer { host };
  BudgetDetailPresenter budgetDetailPresenter{host, make_unique<BudgetControllerStub>(call_recorder)};

  BudgetDetailFixture()
  {
    placer.div("vertical <weight=20 tabs><body>");
    placer.field("tabs") << budgetDetailPresenter.window();
    for(auto &&tab : budgetDetailPresenter.tabs()){
      placer.field("body").fasten(tab);
    }
    placer.collocate();
  }
};

SCENARIO_METHOD(BudgetDetailFixture, "BudgetDetailPresenter shows", "[budget-detail-presenter-class][presenter]")
{
  GIVEN("A BudgetDetailPresenter correcly initialized")
  {
    WHEN("Created")
    {
      THEN("Show 3 tabs")
      {
        UserInputChecker uic("", "the window should have three tabs, Summary, Estimates, Executions, the first one being selected by default");
        exec(host);
      }
    }
  }
}

SCENARIO_METHOD(BudgetDetailFixture, "BudgetDetailPresenter summary", "[budget-detail-presenter-class][presenter]")
{
  GIVEN("A BudgetDetailPresenter correcly initialized")
  {
    WHEN("Summary tab is selected")
    {
      THEN("Show the summary")
      {
        UserInputChecker uic("Click the first tab", "the summary is shown");
        exec(host);
        REQUIRE(call_recorder.has("listEstimates"));
      }
    }
  }
}

SCENARIO_METHOD(BudgetDetailFixture, "BudgetDetailPresenter estimates", "[budget-detail-presenter-class][presenter]")
{
  GIVEN("A BudgetDetailPresenter correcly initialized")
  {
    WHEN("Estimates tab is selected")
    {
      THEN("Show the estimates")
      {
        UserInputChecker uic("Click the second tab", "the estimates are shown");
        exec(host);
      }
    }
  }
}

SCENARIO_METHOD(BudgetDetailFixture, "BudgetDetailPresenter executions", "[budget-detail-presenter-class][presenter]")
{
  GIVEN("A BudgetDetailPresenter correcly initialized")
  {
    WHEN("Execution tab is selected")
    {
      THEN("Show the executions")
      {
        UserInputChecker uic("Click the third tab", "the executions are shown");
        exec(host);
      }
    }
  }
}
