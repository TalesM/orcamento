#include "Presenter.hpp"

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/timer.hpp>

namespace orca{

Presenter::Presenter()
{
}

Presenter::~Presenter()
{
}

void Presenter::execTimeout(unsigned timeout, function<void(bool)> callback)
{
  using namespace nana;
  form fm;
  label lb(fm);
  lb.caption("Hi Mundo");
  fm.show();
  
  timer timer;
  timer.interval(timeout);
  bool time_is_up = false;
  timer.elapse([&time_is_up](){
    time_is_up = true;
    API::exit();
  });
  timer.start();
  exec();
  callback(not time_is_up);
}
  
}
