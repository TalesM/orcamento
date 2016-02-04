#include "SplasherPresenter.hpp"

orca::SplasherPresenter::SplasherPresenter():
  fSplasher(API::make_center(600, 400)),
  bNew(fSplasher, "New"),
  bOpen(fSplasher, "Open"),
  placer(fSplasher)
{
  placer.div("<main>");
  placer.field("main") << bNew << bOpen;
  placer.collocate();
}

orca::SplasherPresenter::~SplasherPresenter()
{
}

void orca::SplasherPresenter::present()
{
  fSplasher.show();
}
