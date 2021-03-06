
/**
 * This is a Standard C++ Library header.
 * This file is the user oriented part of amachi STL
 * Open source by MIT by amachi Inori
 * Copyright (C) 2020-2020 Amachi Inori.
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
 * Some practical methods have been added
 * 
 * Inherited from specialized vector
**/
class string : public vector<char, __secondary_allocator> {
public:
    /** 
     * Default constructor of string
     * @return no return 
     * 
    **/
    string() noexcept = default;

    /** 
     * Constructor of string with a uint length, chars uses its default constructor 
     * Pass-call function
     * @return no return 
     * @param length - unsigned int - the length of the array
    **/
    explicit string(size_type _length) noexcept : vector(_length) { }

    /** 
     * Constructor of string with a uint length, all the element were set to _c
     * Pass-call function
     * @return no return 
     * @param _length - unsigned int    - the length of the array
     * @param _c      - const char      - the copied element
    **/
    string(size_type _length, const char _c) noexcept : vector(_length, _c) { }

    /** 
     * Constructor of string with a const char*
     * Pass-call function
     * @return no return 
     * @param _str - const char* - the origin char array
    **/
    string(const char* _str) noexcept : vector((char*)_str, (char*)_str + strlen(_str)) {}

    /** 
     * Constructor of string with two iterator to copy all the chars between _begin and _end 
     * Pass-call function
     * @return no return 
     * @param _begin - char* - the start point of the copied string
     * @param _end   - char* - the end point of the copied string
    **/
    string(iterator _begin, iterator _end) noexcept : vector(_begin, _end) { }

    /**
     * Move constructor
     * Pass-call function
     * @return no return 
     * @param __move_ori - rvalue of a string
    **/
    string(string&& _move_ori) noexcept : vector(_move_ori) { }

    /** 
     * Copy constructor of string
     * Pass-call function
     * @return no return 
     * @param _copy_ori - const string& - the copied string
    **/
    string(const string& _copy_ori) noexcept : vector(_copy_ori) { }

    /**
     * Destructor of string
    **/
    ~string() noexcept = default;

    /**
     * Standard assignment operator
     * Pass-call function
     * @return returns: string& - lvalue of assignment
     * @param const string& - the right value of assignment  
    **/
    string& operator=(const string&) noexcept = default;

    /**
     * Move assignment operator
     * Pass-call function
     * @return returns: string& - lvalue of assignment
     * @param string&& - the rvalue of assignment
    **/
    string& operator=(string&&) noexcept = default;

    /**
     * Gets the occupied size of string
     * Pass-call function
     * @return returns: unsigned int - occupied size of string
     * 
    **/
    size_type length() const { return vector::size(); }

    /**
     * Add a character to the end of the string
     * Pass-call function
     * @return returns: string& - *this
     * @param _c - const char & - the apped char
    **/
    string& append(const char &_c) { 
        vector::push_back(_c);
        return (*this);
    }

    /**
     * Add a string to the end of the string
     * @return returns: string& - *this
     * @param _c - const string & - the apped string
    **/
    string& append(const string &_c) { 
        while (this->size() + _c.size() > this->capacity()) 
            this->__enlarge();
        AMI_std::uninitialized_copy(_c.__map_begin, _c.__map_end, this->end());
        this->__map_end += _c.size();
        return (*this);
    }

    /**
     * Return a C-type string
     * @return returns: char* - the c type "string"
     * 
    **/
    char* c_str() const { return vector::__map_begin; }

    /**
     * Return a sub string of this string
     * @return returns: string - the sub stirng
     * @param _begin    - iterator - the begin of the sub string
     * @param _end      - iterator - the end of the sub stirng
    **/
    string substr(iterator _begin, iterator _end) { return string(_begin, _end); }

    /**
     * Return a sub string of this string
     * @return returns: string - the sub stirng
     * @param _begin    - uint   - the begin location of the sub string
     * @param _end      - uint   - the end location of the sub stirng
    **/
    string substr(size_type _begin, size_type _end) { return substr(_begin + vector::begin(), _end + vector::begin()); }

    /**
     * Return if the two stirngs are equel
     * @return returns: bool - if the two stirngs are equel
     * @param _str      - const string & - the compared string
    **/
    bool compare(const string &_str) {
        if (this->length() != _str.length()) return false;
        for (size_type i = 0; i < this->length(); i++) {
            if (this->at(i) != *(_str.__map_begin + i)) return false;
        }
        return true;
    }

    /**
     * Return if the two stirngs are equel
     * Pass-call function
     * @return returns: bool - if the two stirngs are equel
     * @param other_str      - const string & - the compared string
    **/
    bool operator==(const string &other_str) {
        return compare(other_str);
    }

    /**
     * Add a string to a copy of this string
     * @return returns: string
     * @param _c - const string & - the apped string
    **/
    string operator+(const string &_c) const { //加法运算符绝对不返回引用
        string temp = *this;
        temp += _c;
        return temp;
    }

    /**
     * Add a string to the end of the string
     * @return returns: string& - *this
     * @param _c - const string & - the apped string
    **/
    string& operator+=(const string &_c) {
        return (append(_c));
    }

    /**
     * Set all of the upper alpha to lower
     * @return returns: string& - *this
     * 
    **/
    string& to_lower() {
        for (auto &c : *this) {
            if (isUpperAlpha(c)) c = c + 'a' - 'A';
        }
        return (*this);
    }

    /**
     * Set all of the lower alpha to upper
     * @return returns: string& - *this
     * 
    **/
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