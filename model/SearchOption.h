#ifndef _ORCA_SEARCHOPTION_H
#define _ORCA_SEARCHOPTION_H

#include <cassert>
#include <memory>
#include <sstream>
#include <string>

enum class Operation{
    NONE,
    EQUAL,
    LESS,
    LESS_EQUAL,
    DIFFERENT,
    MORE,
    MORE_EQUAL,
    CONTAINS,
    PREFIX,
    SUFFIX,

    AND,
    OR,
};


/**
 * @class SearchOption
 * @author Tales
 * @date 28/06/2015
 * @file SearchOption.h
 * @brief Create search options for numerics and string components...
 */
class SearchOption: public std::enable_shared_from_this<SearchOption>{
public:
    SearchOption(const std::string &field);
    SearchOption(const std::string &field, Operation op, const std::string &value);
    SearchOption(std::shared_ptr<const SearchOption> prev, Operation op, std::shared_ptr<const SearchOption> next);
    ~SearchOption();
    
    std::shared_ptr<SearchOption> equal(const std::string &s) const{
        return operate(Operation::EQUAL, s);
    }
    std::shared_ptr<SearchOption> less(const std::string &s) const{
        return operate(Operation::LESS, s);
    }
    std::shared_ptr<SearchOption> lessEqual(const std::string &s) const{
        return operate(Operation::LESS_EQUAL, s);
    }
    std::shared_ptr<SearchOption> different(const std::string &s) const{
        return operate(Operation::DIFFERENT, s);
    }
    std::shared_ptr<SearchOption> more(const std::string &s) const{
        return operate(Operation::MORE, s);
    }
    std::shared_ptr<SearchOption> moreEqual(const std::string &s) const{
        return operate(Operation::MORE_EQUAL, s);
    }
    std::shared_ptr<SearchOption> contains(const std::string &s) const{
        return operate(Operation::CONTAINS, s);
    }
    std::shared_ptr<SearchOption> prefix(const std::string &s) const{
        return operate(Operation::PREFIX, s);
    }
    std::shared_ptr<SearchOption> suffix(const std::string &s) const{
        return operate(Operation::SUFFIX, s);
    }
    
    std::shared_ptr<SearchOption> and_(std::shared_ptr<const SearchOption>) const;
    std::shared_ptr<SearchOption> or_(std::shared_ptr<const SearchOption>) const;
    
    
    ///@name getters
    ///@{
    Operation operation() const {
        return _operation;
    }
    
    const std::string &field() const{
        assert(_operation != Operation::AND && _operation != Operation::OR);
        return _field;
    }
    const std::string &value() const{
        assert(_operation != Operation::AND && _operation != Operation::OR && _operation != Operation::NONE);
        return _value;
    }
    
    const std::shared_ptr<const SearchOption> &prev() const {
        assert(_operation == Operation::AND || _operation == Operation::OR);
        return _prev;
    }
    const std::shared_ptr<const SearchOption> &next() const {
        assert(_operation == Operation::AND || _operation == Operation::OR);
        return _next;
    }
    ///@}
private:
    std::shared_ptr<SearchOption> operate(Operation op, const std::string &s) const;

    union {
        std::string _field;
        std::shared_ptr<const SearchOption> _prev;
    };
    union {
        std::string _value;
        std::shared_ptr<const SearchOption> _next;
    };
    Operation _operation = Operation::NONE;
};

typedef std::shared_ptr<const SearchOption> Search;
/**
 * @brief Starts a search by the given field
 * @param field The field's name
 * @return the search object to be compound or passed to the view.
 */
inline Search search(const std::string &field){
    return std::make_shared<SearchOption>(field);
}

template<typename CALLABLE>
inline auto linearize(const std::shared_ptr<const SearchOption> &origin, CALLABLE callableVisitor) -> decltype(callableVisitor(std::string(), Operation::NONE, std::string())){
    auto operation = origin->operation();
    if(operation != Operation::AND && operation != Operation::OR){
        return callableVisitor(origin->field(), operation, origin->value());
    }
    return callableVisitor(linearize(origin->prev(), callableVisitor), operation, linearize(origin->next(), callableVisitor));
}

//    
inline Search operator &&(Search lhs, Search rhs){
    return lhs->and_(rhs);
}
inline Search operator ||(Search lhs, Search rhs){
    return lhs->or_(rhs);
}

template <typename VALUE>
std::string convertToString(VALUE v){
    std::stringstream ss;
    ss << v;
    return ss.str();
}

template <typename VALUE>
Search operator ==(Search lhs, VALUE v){
    return lhs->equal(convertToString(v));
}
template <typename VALUE>
Search operator <(Search lhs, VALUE v){
    return lhs->less(convertToString(v));
}
template <typename VALUE>
Search operator <=(Search lhs, VALUE v){
    return lhs->lessEqual(convertToString(v));
}
template <typename VALUE>
Search operator !=(Search lhs, VALUE v){
    return lhs->different(convertToString(v));
}
template <typename VALUE>
Search operator >(Search lhs, VALUE v){
    return lhs->more(convertToString(v));
}
template <typename VALUE>
Search operator >=(Search lhs, VALUE v){
    return lhs->moreEqual(convertToString(v));
}

#endif // _ORCA_SEARCHOPTION_H
