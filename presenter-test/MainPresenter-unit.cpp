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

SCENARIO("MainPresenter startup", "[presenter][main-presenter-class]")
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

SCENARIO("MainPresenter started ok", "[presenter][main-presenter-class]")
{
  Manager manager;
  int calledListBudgets = 0;
  int calledFlush = 0;
  struct StubMainController : public MainController {
    int &calledListBudgets;
    int &calledFlush;
    StubMainController(int &calledListBudgets, int &calledFlush)
        : calledListBudgets(calledListBudgets), calledFlush(calledFlush)
    {
    }
    vector<string> listBudgets() const override
    {
      ++calledListBudgets;
      return {"One", "Two", "Three"};
    }
    
    void flush() override{
      ++calledFlush;
    }
  };
  manager.register_filetype(
      ".*", [&calledListBudgets, &calledFlush](auto x) { return make_unique<StubMainController>(calledListBudgets, calledFlush); });

  GIVEN("A MainPresenter with a filepath")
  {
    MainPresenter mainPresenter{manager, "/home/user/test"};

    WHEN("Is created")
    {
      mainPresenter.schedule(100, []() { nana::API::exit(); });

      THEN("Calls the MainController.listBudgets()")
      {
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