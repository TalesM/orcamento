#ifndef ORCA_PRESENTER_TEST_BUDGETCONTROLLER_STUB_HPP
#define ORCA_PRESENTER_TEST_BUDGETCONTROLLER_STUB_HPP

#include "../common.hpp"
#include "BudgetController.hpp"
#include "EstimateControllerStub.hpp"
#include "ExecutionControllerStub.hpp"

/**
 * @class RecorderBudgetController
 * @author Tales
 * @date 08/02/2016
 * @file EstimateListPresenter-unit.cpp
 * @brief Stub for BudgetController
 */
struct BudgetControllerStub : public BudgetController {
  CallRecorder &call_recorder;
  BudgetControllerStub(CallRecorder &c) : call_recorder{c} {}
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
    ORCA_RECORD_CALL(call_recorder);
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

  std::vector<ExecutionView> listExecutions() const override
  {
    ORCA_RECORD_CALL(call_recorder);
    return {
        {1, "2006-02-02", 100, Operation::INCOME, "POCKET", "Estatimate 1", "CAT"},
        {2, "2006-02-04", 1000, Operation::EXPENSE, "POCKET", "Estatimate 2", "CAT"},
        {3, "2006-04-15", 500, Operation::EXCHANGE, "POCKET", "Estatimate 4", "CAT"},
    };
  }
  ExecutionView insertExecution() override
  {
    ORCA_RECORD_CALL(call_recorder);
    return {
        15,
        "2006-10-13",
        100,
        Operation::INCOME,
        "POCKET",
        "Estatimate 3",
        "CAT",
        [this]() -> unique_ptr<ExecutionController> { return make_unique<ExecutionControllerStub>(call_recorder); }};
  }

  void eraseExecutions(const std::unordered_set<std::string> &estimatesNames) override
  {
    ORCA_RECORD_CALL(call_recorder);
  }
};
#endif  // ORCA_PRESENTER_TEST_BUDGETCONTROLLER_STUB_HPP
