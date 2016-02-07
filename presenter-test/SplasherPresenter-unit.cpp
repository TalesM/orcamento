#include "config.hpp"
#include "SplasherPresenter.hpp"

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

TEST_CASE("PresenterSplasher exiting", "[presenter][splasher-presenter-class]")
{
  Manager manager;
  SplasherPresenter splasher{manager};
  cout << "Click at 'X' button." << endl;

  bool cancelled = false;
  splasher.onCancel([&cancelled]() { cancelled = true; });
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  REQUIRE(cancelled);
}

TEST_CASE("PresenterSplasher new", "[presenter][splasher-presenter-class]")
{
  Manager manager;
  manager.register_filetype(".*", nullStubRegister);

  SplasherPresenter splasher{manager};

  bool cancelled = false;
  splasher.onCancel([&cancelled]() { cancelled = true; });
  bool success = false;
  splasher.onSuccess([&success](std::unique_ptr<MainController> p) {
    success = true;
    REQUIRE(p != nullptr);
    REQUIRE_NOTHROW(dynamic_cast<StubMainController&>(*p));
  });

  cout << "Click at 'New' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  cout << "'Created' file " << result << endl;
  REQUIRE(result != "");
  REQUIRE(success);
  REQUIRE_FALSE(cancelled);
}

TEST_CASE("PresenterSplasher open", "[presenter][splasher-presenter-class]")
{
  Manager manager;
  manager.register_filetype(".*", nullStubRegister);

  SplasherPresenter splasher{manager};

  bool cancelled = false;
  splasher.onCancel([&cancelled]() { cancelled = true; });
  bool success = false;
  splasher.onSuccess([&success](std::unique_ptr<MainController> p) {
    success = true;
    REQUIRE(p != nullptr);
    REQUIRE_NOTHROW(dynamic_cast<StubMainController&>(*p));
  });

  cout << "Click at 'Open' button." << endl;
  splasher.execTimeout(USER_TIMEOUT, checkFinishedOk);
  cout << "'Opened' file " << result << endl;
  REQUIRE(result != "");
  REQUIRE(success);
  REQUIRE_FALSE(cancelled);
}