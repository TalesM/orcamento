#include "common.hpp"
#include "SplasherPresenter.hpp"

#include "MainController.hpp"
#include "Manager.hpp"
using namespace orca;

struct StubMainController : public MainController {
  bool stub;
};
/// Ugly hack.
static string result = "";
static auto nullStubRegister = [](auto p) -> std::unique_ptr<MainController> {
  result = p[0];
  return make_unique<StubMainController>();
};

SCENARIO("PresenterSplasher exit conditions.", "[presenter][splasher-presenter-class]")
{
  GIVEN("A manager")
  {
    Manager manager;
    manager.register_filetype(".*", nullStubRegister);
    SplasherPresenter splasher{manager};

    WHEN("Click on cancel or exit")
    {
      cout << "Click at 'X' button." << endl;

      THEN("Exit normally")
      {
        bool cancelled = false;
        splasher.onCancel([&cancelled]() { cancelled = true; });
        splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
        REQUIRE(cancelled);
      }
    }

    WHEN("Click on new")
    {
      cout << "Click at 'New' button." << endl;
      THEN("Executes success callback and exits")
      {
        bool cancelled = false;
        splasher.onCancel([&cancelled]() { cancelled = true; });
        bool success = false;
        splasher.onSuccess([&success](std::unique_ptr<MainController> p) {
          success = true;
          REQUIRE(p != nullptr);
          REQUIRE_NOTHROW(dynamic_cast<StubMainController&>(*p));
        });

        splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
        cout << "'Created' file " << result << endl;
        REQUIRE(result != "");
        REQUIRE(success);
        REQUIRE_FALSE(cancelled);
      }
    }

    WHEN("Click on open")
    {
      cout << "Click at 'Open' button." << endl;
      THEN("Executes success callback and exits")
      {
        bool cancelled = false;
        splasher.onCancel([&cancelled]() { cancelled = true; });
        bool success = false;
        splasher.onSuccess([&success](std::unique_ptr<MainController> p) {
          success = true;
          REQUIRE(p != nullptr);
          REQUIRE_NOTHROW(dynamic_cast<StubMainController&>(*p));
        });

        splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
        cout << "'Opened' file " << result << endl;
        REQUIRE(result != "");
        REQUIRE(success);
        REQUIRE_FALSE(cancelled);
      }
    }
  }
}
