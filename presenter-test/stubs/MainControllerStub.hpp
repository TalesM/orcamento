#pragma once

#include "BudgetControllerStub.hpp"
#include "MainController.hpp"

struct MainControllerStub : public MainController {
  CallRecorder &call_recorder;

  MainControllerStub(CallRecorder &r) : call_recorder{r} {}
  std::string pushBudget() override
  {
    static const char *names[] = {"A new one", "Another new one"};
    static auto index = 0;
    call_recorder.push("pushBudget");
    return names[(index++) % 2];
  }

  void popBudget() override
  {
    call_recorder.push("popBudget");  // Don't do nothing here...
  }

  vector<string> listBudgets() const override
  {
    call_recorder.push("listBudgets");
    return {"One", "Two", "Three"};
  }

  BudgetView getBudget(const std::string &name) override
  {
    ORCA_RECORD_CALL(call_recorder);
    return {
      name : name,
      controller : [this]() -> unique_ptr<BudgetController> { return make_unique<BudgetControllerStub>(call_recorder); }
    };
  }
};
