#pragma once
#include <string>
#include "Operation.hpp"

namespace orca
{
/**
 * @class ExecutionController
 * @author Tales
 * @date 16/02/2016
 * @file ExecutionController.hpp
 * @brief Controls execution
 */
class ExecutionController
{
 public:
  ExecutionController() {}
  virtual ~ExecutionController() = default;
  virtual void setDate(const string &newValue) = 0;
  virtual void setAmount(unsigned newValue) = 0;
  virtual void setOperation(Operation newValue) = 0;
  virtual void setAccount(std::string newValue) = 0;
  virtual void setEstimate(std::string newValue) = 0;
  virtual void setCategory(std::string newValue) = 0;
};
}
