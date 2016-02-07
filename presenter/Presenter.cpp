#include "Presenter.hpp"

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

namespace orca
{
using namespace nana;

// Necessary to define here because the time is foward declared on the header so the destructor can't be generated them.
Presenter::Presenter() = default;
Presenter::~Presenter() = default;

void Presenter::execTimeout(unsigned timeout, function<void(bool)> callback)
{
  timer timer;
  timer.interval(timeout);
  bool time_is_up = false;
  timer.elapse([&time_is_up]() {
    time_is_up = true;
    API::exit();
  });
  timer.start();
  present();
  exec();
  callback(not time_is_up);
} 
}

size_t orca::Presenter::schedule(unsigned timeout, function<void()> callback)
{
  aTimers.emplace_back();
  auto iterator = --(aTimers.end());
  auto &timer = aTimers.back();
  timer.interval(timeout);
  timer.elapse([callback, iterator, this]() {
    aTimers.erase(iterator);
    callback();
  });
  timer.start();
  return 0;
}
