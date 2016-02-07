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
        bool called = false;
        mainPresenter.onLoadError([&called]() { called = true; });
        REQUIRE_FALSE(called);
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(called);
      }
    }
    WHEN("User opens or create a file on splasher")
    {
      cout << "Create or load a file please" << endl;

      THEN("Creates a controller")
      {
        bool called = false;
        MainController *addressController = nullptr;
        mainPresenter.onLoadSuccess([&called, &addressController](auto &&controller) {
          called = true;
          addressController = &controller;
        });
        REQUIRE_FALSE(called);
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(called);
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
        bool called = false;
        mainPresenter.onLoadSuccess([&called](auto &&) { called = true; });
        mainPresenter.onLoadError([&called]() { called = true; });
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        INFO("Splasher should not be called in this case");
        REQUIRE_FALSE(called);
      }
    }
  }
}

SCENARIO("MainPresenter started ok", "[presenter][main-presenter-class]")
{
  Manager manager;
  bool called = false;
  struct StubMainController : public MainController {
    bool &called;
    StubMainController(bool &called) : called(called) {}
    vector<string> listBudgets() const override{
      called = true;
      return {"One", "Two", "Three"};
    }
  };
  manager.register_filetype(".*", [&called](auto x) { return make_unique<StubMainController>(called); });

  GIVEN("A MainPresenter with a filepath")
  {
    MainPresenter mainPresenter{manager, "/home/user/test"};

    WHEN("Is created")
    {

      THEN("Calls the MainController.listBudgets()")
      {
        mainPresenter.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(called);
        INFO("Splasher should not be called in this case");
      }
    }
  }
}