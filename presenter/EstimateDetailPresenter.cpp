#include "EstimateDetailPresenter.hpp"
#include <iomanip>
#include <sstream>

using namespace nana;
using namespace std;

orca::EstimateDetailPresenter::EstimateDetailPresenter(const EstimateView& view)
    : placer(f_estimateDetail), a_view(view)
{
  /// Setting up controls
  // name
  l_name.create(f_estimateDetail);
  l_name.caption("name");
  t_name.create(f_estimateDetail);
  t_name.multi_lines(false);
  API::tabstop(t_name);
  API::eat_tabstop(t_name, false);
  t_name.events().focus([this](auto&& arg) {
    auto newName = t_name.caption();
    if(not arg.getting and newName != a_view.name) {
      a_controller->setName(newName);
      a_view.name = newName;
      t_name.edited_reset();
    }
  });

  // category
  l_category.create(f_estimateDetail);
  l_category.caption("category");
  t_category.create(f_estimateDetail);
  API::tabstop(t_category);
  API::eat_tabstop(t_category, false);
  t_category.events().focus([this](auto&& arg) {
    auto newCat = t_category.caption();
    if(!not arg.getting and newCat != a_view.category) {
      a_controller->setCategory(newCat);
      a_view.category = newCat;
      t_category.edited_reset();
    }
  });

  // operation
  l_operation.create(f_estimateDetail);
  l_operation.caption("operation");
  c_operation.create(f_estimateDetail);
  c_operation.editable(false);
  // TODO: Replace it with some solution that does not require it to be repeated in every source.
  c_operation.push_back("INCOME");
  c_operation.push_back("EXPENSE");
  c_operation.push_back("TRANSFERENCE");
  API::tabstop(c_operation);
  c_operation.events().selected([this](auto&& arg) {
    Operation newOp = static_cast<Operation>(c_operation.option() + 1);
    if(a_controller) {
      a_controller->setOperation(newOp);
      a_view.operation = newOp;
    }
  });

  // estimated
  l_estimated.create(f_estimateDetail);
  l_estimated.caption("estimated");
  s_estimated.create(f_estimateDetail);
  s_estimated.range(0, +1'000'000, 1);
  API::tabstop(s_estimated);
  API::eat_tabstop(s_estimated, false);
  s_estimated.events().focus([ this ](auto&& arg) {
    auto estimatedValue = s_estimated.to_int() * 100;
    if(not arg.getting and estimatedValue != a_view.estimated) {
      a_controller->setEstimated(estimatedValue);
      a_view.estimated = estimatedValue;
    }
  });

  // fulfilled
  l_fulfilled.create(f_estimateDetail);
  l_fulfilled.caption("fulfilled");
  s_fulfilled.create(f_estimateDetail);
  s_fulfilled.range(-1'000'000, +1'000'000, 1);
  s_fulfilled.enabled(false);

  // dueDay
  l_dueDay.create(f_estimateDetail);
  l_dueDay.caption("dueDay");
  s_dueDay.create(f_estimateDetail);
  s_dueDay.range(0, 31, 1);
  API::tabstop(s_dueDay);
  API::eat_tabstop(s_dueDay, false);
  s_dueDay.events().focus([ this](auto&& arg) {
    short dueDay = s_dueDay.to_int();
    if(not arg.getting and dueDay != a_view.dueDay) {
      a_controller->setDueDay(dueDay);
      a_view.dueDay = dueDay;
    }
  });

  // done
  l_done.create(f_estimateDetail);
  l_done.caption("done");
  c_done.create(f_estimateDetail);
  c_done.events().focus([ this ](auto&& arg) {
    auto done = c_done.checked();
    if(not arg.getting and a_view.done != done) {
      a_controller->setDone(done);
      a_view.done = done;
    }
  });
  ;
  API::tabstop(c_done);

  // Layout
  placer.div("<main grid=[2,7]>");
  placer.field("main") << l_name << t_name << l_category << t_category << l_operation << c_operation << l_estimated
                       << s_estimated << l_fulfilled << s_fulfilled << l_dueDay << s_dueDay << l_done << c_done;

  placer.collocate();

  // Reading values
  reset(view);
}

void orca::EstimateDetailPresenter::present() { f_estimateDetail.modality(); }
void orca::EstimateDetailPresenter::reset(const EstimateView& view)
{
  t_name.caption(view.name);
  t_name.edited_reset();
  t_category.caption(view.category);
  t_category.edited_reset();
  switch(view.operation) {
  case Operation::INCOME:
    c_operation.option(0);
    break;
  case Operation::EXPENSE:
    c_operation.option(1);
    break;
  case Operation::EXCHANGE:
    c_operation.option(2);
    break;
  }
  stringstream ss;
  ss << defaultfloat << (view.estimated / 100.0);
  s_estimated.value(ss.str());
  ss.str("");
  ss << defaultfloat << setprecision(2) << (view.fulfilled / 100.0);
  s_fulfilled.value(ss.str());
  ss.str("");
  ss << view.dueDay;
  s_dueDay.value(ss.str());
  c_done.check(view.done);

  a_controller = view.controller();
  if(not a_controller) {
    throw std::logic_error("Trying to preesent a non persisted (user-created) view.");
  }
}

orca::EstimateView orca::EstimateDetailPresenter::get()
{
  return a_view;
}
