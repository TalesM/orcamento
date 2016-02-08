#ifndef ORCA_PRESENTER_PRESENTER_HPP
#define ORCA_PRESENTER_PRESENTER_HPP

namespace nana
{
class widget;
}
namespace orca
{
/**
 * @class Presenter
 * @author Tales
 * @date 08/02/2016
 * @file Presenter.hpp
 * @brief Presenter interface
 */
class Presenter
{
 public:
  /// Rule of five mandates if one is declared, all others must be.
  /// I needed a virtual dtor, so the others are marked as default.
  /// @{
  Presenter() = default;
  Presenter(const Presenter &) = default;
  Presenter(Presenter &&) = default;
  Presenter &operator=(const Presenter &) = default;
  Presenter &operator=(Presenter &&) = default;
  virtual ~Presenter() = default;
  /// @}
};
}

#endif  // ORCA_PRESENTER_PRESENTER_HPP
