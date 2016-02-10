#include "common.hpp"
#include "EstimateDetailPresenter.hpp"
#include "stubs/EstimateControllerStub.hpp"

static auto make_controller(CallRecorder &cr)
{
  return [&cr]() -> shared_ptr<EstimateController> {
    cr.push("controller");
    return make_shared<EstimateControllerStub>(cr);
  };
}

struct EstimateDetailFixture {
  CallRecorder call_recorder;
  EstimateView ev{
    name : "Test1",
    category : "CAT",
    operation : Operation::INCOME,
    estimated : 1500'00,
    fulfilled : 0,
    dueDay : 0,
    done : false,
    controller : make_controller(call_recorder)
  };
};

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter opens ok",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("A EstimateView")
  {
    WHEN("Opens")
    {
      THEN("Executes EstimateView.controller()")
      {
        EstimateDetailPresenter edp{ev};
        REQUIRE(call_recorder.has("controller"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture, "EstimateDetailPresenter view", "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("A EstimateView")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Shows the view")
    {
      THEN("Shows info correctly")
      {
        cout << "Check if the viewed fields are:" << endl
             << "'name': 'Test1'," << endl
             << "'category': 'CAT'," << endl
             << "'operation': 'INCOME'," << endl
             << "'estimated': '1500.00'," << endl
             << "'fulfilled': '0.00'," << endl
             << "'dueDay': '0'," << endl
             << "'done': Unchecked," << endl;
        REQUIRE_NOTHROW(exec(edp));
      }
    }

    WHEN("Change the view")
    {
      EstimateView view{
        name : "Test2",
        category : "OTHER CAT",
        operation : Operation::EXPENSE,
        estimated : 700'00,
        fulfilled : 700'00,
        dueDay : 10,
        done : true,
        controller : make_controller(call_recorder)
      };
      THEN("Shows info correctly")
      {
        cout << "Check if the viewed fields are:" << endl
             << "'name': 'Test2'," << endl
             << "'category': 'OTHER CAT'," << endl
             << "'operation': 'EXPENSE'," << endl
             << "'estimated': '700.00'," << endl
             << "'fulfilled': '700.00'," << endl
             << "'dueDay': '10'," << endl
             << "'done': Checked," << endl;

        edp.reset(view);
        REQUIRE_NOTHROW(exec(edp));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter editing name",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("An open editing")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Change The name")
    {
      cout << "Change the name value and then exit." << endl;
      THEN("Call the appropriated controller.name()")
      {
        REQUIRE_NOTHROW(exec(edp));
        REQUIRE(call_recorder.has("setName"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter editing category",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("An open editing")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Change the category to a valid one")
    {
      cout << "Change the category to any value but '!invalid' and then exit." << endl;
      THEN("Call the appropriated controller.category()")
      {
        REQUIRE_NOTHROW(exec(edp));
        REQUIRE(call_recorder.has("setCategory"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter editing operation",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("An open editing")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Change the operation to a valid one")
    {
      cout << "Change the operation to any value but '!invalid' and then exit." << endl;
      THEN("Call the appropriated controller.operation()")
      {
        REQUIRE_NOTHROW(exec(edp));
        REQUIRE(call_recorder.has("setOperation"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter editing estimated value",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("An open editing")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Change the estimated to a valid one")
    {
      cout << "Change the estimated to any value but '!invalid' and then exit." << endl;
      THEN("Call the appropriated controller.estimated()")
      {
        REQUIRE_NOTHROW(exec(edp));
        REQUIRE(call_recorder.has("setEstimated"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter editing due day",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("An open editing")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Change the due day")
    {
      cout << "Change the due day to any value but '!invalid' and then exit." << endl;
      THEN("Call the appropriated controller.setDueDay()")
      {
        REQUIRE_NOTHROW(exec(edp));
        REQUIRE(call_recorder.has("setDueDay"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateDetailFixture,
                "EstimateDetailPresenter editing done",
                "[estimate-detail-presenter-class][presenter]")
{
  GIVEN("An open editing")
  {
    EstimateDetailPresenter edp{ev};
    WHEN("Check the done")
    {
      cout << "Check the 'done' and then exit." << endl;
      THEN("Call the appropriated controller.setDone()")
      {
        REQUIRE_NOTHROW(exec(edp));
        REQUIRE(call_recorder.has("setDone"));
      }
    }
  }
}
