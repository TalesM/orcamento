#include "SearchOption.h"

using namespace std;

SearchOption::SearchOption(const std::string& field):
    _field(field), _operation(Operation::NONE)
{
}

SearchOption::SearchOption(const std::string& field, Operation op, const std::string& value):
    _field(field), _value(value), _operation(op)
{
    assert(_operation != Operation::AND && _operation != Operation::OR && _operation != Operation::NONE);
}

SearchOption::SearchOption(std::shared_ptr<const SearchOption> prev, Operation op, std::shared_ptr<const SearchOption> next):
    _prev(prev), _next(next), _operation(op)
{
    assert(_operation == Operation::AND || _operation == Operation::OR);
}

SearchOption::~SearchOption()
{
    if(_operation == Operation::NONE){
        _field.~string();
    } else if(_operation == Operation::AND || _operation == Operation::OR){
        _prev.~shared_ptr<const SearchOption>();
        _next.~shared_ptr<const SearchOption>();
    } else {
        _field.~string();
        _value.~string();
    }
}

std::shared_ptr<SearchOption> SearchOption::and_(std::shared_ptr<const SearchOption> rhs) const
{
    return make_shared<SearchOption>(shared_from_this(), Operation::AND, rhs);
}
std::shared_ptr<SearchOption> SearchOption::or_(std::shared_ptr<const SearchOption> rhs) const
{
    return make_shared<SearchOption>(shared_from_this(), Operation::OR, rhs);
}

std::shared_ptr<SearchOption> SearchOption::operate(Operation op, const std::string& s) const
{
    auto v = make_shared<SearchOption>(_field, op, s);
    if(_operation == Operation::NONE){
        return v;
    }
    return and_(v);
}
