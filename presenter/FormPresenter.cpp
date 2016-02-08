#include "FormPresenter.hpp"

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>

namespace orca
{
using namespace nana;

// Necessary to define here because the time is foward declared on the header so the destructor can't be generated them.
FormPresenter::FormPresenter() = default;
FormPresenter::~FormPresenter(){
  for(auto &&timer: aTimers){
    timer.stop();
  }
}

void FormPresenter::execTimeout(unsigned timeout, function<void(bool)> callback)
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
  for(auto &&timer: aTimers){
    timer.stop();
  }
  aTimers.clear();
  callback(not time_is_up);
} 
}

size_t orca::FormPresenter::schedule(unsigned timeout, function<void()> callback)
{
  aTimers.emplace_back();
  auto iterator = --(aTimers.end());
  auto &timer = aTimers.back();
  timer.interval(timeout);
  timer.elapse([callback, iterator, this]() {
    callback();
    iterator->stop();
    aTimers.erase(iterator);
  });
  timer.start();
  return 0;
}
