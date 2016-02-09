#include "common.hpp"
#include "EstimateListPresenter.hpp"

#include <nana/gui.hpp>
#include "EstimateController.hpp"

/**
 * @class RecorderEstimateController
 * @author Tales
 * @date 09/02/2016
 * @file EstimateListPresenter-unit.cpp
 * @brief Stub for EstimateController
 */
struct RecorderEstimateController : public EstimateController {
  CallRecorder &call_recorder;
  RecorderEstimateController(CallRecorder &c) : call_recorder{c} {}
  void setName(const std::string &newName) override
  {
    ORCA_RECORD_CALL(call_recorder);
    cout << "Renamed to: " << newName << endl;
  }
};

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
  void insertEstimate(const EstimateView &view) override { call_recorder.push("insertEstimate"); }
  void eraseEstimates(const std::unordered_set<std::string> &estimatesNames) override
  {
    call_recorder.push("eraseEstimates");
  }

  unique_ptr<EstimateController> selectEstimate(const string &) override
  {
    return make_unique<RecorderEstimateController>(call_recorder);
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
    WHEN("User press Ctrl-Insert")
    {
      cout << "Please, press Ctrl-Insert and close the program." << endl;
      THEN("Call EstimateController.insertEstimate()")
      {
        exec(host);
        REQUIRE(call_recorder.has("insertEstimate"));
      }
    }
    WHEN("A external menu is pressed")
    {
      estimatePresenter.newEstimate();
      THEN("Call EstimateController.insertEstimate()") { REQUIRE(call_recorder.has("insertEstimate")); }
    }
  }
}

SCENARIO_METHOD(EstimateListPresenterFixture,
                "EstimatePresenter remove an estimate",
                "[estimate-presenter-class][presenter]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User press Ctrl-Delete")
    {
      cout << "Please, select a estimate and press Ctrl-Delete and close the program." << endl;
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
                "[.][estimate-presenter-class][presenter][!mayfail]")
{
  GIVEN("A EstimatePresenter with a budget")
  {
    WHEN("User edits the name")
    {
      cout << "Please, edit an estimate name.";
      THEN("It calls EstimateController.setName()")
      {
        exec(host);
        REQUIRE(call_recorder.has("setName"));
      }
    }
  }
}
