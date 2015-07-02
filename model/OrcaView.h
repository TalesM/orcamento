#ifndef _ORCA_VIEW_H
#define _ORCA_VIEW_H

#include <functional>
#include <string>
#include <SQLiteCpp/Database.h>

template<int N>
struct my_placeholder { static my_placeholder ph; };

template<int N>
my_placeholder<N> my_placeholder<N>::ph;

namespace std {
    template<int N>
    struct is_placeholder<::my_placeholder<N>> : std::integral_constant<int, N> { };
}

template<class R, class T, class...Types, class U, int... indices>
std::function<R (Types...)> bind_first(std::function<R (T, Types...)> f, U val, std::integer_sequence<int, indices...> /*seq*/) {
    return std::bind(f, val, my_placeholder<indices+1>::ph...);
}
template<class R, class T, class...Types, class U>
std::function<R (Types...)> bind_first(std::function<R (T, Types...)> f, U val) {
    return bind_first(f, val, std::make_integer_sequence<int, sizeof...(Types)>());
}

template<typename ...ARGS>
class OrcaView
{
public:
    typedef std::function<void(ARGS...)> HANDLER;
    OrcaView(const std::string &sql):
        _sql(sql)
    {}

    virtual ~OrcaView(){}

    void look(SQLite::Database &model, HANDLER handler)
    {
        SQLite::Statement stm(model, _sql);
        setup(stm);
        while(stm.executeStep()){
            exec(stm, handler);
        }
    }

protected:
    void query(const std::string &s){
        _sql = s;
    }
    
    std::string query() const {
        return _sql;
    }

    /**
     * @brief Use this to bind your stuff.
     */
    virtual void setup(SQLite::Statement &stm) {};

private:
    template<class ...FARGS>
    void exec(SQLite::Statement &stm, std::function<void(FARGS...)> handler, size_t c=0){
        exec(stm, bind_first(handler, stm.getColumn(c)), c+1);
    }

    void exec(SQLite::Statement &stm, std::function<void()> handler, size_t c=0){
        handler();
    }

private:
    std::string _sql;
};

#endif // _ORCA_VIEW_H
