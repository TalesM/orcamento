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

SearchOption::SearchOption(std::shared_ptr<SearchOption> prev, Operation op, std::shared_ptr<SearchOption> next):
    _prev(prev), _next(next), _operation(op)
{
    assert(_operation == Operation::AND || _operation == Operation::OR);
}

SearchOption::~SearchOption()
{
    if(_operation == Operation::NONE){
        _field.~string();
    } else if(_operation == Operation::AND || _operation == Operation::OR){
        _field.~string();
        _value.~string();
    } else {
        _prev.~shared_ptr<SearchOption>();
        _next.~shared_ptr<SearchOption>();
    }
}

std::shared_ptr<SearchOption> SearchOption::and_(std::shared_ptr<SearchOption>) const
{
}

std::shared_ptr<SearchOption> SearchOption::contains(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::different(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::equal(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::less(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::lessEqual(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::more(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::moreEqual(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::or_(std::shared_ptr<SearchOption>) const
{
}

std::shared_ptr<SearchOption> SearchOption::prefix(const std::string& s) const
{
}

std::shared_ptr<SearchOption> SearchOption::suffix(const std::string& s) const
{
}

