#include "common.hpp"
#include "ExecutionDetailPresenter.hpp"
#include "ExecutionView.hpp"
#include "stubs/ExecutionControllerStub.hpp"
#include <array>

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
  array<string, 3> accounts{{"pocket", "bank", "savings"}};
  array<string, 3> categories{{"ARTICUNO", "ZAPDOS", "MOLTRES"}};
  array<string, 3> estimates{{"ESTIMATE1", "ESTIMATE2", "ESTIMATE3"}};
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
                "ExecutionDetailPresenter accounts",
                "[presenter][execution-detail-presenter-class]")
{
  GIVEN("A Properly initialized Execution Detail Presenter")
  {
    WHEN("The accounts is set")
    {
      executionDetailPresenter.accounts(begin(accounts), end(accounts));
      THEN("See the accounts")
      {
        UserInputChecker uic("", "the accounts field is filled");
        exec(executionDetailPresenter);
      }
    }
  }
}

SCENARIO_METHOD(ExecutionDetailPresenterFixture,
                "ExecutionDetailPresenter estimates",
                "[presenter][execution-detail-presenter-class]")
{
  GIVEN("A Properly initialized Execution Detail Presenter")
  {
    WHEN("The accunts is set")
    {
      executionDetailPresenter.estimates(begin(estimates), end(estimates));
      THEN("See the estimates")
      {
        UserInputChecker uic("", "the estimates field is filled");
        exec(executionDetailPresenter);
      }
    }
  }
}

SCENARIO_METHOD(ExecutionDetailPresenterFixture,
                "ExecutionDetailPresenter categories",
                "[presenter][execution-detail-presenter-class]")
{
  GIVEN("A Properly initialized Execution Detail Presenter")
  {
    WHEN("The categories is set")
    {
      executionDetailPresenter.categories(begin(categories), end(categories));
      THEN("See the categories")
      {
        UserInputChecker uic("", "the categories field is filled");
        exec(executionDetailPresenter);
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
    executionDetailPresenter.accounts(begin(accounts), end(accounts));
    executionDetailPresenter.estimates(begin(estimates), end(estimates));
    executionDetailPresenter.categories(begin(categories), end(categories));
    WHEN("It sets the date")
    {
      THEN("It calls setDate()")
      {
        UserInputChecker uic("set date", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setDate"));
        REQUIRE(view.date != executionDetailPresenter.get().date);
      }
    }
    WHEN("It sets the amount")
    {
      THEN("It calls setAmount()")
      {
        UserInputChecker uic("set amount", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setAmount"));
        REQUIRE(view.amount != executionDetailPresenter.get().amount);
      }
    }
    WHEN("It sets the operation")
    {
      THEN("It calls setOperation()")
      {
        UserInputChecker uic("set operation", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setOperation"));
        REQUIRE(view.operation != executionDetailPresenter.get().operation);
      }
    }
    WHEN("It sets the account")
    {
      THEN("It calls setAccount()")
      {
        UserInputChecker uic("set account", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setAccount"));
        REQUIRE(executionDetailPresenter.get().account.size() > 0);
        REQUIRE(view.account != executionDetailPresenter.get().account);
      }
    }
    WHEN("It sets the estimate")
    {
      THEN("It calls setEstimate()")
      {
        UserInputChecker uic("set estimate", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setEstimate"));
        REQUIRE(executionDetailPresenter.get().estimate.size() > 0);
        REQUIRE(view.estimate != executionDetailPresenter.get().estimate);
      }
    }
    WHEN("It sets the category")
    {
      THEN("It calls setCategory()")
      {
        UserInputChecker uic("set category", "");
        exec(executionDetailPresenter);
        REQUIRE(call_recorder.has("setCategory"));
        REQUIRE(executionDetailPresenter.get().category.size() > 0);
        REQUIRE(view.category != executionDetailPresenter.get().category);
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
