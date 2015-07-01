#include "Search.h"

using namespace std;

SearchRaw::SearchRaw(const std::string& field):
    _field(field), _operation(Operation::NONE)
{
}

SearchRaw::SearchRaw(const std::string& field, Operation op, const std::string& value):
    _field(field), _value(value), _operation(op)
{
    assert(_operation != Operation::AND && _operation != Operation::OR && _operation != Operation::NONE);
}

SearchRaw::SearchRaw(std::shared_ptr<const SearchRaw> prev, Operation op, std::shared_ptr<const SearchRaw> next):
    _prev(prev), _next(next), _operation(op)
{
    assert(_operation == Operation::AND || _operation == Operation::OR);
}

SearchRaw::~SearchRaw()
{
    if(_operation == Operation::NONE){
        _field.~string();
    } else if(_operation == Operation::AND || _operation == Operation::OR){
        _prev.~shared_ptr<const SearchRaw>();
        _next.~shared_ptr<const SearchRaw>();
    } else {
        _field.~string();
        _value.~string();
    }
}

std::shared_ptr<SearchRaw> SearchRaw::and_(std::shared_ptr<const SearchRaw> rhs) const
{
    return make_shared<SearchRaw>(shared_from_this(), Operation::AND, rhs);
}
std::shared_ptr<SearchRaw> SearchRaw::or_(std::shared_ptr<const SearchRaw> rhs) const
{
    return make_shared<SearchRaw>(shared_from_this(), Operation::OR, rhs);
}

std::shared_ptr<SearchRaw> SearchRaw::operate(Operation op, const std::string& s) const
{
    auto v = make_shared<SearchRaw>(_field, op, s);
    if(_operation == Operation::NONE){
        return v;
    }
    return and_(v);
}
