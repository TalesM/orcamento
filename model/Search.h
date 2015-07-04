#ifndef _ORCA_SEARCHOPTION_H
#define _ORCA_SEARCHOPTION_H

#include <cassert>
#include <memory>
#include <sstream>
#include <set>
#include <string>
#include <vector>

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

struct SearchQuery{
    std::string query;
    std::vector<std::string> sValues;
    std::vector<int> iValues;
};

struct FieldDescriptor{
    std::string fieldNick;
    std::string fieldSql;
    enum Type {
        STRING,
        INT,
    }type;
    
    FieldDescriptor(const std::string &nick, Type type = STRING): 
        fieldNick(nick), fieldSql(nick), type(type){}
    FieldDescriptor(const std::string &nick, const std::string &sql, Type type = STRING): 
        fieldNick(nick), fieldSql(sql), type(type){}
    
    bool operator <(const std::string &o) const {
        return fieldNick < o;
    }
    bool operator <(const FieldDescriptor &o) const {
        return fieldNick < o.fieldNick;
    }
};

/**
 * @class SearchOption
 * @author Tales
 * @date 28/06/2015
 * @file SearchOption.h
 * @brief Create search options for numerics and string components...
 */
class SearchRaw: public std::enable_shared_from_this<SearchRaw>{
public:
    SearchRaw(const std::string &field);
    SearchRaw(const std::string &field, Operation op, const std::string &value);
    SearchRaw(std::shared_ptr<const SearchRaw> prev, Operation op, std::shared_ptr<const SearchRaw> next);
    ~SearchRaw();
    
    std::shared_ptr<const SearchRaw> equal(const std::string &s) const{
        return operate(Operation::EQUAL, s);
    }
    std::shared_ptr<const SearchRaw> less(const std::string &s) const{
        return operate(Operation::LESS, s);
    }
    std::shared_ptr<const SearchRaw> lessEqual(const std::string &s) const{
        return operate(Operation::LESS_EQUAL, s);
    }
    std::shared_ptr<const SearchRaw> different(const std::string &s) const{
        return operate(Operation::DIFFERENT, s);
    }
    std::shared_ptr<const SearchRaw> more(const std::string &s) const{
        return operate(Operation::MORE, s);
    }
    std::shared_ptr<const SearchRaw> moreEqual(const std::string &s) const{
        return operate(Operation::MORE_EQUAL, s);
    }
    std::shared_ptr<const SearchRaw> contains(const std::string &s) const{
        return operate(Operation::CONTAINS, s);
    }
    std::shared_ptr<const SearchRaw> prefix(const std::string &s) const{
        return operate(Operation::PREFIX, s);
    }
    std::shared_ptr<const SearchRaw> suffix(const std::string &s) const{
        return operate(Operation::SUFFIX, s);
    }
    
    std::shared_ptr<const SearchRaw> and_(std::shared_ptr<const SearchRaw>) const;
    std::shared_ptr<const SearchRaw> or_(std::shared_ptr<const SearchRaw>) const;
    
    
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
    
    const std::shared_ptr<const SearchRaw> &prev() const {
        assert(_operation == Operation::AND || _operation == Operation::OR);
        return _prev;
    }
    const std::shared_ptr<const SearchRaw> &next() const {
        assert(_operation == Operation::AND || _operation == Operation::OR);
        return _next;
    }
    ///@}
private:
    std::shared_ptr<const SearchRaw> operate(Operation op, const std::string &s) const;

    union {
        std::string _field;
        std::shared_ptr<const SearchRaw> _prev;
    };
    union {
        std::string _value;
        std::shared_ptr<const SearchRaw> _next;
    };
    Operation _operation = Operation::NONE;
};

typedef std::shared_ptr<const SearchRaw> Search;
/**
 * @brief Starts a search by the given field
 * @param field The field's name
 * @return the search object to be compound or passed to the view.
 */
inline Search search(const std::string &field){
    return std::make_shared<SearchRaw>(field);
}

/**
 * @brief Linearizes a search by a custom algorithm
 * @param origin the base search node
 * @param callableVisitor Any callable object.
 * @tparam CALLABLE Any type that may be called.
 */
template<typename CALLABLE>
inline auto linearize(const Search &origin, CALLABLE callableVisitor) -> decltype(callableVisitor(std::string(), Operation::NONE, std::string())){
    auto operation = origin->operation();
    if(operation == Operation::NONE){
        return callableVisitor(origin->field(), operation);
    }
    if(operation != Operation::AND && operation != Operation::OR){
        return callableVisitor(origin->field(), operation, origin->value());
    }
    return callableVisitor(linearize(origin->prev(), callableVisitor), operation, linearize(origin->next(), callableVisitor));
}

/**
 * @brief Transform a search in a query and variables
 * @param origin The search
 * @return A structure containing the query and necessary variables to bind.
 */
SearchQuery sqlize(const Search &origin, const std::set<FieldDescriptor> &description={});

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

inline bool operator ==(Search lhs, Search rhs){
    return lhs.get()==rhs.get();
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
