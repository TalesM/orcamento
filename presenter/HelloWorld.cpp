/**
* From the tutorial https://github.com/qPCR4vir/nana-docs/wiki/Getting-Started
**/
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>

int main(int argc, char const *argv[]) {
  using namespace nana;
  form fm;
  button btn(fm, rectangle(0, 0, 100, 20));
  btn.caption("Hello Nana");
  btn.events().click(API::exit);
  fm.show();
  exec();
  return 0;
}
