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

std::shared_ptr<const SearchRaw> SearchRaw::and_(std::shared_ptr<const SearchRaw> rhs) const
{
    return make_shared<SearchRaw>(shared_from_this(), Operation::AND, rhs);
}
std::shared_ptr<const SearchRaw> SearchRaw::or_(std::shared_ptr<const SearchRaw> rhs) const
{
    return make_shared<SearchRaw>(shared_from_this(), Operation::OR, rhs);
}

std::shared_ptr<const SearchRaw> SearchRaw::operate(Operation op, const std::string& s) const
{
    auto v = make_shared<SearchRaw>(_field, op, s);
    if(_operation == Operation::NONE){
        return v;
    }
    return and_(v);
}

SearchQuery sqlize(const Search &origin, const std::set<FieldDescriptor> &description){
    SearchQuery q{};
    static const char *values[] = {
        " AND RAISE(FAIL, 'xxx')",
        "=",
        "<",
        "<=",
        "<>",
        ">",
        ">=",
        "LIKE",
        "LIKE",
        "LIKE",
        "AND",
        "OR",
    };
    q.query = linearize(origin, [&q, &description](const string &a, Operation op, const string &b="") -> string{
        if(op == Operation::OR || op == Operation::AND){
            if(a==""){
                return b;
            }
            return "("+a+" "+values[int(op)]+" "+b+")";
        }
        if(!description.count(a)){
            return "";
        }
        auto &fieldDescription = *description.lower_bound(a);
        if(op == Operation::CONTAINS){
            q.sValues.push_back("%"+b+"%");
        }else if(op == Operation::PREFIX){
            q.sValues.push_back(b+"%");
        }else if(op == Operation::SUFFIX){
            q.sValues.push_back("%"+b);
        }else {
            if(fieldDescription.type == FieldDescriptor::INT){
                int i;
                stringstream ss(b), tt;
                ss >> i;
                q.iValues.push_back(i);
                tt << q.iValues.size();
                return fieldDescription.fieldSql+" "+values[int(op)]+" :i_"+tt.str();
            } else if(fieldDescription.type == FieldDescriptor::MONEY){ 
                double d;
                stringstream ss(b), tt;
                ss >> d;
                q.iValues.push_back(int(d*100));
                tt << q.iValues.size();
                return fieldDescription.fieldSql+" "+values[int(op)]+" :i_"+tt.str();
            } else { //if fieldDescription.type == FieldDescriptor::STRING
                q.sValues.push_back(b);
            }
        }
        stringstream ss;
        ss << q.sValues.size();
        return fieldDescription.fieldSql+" "+values[int(op)]+" :s_"+ss.str();
    });
    return q;

}