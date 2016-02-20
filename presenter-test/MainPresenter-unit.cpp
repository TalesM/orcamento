#include "common.hpp"
#include "MainPresenter.hpp"

#include <iostream>
#include "MainController.hpp"
#include "Manager.hpp"
#include "stubs/MainControllerStub.hpp"

using namespace orca;

inline Manager createManagerForTest(CallRecorder &callRecorder)
{
  Manager manager;
  manager.register_filetype(".*", [&callRecorder](auto x) { return make_unique<MainControllerStub>(callRecorder); });
  return manager;
}

SCENARIO("MainPresenter startup with no file", "[presenter][main-presenter-class]")
{
  GIVEN("A main presenter with no file")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager};

    WHEN("User cancels splasher")
    {
      UserInputChecker uic("click at [cancel] or [x] button", "the application finishes");

      THEN("Finishes Application")
      {
        bool calledListBudgets = false;
        mainPresenter.onLoadError([&calledListBudgets]() { calledListBudgets = true; });
        REQUIRE_FALSE(calledListBudgets);
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets);
      }
    }
    WHEN("User opens or create a file on splasher")
    {
      UserInputChecker uic("click at [open] or [new] button");
      THEN("Creates a controller")
      {
        bool calledListBudgets = false;
        MainController *addressController = nullptr;
        mainPresenter.onLoadSuccess([&calledListBudgets, &addressController](auto &&controller) {
          calledListBudgets = true;
          addressController = &controller;
        });
        REQUIRE_FALSE(calledListBudgets);
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets);
        MainController &controller = mainPresenter.controller().value();
        REQUIRE(&controller == addressController);
      }
    }
  }
}

SCENARIO("MainPresenter startup with file", "[presenter][main-presenter-class][tabs]")
{
  GIVEN("A Main  Presenter with a filepath")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "/home/user/test"};

    WHEN("Presented")
    {
      UserInputChecker uic("",
                           "splasher does not open and the window should have three tabs, Summary, Estimates, "
                           "Executions, the first one being selected by default");
      THEN("Does not show dialog at presentation")
      {
        bool calledListBudgets = false;
        mainPresenter.onLoadSuccess([&calledListBudgets](auto &&) { calledListBudgets = true; });
        mainPresenter.onLoadError([&calledListBudgets]() { calledListBudgets = true; });
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        INFO("Splasher should not be calledListBudgets in this case");
        REQUIRE_FALSE(calledListBudgets);
      }
    }
  }
}

struct CounterMainController : public MainController {
  int &calledListBudgets;
  int &calledFlush;
  CounterMainController(int &calledListBudgets, int &calledFlush)
      : calledListBudgets(calledListBudgets), calledFlush(calledFlush)
  {
  }
  vector<string> listBudgets() const override
  {
    ++calledListBudgets;
    return {"One", "Two", "Three"};
  }

  void flush() override { ++calledFlush; }
};

// TODO: Fix the bug (Issue #42).
SCENARIO("MainPresenter startup with file2", "[presenter][main-presenter-class][.][!mayfail]")
{
  GIVEN("A MainPresenter with a filepath")
  {
    Manager manager;
    int calledListBudgets = 0;
    int calledFlush = 0;
    manager.register_filetype(".*", [&calledListBudgets, &calledFlush](auto x) {
      return make_unique<CounterMainController>(calledListBudgets, calledFlush);
    });
    MainPresenter mainPresenter{manager, "/home/user/test"};

    WHEN("Is created")
    {
      THEN("Calls the MainController.listBudgets()")
      {
        mainPresenter.schedule(100, [&mainPresenter]() { mainPresenter.close(); });
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets);
      }
    }

    WHEN("It clicks Menu->Open")
    {
      UserInputChecker uic("click at [file->open]");

      THEN("Calls the MainController.listBudgets() twice")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets == 2);
      }
    }

    WHEN("It clicks Menu->New")
    {
      UserInputChecker uic("click at [file->new]");

      THEN("Calls the MainController.listBudgets() twice")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets == 2);
      }
    }

    WHEN("It clicks Menu->Save")
    {
      UserInputChecker uic("click at [file->save]");

      THEN("Calls the MainController.flush()")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledFlush);
      }
    }
  }
}

SCENARIO("MainPresenter startup", "[presenter][main-presenter-class]")
{
  GIVEN("A MainPresernter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("It presents")
    {
      THEN("it shows the last budget selected and a summary on right side")
      {
        UserInputChecker uic("", "it shows the last budget selected and a summary on right side");
        exec(mainPresenter);
      }
    }
    WHEN("It changes the budget")
    {
      THEN("It calls getBudget twice.")
      {
        UserInputChecker uic("Select any budget but the last");
        CHECK(callRecorder.has("getBudget"));
        callRecorder.record.clear();
        exec(mainPresenter);
        REQUIRE(callRecorder.has("getBudget"));
      }
    }
  }
}

SCENARIO("Budget list manipulation", "[presenter][main-presenter-class]")
{
  GIVEN("A MainPresenter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("User clicks on Budget->New")
    {
      cout << "Please, click in Budget->New and then exit." << endl;
      THEN("It calls MainController.pushBudget() returning the name.")
      {
        exec(mainPresenter);
        REQUIRE(callRecorder.has("pushBudget"));
      }
    }
    WHEN("User clicks on Budget->Delete Last Budgets")
    {
      cout << "Please, click in Budget->Delete Last, confirm it and then exit." << endl;
      THEN("It calls MainController.popBudget()")
      {
        exec(mainPresenter);
        REQUIRE(callRecorder.has("popBudget"));
      }
    }
  }
}

SCENARIO("Exectution List Manipulation", "[presenter][main-presenter-class]")
{
  GIVEN("A MainPresenter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("User clicks on Execution->New")
    {
      THEN("The ExecutionDetailPresenter shows up")
      {
        UserInputChecker uic("click at the menu Execution->New",
                             "the execution tab is selected and the dialog to edit an estimate shows up");
        exec(mainPresenter);
      }
    }
    WHEN("User clicks on Execution->Edit")
    {
      THEN("The ExecutionDetailPresenter shows up")
      {
        UserInputChecker uic("click at the menu Execution->Edit",
                             "the execution tab is selected and the dialog to edit an estimate shows up");
        exec(mainPresenter);
      }
    }
    WHEN("User clicks on Execution->Delete")
    {
      THEN("The confirmation shows up")
      {
        UserInputChecker uic("click at the menu Execution->Delete",
                             "c confirmation shows up and in yes case it removes the selected line");
        exec(mainPresenter);
      }
    }
  }
}

SCENARIO("MainPresenter tab summary", "[main-presenter-class][presenter][tabs]")
{
  GIVEN("A MainPresenter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("Summary tab is selected")
    {
      THEN("Show the summary")
      {
        UserInputChecker uic("Click the first tab", "the summary is shown");
        exec(mainPresenter);
      }
    }
  }
}

SCENARIO("MainPresenter tab estimates", "[main-presenter-class][presenter][tabs]")
{
  GIVEN("A MainPresenter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("Estimates tab is selected")
    {
      THEN("Show the estimates")
      {
        UserInputChecker uic("Click the second tab", "the estimates are shown");
        exec(mainPresenter);
      }
    }
  }
}

SCENARIO("MainPresenter tab executions", "[main-presenter-class][presenter][tabs]")
{
  GIVEN("A MainPresenter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("Execution tab is selected")
    {
      THEN("Show the executions")
      {
        UserInputChecker uic("Click the third tab", "the executions are shown");
        exec(mainPresenter);
      }
    }
  }
}
