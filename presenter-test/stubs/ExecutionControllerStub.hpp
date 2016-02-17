#pragma once
#include "../common.hpp"
#include "ExecutionController.hpp"

namespace orca
{
/**
 * @class ExecutionControllerStub
 * @author Tales
 * @date 17/02/2016
 * @file ExecutionControllerStub.hpp
 * @brief Execution controller stub
 */
struct ExecutionControllerStub : public ExecutionController {
  CallRecorder &call_recorder;
  ExecutionControllerStub(CallRecorder &c) : call_recorder{c} {}
  void setDate(const string &newValue) override { ORCA_RECORD_CALL(call_recorder); }
  void setAmount(unsigned newValue) override { ORCA_RECORD_CALL(call_recorder); }
  void setOperation(Operation newValue) override { ORCA_RECORD_CALL(call_recorder); }
  void setAccount(std::string newValue) override { ORCA_RECORD_CALL(call_recorder); }
  void setEstimate(std::string newValue) override { ORCA_RECORD_CALL(call_recorder); }
  void setCategory(std::string newValue) override { ORCA_RECORD_CALL(call_recorder); }
};
}
