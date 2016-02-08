#ifndef ORCA_PRESENTER_TEST_CONFIG_HPP
#define ORCA_PRESENTER_TEST_CONFIG_HPP

#include <catch.hpp>
#include <iostream>
#include "Presenter.hpp"

using namespace std;

/// Default timeout for tests
constexpr auto USER_TIMEOUT = 60000u;

/// Check if the execution ended ok
inline void checkFinishedOk(bool finishedOk)
{
  INFO("Execution timeout. Please execute the tasks more quickly.");
  REQUIRE(finishedOk);
}

/// Exec a presenter.
inline void exec(orca::Presenter &p, unsigned timeout = USER_TIMEOUT) { p.execTimeout(timeout, checkFinishedOk); }
#endif  // ORCA_PRESENTER_TEST_CONFIG_HPP