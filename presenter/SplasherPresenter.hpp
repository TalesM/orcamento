#ifndef PRESENTER_SPLASHER_PRESENTER_HPP
#define PRESENTER_SPLASHER_PRESENTER_HPP

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include "Presenter.hpp"

namespace orca
{
using namespace nana;
/**
 * @class SplasherPresenter
 * @author Tales
 * @date 04/02/2016
 * @file SplasherPresenter.hpp
 * @brief The splasher screen.
 */
class SplasherPresenter: public Presenter
{
public:
  SplasherPresenter();
  ~SplasherPresenter();
  
  void present() override;
private:
  form fSplasher;
  button bNew, bOpen;
  place placer;
};

}

#endif // PRESENTER_SPLASHER_PRESENTER_HPP
