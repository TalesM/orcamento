#ifndef ORCA_PRESENTER_COMMON_INLINETEXTNOTIFIER_HPP
#define ORCA_PRESENTER_COMMON_INLINETEXTNOTIFIER_HPP

#include <functional>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/textbox.hpp>

namespace orca
{
/// Callback to InlineTextNotifier.
using ValueChangeCallback = std::function<void(const nana::listbox::index_pair&)>;
/**
 * @class InlineTextNotifier
 * @author Tales
 * @date 09/02/2016
 * @file InlineTextNotifier.hpp
 * @brief Enables editing inside listbox cell.
 */
class InlineTextNotifier : public nana::listbox::inline_notifier_interface
{
 private:
  virtual void create(nana::window wd) override
  {
    l_cell.create(wd);
    l_cell.transparent(true);
    l_cell.events().click([this] { a_indicator->selected(a_pos); });
    l_cell.events().dbl_click([this] {
      t_cell.show();
      t_cell.focus();
    });
    l_cell.events().mouse_move([this] { a_indicator->hovered(a_pos); });

    t_cell.create(wd, false);
    t_cell.multi_lines(false).line_wrapped(false).borderless(true);
    t_cell.events().focus([this](auto&& arg) {
      if(not arg.getting) {
        this->persist();
      }
    });
    t_cell.events().key_press([this](auto&& arg) {
      switch(arg.key) {
      case nana::keyboard::enter:
        this->persist();
        break;
      case nana::keyboard::escape:
        this->reset();
        break;
      default:
        break;
      }
    });
  }
  void activate(inline_indicator& ind, index_type pos) override
  {
    a_indicator = &ind;
    a_pos = pos;
  }

  void resize(const nana::size& dimension) override
  {
    t_cell.size(dimension);
    l_cell.size(dimension);
  }
  void set(const value_type& value)
  {
    t_cell.caption(value);
    l_cell.caption(value);
  }
  bool whether_to_draw() const override { return false; }
  void persist()
  {
    t_cell.hide();
    auto newValue = t_cell.caption();
    a_indicator->modify(a_pos, newValue);
    l_cell.caption(newValue);
    auto& host = dynamic_cast<nana::listbox&>(a_indicator->host());
    auto item = host.at(a_pos);
    if(const ValueChangeCallback* callback = item.value_ptr<const ValueChangeCallback>()) {
      (*callback)(a_pos);
    }
  }

  void reset()
  {
    t_cell.hide();
    t_cell.caption(l_cell.caption());
  }

 private:
  inline_indicator* a_indicator{nullptr};
  index_type a_pos;
  nana::textbox t_cell;
  nana::label l_cell;
};
}

#endif  // ORCA_PRESENTER_COMMON_INLINETEXTNOTIFIER_HPP