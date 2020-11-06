# pragma once
# include "AMI_stlconfig.h"
# include "AMI_stddef.h"

__ASTL_NAMESPACE_START

class base_exception {
    unsigned int strlen(const char* _str) {
        int _i = 0;
        for (_i = 0; _str[_i] != '\0'; _i++);
        return _i;
    }
    char* _what;
public:
    base_exception(const char* _wrd) {
        unsigned int _wrdlen = strlen(_wrd);
        _what = new char [_wrdlen];
        for (unsigned int i = 0; i < _wrdlen; i++) {
            _what[i] = _wrd[i];
        }
    }
    virtual ~base_exception() { delete[] _what; }
    const char* what() const { return _what; }
};

class OUT_OF_BOUND : public base_exception {
public:
    OUT_OF_BOUND() : base_exception("access_out_of_bound") { }
};

class BAD_ALLOC : public base_exception {
public:
    BAD_ALLOC() : base_exception("BAD_ALLOC") { }
};

__ASTL_NAMESPACE_END