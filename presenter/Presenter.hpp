#ifndef ORCA_PRESENTER_HPP
#define ORCA_PRESENTER_HPP

#include <functional>

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

};

}

#endif // ORCA_PRESENTER_HPP
