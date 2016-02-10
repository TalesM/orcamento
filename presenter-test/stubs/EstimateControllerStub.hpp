#ifndef ORCA_PRESENTER_TEST_ESTIMATECONTROLLER_TEST_HPP
#define ORCA_PRESENTER_TEST_ESTIMATECONTROLLER_TEST_HPP

#include "../common.hpp"
#include "EstimateController.hpp"

/**
 * @class RecorderEstimateController
 * @author Tales
 * @date 09/02/2016
 * @file EstimateListPresenter-unit.cpp
 * @brief Stub for EstimateController
 */
struct EstimateControllerStub : public EstimateController {
  CallRecorder &call_recorder;
  EstimateControllerStub(CallRecorder &c) : call_recorder{c} {}
  void setName(const std::string &newName) override
  {
    ORCA_RECORD_CALL(call_recorder);
    cout << "Renamed to: " << newName << endl;
  }

  void setCategory(const std::string &newCategory) override
  {
    ORCA_RECORD_CALL(call_recorder);
    cout << "Categorized as " << newCategory << endl;
  }

  void setOperation(const Operation &operation) override
  {
    ORCA_RECORD_CALL(call_recorder);
    cout << "Operation: " << static_cast<int>(operation) << endl;
  }
  
  void setEstimated(unsigned value) override 
  {
    ORCA_RECORD_CALL(call_recorder);
    cout << "Estimated value: " << value / 100.0 << endl;
  }
  
  virtual void setDueDay(short value){
    ORCA_RECORD_CALL(call_recorder);
    cout << "Due: " << value << endl;
  }
  virtual void setDone(bool value){
    ORCA_RECORD_CALL(call_recorder);
    cout << "Done?: " << value << endl;
  }
};

#endif  // ORCA_PRESENTER_TEST_ESTIMATECONTROLLER_TEST_HPP
