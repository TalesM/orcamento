#ifndef ORCA_PRESENTER_HPP
#define ORCA_PRESENTER_HPP

#include <functional>
#include <list>

namespace nana{
//Forward decl
class timer; 
class widget; 
}

namespace orca
{
using namespace std;
/**
 * @class Presenter
 * @author Tales
 * @date 02/02/2016
 * @file Presenter.hpp
 * @brief The main container of presentation layer.
 */
class Presenter
{
public:
  Presenter();
  ~Presenter();
  
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
  virtual void present(){
    //throw?
  }
private:
  list<nana::timer> aTimers;
};

}

#endif // ORCA_PRESENTER_HPP
