#ifndef ORCA_PRESENTER_FORMPRESENTER_HPP
#define ORCA_PRESENTER_FORMPRESENTER_HPP

#include <functional>
#include <list>
#include <stdexcept>

namespace nana
{
// Forward decl
class timer;
}

namespace orca
{
using namespace std;
/**
 * @class FormPresenter
 * @author Tales
 * @date 02/02/2016
 * @file FormPresenter.hpp
 * @brief The main container of presentation layer.
 */
class FormPresenter
{
 public:
  // Rule of five mandates if one is declared, all others must be.
  // I needed a virtual dtor, so the others are marked as default.
  FormPresenter();
  FormPresenter(const FormPresenter &) = default;
  FormPresenter(FormPresenter &&) = default;
  FormPresenter &operator=(const FormPresenter &) = default;
  FormPresenter &operator=(FormPresenter &&) = default;
  virtual ~FormPresenter();

  /**
   * @brief Executes the presenter until it times out.
   * @param timeout the max execution time
   * @param callback a callback.
   *
   * The callback is aways called, the parameter is a flag
   *  showing if it was aborted due the timeout (false) or
   *  finished on its own.
   */
  void execTimeout(unsigned timeout, function<void(bool)> callback);

  /**
   * @brief Schedule some command to execute.
   * @param timeout
   * @param callback a callback.
   */
  size_t schedule(unsigned timeout, function<void()> callback);

 protected:
  virtual void present() { throw std::logic_error("Not implemented"); }
 private:
  list<nana::timer> aTimers;
};
}

#endif  // ORCA_PRESENTER_FORMPRESENTER_HPP
