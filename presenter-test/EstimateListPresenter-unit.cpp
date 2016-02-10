#include "common.hpp"
#include "EstimateListPresenter.hpp"

#include <nana/gui.hpp>
#include "EstimateController.hpp"
#include "stubs/EstimateControllerStub.hpp"

/**
 * @class RecorderBudgetController
 * @author Tales
 * @date 08/02/2016
 * @file EstimateListPresenter-unit.cpp
 * @brief Stub for BudgetController
 */
struct RecorderBudgetController : public BudgetController {
  CallRecorder &call_recorder;
  RecorderBudgetController(CallRecorder &c) : call_recorder{c} {}
  vector<EstimateView> listEstimates() const override
  {
    ORCA_RECORD_CALL(call_recorder);
    return {
        {"Estimate 1", "CATEGORY", Operation::INCOME, 150'00, 150'00, 2, true},
        {"Estimate 2", "CATEGORY", Operation::EXPENSE, 15'00, 0'00, 10, false},
        {"Estimate 3", "CATEGORY", Operation::EXCHANGE, 15'00, 0'00, 10, false},
        {"Estimate 4", "CATEGORY", Operation::EXPENSE, 80'00, 78'90, 0, true},
    };
  }
  EstimateView insertEstimate() override
  {
    ORCA_RECORD_CALL(call_recorder);
    return {"New Estimate",
            "CATEGORY",
            Operation::INCOME,
            150'00,
            150'00,
            2,
            false,
            [this]() -> shared_ptr<EstimateController> { return make_unique<EstimateControllerStub>(call_recorder); }};
  }
  void eraseEstimates(const std::unordered_set<std::string> &estimatesNames) override
  {
    call_recorder.push("eraseEstimates");
  }

  EstimateView getEstimateByName(const string &name) override
  {
    ORCA_RECORD_CALL(call_recorder);
    return {"Editable Estimate",
            "CATEGORY",
            Operation::INCOME,
            150'00,
            150'00,
            2,
            true,
            [this]() -> shared_ptr<EstimateController> { return make_unique<EstimateControllerStub>(call_recorder); }};
  }
};

class EstimateListPresenterFixture
{
 protected:
  CallRecorder call_recorder;
  nana::form host{API::make_center(800, 600)};
  EstimateListPresenter estimatePresenter{host, make_unique<RecorderBudgetController>(call_recorder)};
};

SCENARIO_METHOD(EstimateListPresenterFixture, "EstimatePresenter created", "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("It is created")
    {
      cout << "Please, close the program." << endl;
      THEN("Call EstimateController.listEstimates()")
      {
        exec(host);
        REQUIRE(call_recorder.has("listEstimates"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter adds new estimate",
                "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User press Insert")
    {
      cout << "Please, press Insert, give it a name and close the program." << endl;
      THEN("Call EstimateController.insertEstimate()")
      {
        exec(host);
        REQUIRE(call_recorder.has("insertEstimate"));
        REQUIRE(call_recorder.has("setName"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter remove an estimate",
                "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User press Delete")
    {
      cout << "Please, select a estimate and press Delete and close the program." << endl;
      THEN("Call EstimateController.deleteEstimate()")
      {
        exec(host);
        REQUIRE(call_recorder.has("eraseEstimates"));
      }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter edit an estimate",
                "[estimate-list-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User edits an estimate.")
    {
      cout << "Please, click in an estimate and press [space], then edit the name and close both windows.";
      THEN("It calls EstimateController.setName()")
      {
        call_recorder.record.clear();
        exec(host);
        REQUIRE(call_recorder.has("setName"));
      }
    }
  }
}
// TODO: Integration with EstimateDetail
