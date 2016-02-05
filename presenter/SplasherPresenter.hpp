#ifndef PRESENTER_SPLASHER_PRESENTER_HPP
#define PRESENTER_SPLASHER_PRESENTER_HPP

#include <functional>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include "Presenter.hpp"
#include "Manager.hpp"

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
  using CancelHandler = std::function<void()>;
  using SuccessHandler = std::function<void(std::unique_ptr<MainController> controller)>;
public:
  /**
   * @brief Creates a Splasher
   * @param manager the current Controller manager.
   * 
   * It instantiates all ui elements. It do not shows them, you need to call
   *  present() in order to launch it (always as a modal.)
   */
  SplasherPresenter(Manager &manager);  
  
  void present() override;
  
  /**
   * @brief Informs the callback in case of cancellation.
   * @param cancel_handler the handler
   */
  void onCancel(CancelHandler cancel_handler) {a_cancel_handler = cancel_handler;}
  CancelHandler onCancel() const {return a_cancel_handler;}
  
  void onSuccess(SuccessHandler success_handler) {a_success_handler = success_handler;}
  SuccessHandler onSuccess() const {return a_success_handler;}
private:
  Manager &a_manager;
  CancelHandler a_cancel_handler;
  SuccessHandler a_success_handler;
  std::unique_ptr<MainController> a_controller;

  form f_splasher;
  button b_new, b_open;
  place placer;
};

}

#endif // PRESENTER_SPLASHER_PRESENTER_HPP
