
/**
 * This file is the user oriented part of amachi STL
 * Open source by MIT by amachi Inori
 * 
 * Main header file of string
 * The string is declared and defined in this file with namespace AMI_std
 * Some overloaded stream operations are also defined in this file with namespace AMI_std
**/


# pragma once
# include "AMI_vector.hpp"
# include <iostream>

__ASTL_NAMESPACE_START

inline bool isUpperAlpha(char _c) { return _c >= 'A' && _c <= 'Z'; }
inline bool isLowerAlpha(char _c) { return _c >= 'a' && _c <= 'z'; }

/**
 * String class based on full specialized AMI_std::vector
**/
class string : public vector<char, __secondary_allocator> {
public:
    string() noexcept = default;
    explicit string(size_type _length) noexcept : vector(_length) { }
    string(size_type _length, const char &_c) noexcept : vector(_length, _c) { }
    string(size_type _length, const char* _str) noexcept : vector((char*)_str, (char*)(_str + _length)) { }
    string(const char* _str) noexcept : vector((char*)_str, (char*)_str + strlen(_str)) {}
    string(iterator _begin, iterator _end) noexcept : vector(_begin, _end) { }
    string(string&& _move_ori) noexcept : vector(_move_ori) { }
    string(const string& _copy_ori) noexcept : vector(_copy_ori) { }
    string& operator=(const string&) noexcept = default;
    string& operator=(string&&) noexcept = default;
    size_type length() const { return vector::size(); }
    string& append(const char &_c) { 
        vector::push_back(_c);
        return (*this);
    }
    string& append(const string &_c) { 
        while (this->size() + _c.size() > this->capacity()) 
            this->__enlarge();
        AMI_std::uninitialized_copy(_c.__map_begin, _c.__map_end, this->end());
        this->__map_end += _c.size();
        return (*this);
    }
    char* c_str() const { return vector::__map_begin; }
    string& reverse() { 
        vector::reverse();
        return (*this);
    }
    string substr(iterator _begin, iterator _end) { return string(_begin, _end); }
    string substr(size_type _begin, size_type _end) { return substr(_begin + vector::begin(), _end + vector::begin()); }
    bool compare(const string &_str) {
        if (this->length() != _str.length()) return false;
        for (size_type i = 0; i < this->length(); i++) {
            if (this->at(i) != *(_str.__map_begin + i)) return false;
        }
        return true;
    }
    bool operator==(const string &other_str) {
        return compare(other_str);
    }
    string operator+(const string &_c) const { //加法运算符绝对不返回引用
        string temp = *this;
        temp += _c;
        return temp;
    }
    string& operator+=(const string &_c) {
        return (append(_c));
    }
    string& to_lower() {
        for (auto &c : *this) {
            if (isUpperAlpha(c)) c = c + 'a' - 'A';
        }
        return (*this);
    }
    string& to_upper() {
        for (auto &c : *this) {
            if (isLowerAlpha(c)) c = c + 'A' - 'a';
        }
        return (*this);
    }
# ifndef AMI_STL_STRICT_MODE
    operator bool() { return this->empty(); }
# endif
};

std::ostream &operator<<(std::ostream& os, const string &str) {
    os << str.c_str();
    return os;
}

std::istream &operator>>(std::istream& is, string &str) {
    char _str[is.width()];
    is >> _str;
    str.clear();
    str.append({_str});
    return is;
}

__ASTL_NAMESPACE_END 