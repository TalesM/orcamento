#include "common.hpp"
#include "ExecutionListPresenter.hpp"
#include "stubs/BudgetControllerStub.hpp"

class ExecutionListPresenterFixture
{
 protected:
  CallRecorder call_recorder;
  nana::form host{API::make_center(800, 600)};
  ExecutionListPresenter executionListPresenter{host, make_unique<BudgetControllerStub>(call_recorder)};
};

SCENARIO_METHOD(ExecutionListPresenterFixture,
                "ExecutionListPresenter shows",
                "[execution-list-presenter-class][presenter]")
{
  GIVEN("An ExecutionListPresenter")
  {
    WHEN("It is presented")
    {
      THEN("It exits normally.")
      {
        UserInputChecker uic(
            "",
            "the screen listing some executions with the attributes (Code, Date, Value, Operation, Account, "
            "Estimate, Category)");
        exec(host);
        REQUIRE(call_recorder.has("listExecutions"));
      }
    }
  }
}

SCENARIO_METHOD(ExecutionListPresenterFixture,
                "ExecutionListPresenter inserts",
                "[execution-list-presenter-class][presenter]")
{
  GIVEN("An ExecutionListPresenter with a editViewHandler")
  {
    bool handlerExecuted = false;
    executionListPresenter.editViewHandler([&](ExecutionView &v){
      CHECK_FALSE(handlerExecuted); //Ensure it is called only once
      handlerExecuted = true;
    });
    WHEN("The user inserts")
    {
      UserInputChecker uic("click inside the list and press [insert]", "a new execution appears");
      
      THEN("The function insertExecution() is called")
      {
        exec(host);
        CHECK(handlerExecuted);
        REQUIRE(call_recorder.has("insertExecution"));
      }
    }
  }
}

SCENARIO_METHOD(ExecutionListPresenterFixture,
                "ExecutionListPresenter deletes",
                "[execution-list-presenter-class][presenter]")
{
  GIVEN("An ExecutionListPresenter")
  {
    WHEN("The user deletes")
    {
      UserInputChecker uic("click on an execution, press [delete] and confirm", "the execution selected disappears");
      THEN("The function eraseExecutions() is called")
      {
        exec(host);
        REQUIRE(call_recorder.has("eraseExecutions"));
      }
    }
  }
}
