#ifndef ORCA_PRESENTER_TEST_CONFIG_HPP
#define ORCA_PRESENTER_TEST_CONFIG_HPP

#include <iostream>
#include <catch.hpp>
#include <nana/gui.hpp>
#include "FormPresenter.hpp"

using namespace std;
using namespace orca;
using namespace nana;

/// Default timeout for tests
constexpr auto USER_TIMEOUT = 60000u;

/// Check if the execution ended ok
inline void checkFinishedOk(bool finishedOk)
{
  INFO("Execution timeout. Please execute the tasks more quickly.");
  REQUIRE(finishedOk);
}

/// Exec a presenter.
inline void exec(FormPresenter &p, unsigned timeout = USER_TIMEOUT) { p.execTimeout(timeout, checkFinishedOk); }
inline void exec(form &f, unsigned timeout = USER_TIMEOUT){
  f.show();
  f.wait_for_this();
}

/// Mock... or Stub?
struct CallRecorder {
  vector<string> record;
  bool has(const std::string &call) const { return std::find(record.begin(), record.end(), call) != record.end(); }
  void push(std::string call) { record.push_back(std::move(call)); }
};

#define ORCA_RECORD_CALL(CALL_RECORDER) CALL_RECORDER.push(__FUNCTION__)

#endif  // ORCA_PRESENTER_TEST_CONFIG_HPP
