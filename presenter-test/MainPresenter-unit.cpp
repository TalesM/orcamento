#include "config.hpp"
#include "MainPresenter.hpp"

#include <iostream>
#include "MainController.hpp"
#include "Manager.hpp"

using namespace orca;

struct StubMainController : public MainController {
  bool stub;
};
static auto nullStubRegister = [](auto p) -> std::unique_ptr<MainController> {
  return make_unique<StubMainController>();
};

SCENARIO("MainPresenter startup with no file", "[presenter][main-presenter-class]")
{
  GIVEN("A main presenter with no file")
  {
    Manager manager;
    manager.register_filetype(".*", nullStubRegister);
    MainPresenter mainPresenter{manager};

    WHEN("User cancels splasher")
    {
      cout << "Click at 'Cancel' button." << endl;

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
      cout << "Create or load a file please" << endl;

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
  GIVEN("A Main  Presenter with a filepath")
  {
    Manager manager;
    manager.register_filetype(".*", nullStubRegister);
    MainPresenter mainPresenter{manager, "/home/user/test"};

    WHEN("Presented")
    {
      cout << "If splasher opens, cancel. It is already wrong." << endl;

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

SCENARIO("MainPresenter startup with file", "[presenter][main-presenter-class]")
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
      cout << "Click at file->Open, then exit" << endl;

      THEN("Calls the MainController.listBudgets() twice")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets == 2);
      }
    }

    WHEN("It clicks Menu->New")
    {
      cout << "Click at file->New, then exit" << endl;

      THEN("Calls the MainController.listBudgets() twice")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledListBudgets == 2);
      }
    }

    WHEN("It clicks Menu->Save")
    {
      cout << "Click at file->save, then exit" << endl;

      THEN("Calls the MainController.flush()")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(calledFlush);
      }
    }
  }
}

struct CallRecorder {
  vector<string> record;
  bool has(const std::string &call) const { return std::find(record.begin(), record.end(), call) != record.end(); }
  void push(std::string call) { record.push_back(std::move(call)); }
};

struct RecorderMainController : public MainController {
  CallRecorder &call_recorder;

  RecorderMainController(CallRecorder &r) : call_recorder{r} {}
  std::string pushBudget() override
  {
    static const char *names[] = {"A new one", "Another new one"};
    static auto index = 0;
    call_recorder.push("pushBudget");
    return names[(index++) % 2];
  }

  vector<string> listBudgets() const override
  {
    call_recorder.push("listBudgets");
    return {"One", "Two", "Three"};
  }
};

inline Manager createManagerForTest(CallRecorder &callRecorder)
{
  Manager manager;
  manager.register_filetype(".*",
                            [&callRecorder](auto x) { return make_unique<RecorderMainController>(callRecorder); });
  return manager;
}

inline void exec(Presenter &p, unsigned timeout = USER_TIMEOUT) { p.execTimeout(timeout, checkFinishedOk); }
SCENARIO("Adding a Budget", "[presenter][main-presenter-class]")
{
  GIVEN("A MainPresenter with a file loaded")
  {
    CallRecorder callRecorder;
    Manager manager = createManagerForTest(callRecorder);
    MainPresenter mainPresenter{manager, "teste"};
    WHEN("User clicks on Budget->New")
    {
      cout << "Please, click in Budget->New and then exit" << endl;
      THEN("It calls MainController.pushBudget() returning the name.")
      {
        exec(mainPresenter);
        REQUIRE(callRecorder.has("pushBudget"));
      }
    }
  }
}
