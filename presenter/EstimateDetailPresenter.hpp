#ifndef ORCA_PRESENTER_ESTIMATEDETAILPRESENTER_HPP
#define ORCA_PRESENTER_ESTIMATEDETAILPRESENTER_HPP

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>
#include "EstimateView.hpp"
#include "EstimateController.hpp"
#include "FormPresenter.hpp"

namespace orca
{
/**
 * @class EstimateDetailPresenter
 * @author Tales
 * @date 10/02/2016
 * @file EstimateDetailPresenter.hpp
 * @brief Shows an estimate in detail.
 */
class EstimateDetailPresenter : public FormPresenter
{
 public:
  EstimateDetailPresenter(const EstimateView &view);
  void present() override;

  void reset(const EstimateView &view);
  
  EstimateView get();

 private:
  // The controller
  EstimateView a_view;
  std::shared_ptr<EstimateController> a_controller;
  // The form
  nana::form f_estimateDetail;
  // The controls
  nana::label l_name;
  nana::textbox t_name;
  nana::label l_category;
  nana::textbox t_category;
  nana::label l_operation;
  nana::combox c_operation;
  nana::label l_estimated;
  nana::spinbox s_estimated;
  nana::label l_fulfilled;
  nana::spinbox s_fulfilled;
  nana::label l_dueDay;
  nana::spinbox s_dueDay;
  nana::label l_done;
  nana::checkbox c_done;
  // The layout
  nana::place placer;
};
}

#endif  // ORCA_PRESENTER_ESTIMATEDETAILPRESENTER_HPP
