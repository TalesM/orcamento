#include "common.hpp"
#include "ExecutionDetailPresenter.hpp"
#include "ExecutionView.hpp"
#include "stubs/ExecutionControllerStub.hpp"

struct ExecutionDetailPresenterFixture {
  CallRecorder call_recorder;
  ExecutionView view{
    code : 80085,
    date : "2007-10-05",
    amount : 1000'00,
    operation : Operation::INCOME,
    account : "pocket",
    estimate : "ESTIMATE",
    category : "CATEGORY",
    controller : [this]() -> unique_ptr<ExecutionController> {
      call_recorder.push("controller");
      return make_unique<ExecutionControllerStub>(call_recorder);
    }
  };
  ExecutionDetailPresenter executionDetailPresenter{view};
};

SCENARIO_METHOD(ExecutionDetailPresenterFixture,
                "ExecutionDetailPresenter starts ok",
                "[presenter][execution-detail-presenter-class]")
{
  GIVEN("A Properly initialized Execution Detail Presenter")
  {
    WHEN("It starts")
    {
      THEN("It presents all view's fields")
      {
        UserInputChecker uic("", "the screen showed the view's fields");
        exec(executionDetailPresenter);
        CHECK(call_recorder.has("controller"));
      }
    }
  }
}

SCENARIO_METHOD(ExecutionDetailPresenterFixture,
                "ExecutionDetailPresenter edits",
                "[presenter][execution-detail-presenter-class]")
{
  GIVEN("A Properly initialized Execution Detail Presenter")
  {
    WHEN("It sets the date")
    {
      THEN("It calls setDate()")
      {
        UserInputChecker uic("set date", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setDate"));
      }
    }
    WHEN("It sets the amount")
    {
      THEN("It calls setAmount()")
      {
        UserInputChecker uic("set amount", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setAmount"));
      }
    }
    WHEN("It sets the operation")
    {
      THEN("It calls setOperation()")
      {
        UserInputChecker uic("set operation", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setOperation"));
      }
    }
    WHEN("It sets the account")
    {
      THEN("It calls setAccount()")
      {
        UserInputChecker uic("set account", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setAccount"));
      }
    }
    WHEN("It sets the estimate")
    {
      THEN("It calls setEstimate()")
      {
        UserInputChecker uic("set estimate", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setEstimate"));
      }
    }
    WHEN("It sets the category")
    {
      THEN("It calls setCategory()")
      {
        UserInputChecker uic("set category", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setCategory"));
      }
    }
  }
}

SCENARIO_METHOD(ExecutionDetailPresenterFixture,
                "ExecutionDetailPresenter tabs",
                "[presenter][execution-detail-presenter-class]")
{
  GIVEN("A Properly initialized Execution Detail Presenter")
  {
    WHEN("The user hits tab multiple times")
    {
      THEN("It cycle through the fields")
      {
        UserInputChecker uic("press tab multiple times", "the focus cycles through the fields");
        exec(executionDetailPresenter);
      }
    }
  }
}
// TODO: Setting Accounts
// TODO: Setting Categories
// TODO: Setting Estimates
// TODO: Integrate with the ExecutionListPresenter and MainPresenter
