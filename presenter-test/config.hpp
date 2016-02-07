#ifndef ORCA_PRESENTER_TEST_CONFIG_HPP
#define ORCA_PRESENTER_TEST_CONFIG_HPP

#include <catch.hpp>
#include <iostream>

using namespace std;

/// Default timeout for tests
constexpr auto USER_TIMEOUT = 60000u;

/// Check if the execution ended ok
inline void checkFinishedOk(bool finishedOk) { REQUIRE(finishedOk); }
#endif  // ORCA_PRESENTER_TEST_CONFIG_HPP