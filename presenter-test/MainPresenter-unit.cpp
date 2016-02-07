#include "config.hpp"
#include "MainPresenter.hpp"

#include <iostream>
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
}
