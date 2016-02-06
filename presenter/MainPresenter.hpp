#ifndef ORCA_PRESENTER_MAINPRESENTER_HPP
#define ORCA_PRESENTER_MAINPRESENTER_HPP

#include "Presenter.hpp"  // Base class: orca::Presenter

namespace orca
{
class Manager;

class MainPresenter : public Presenter
{
 public:
  MainPresenter(Manager &manager);

 public:
  void present() override;
};
}

#endif  // ORCA_PRESENTER_MAINPRESENTER_HPP
