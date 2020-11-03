# pragma once
# include "AMI_stlconfig.h"

__ASTL_NAMESPACE_START

class __false {};
class __true {};

typedef __false false_type;
typedef __true true_type;

template <class __type>
class __type_traits {
public:
    typedef __true do_not_redefine_AMI_std_type_traits;

    typedef __false has_trival_default_ctor;
    typedef __false has_trival_default_dtor;
    typedef __false has_trival_default_cpyctor;
    typedef __false has_trival_default_assign;
    typedef __false is_POD_type;
};

/****************************************/

__EXPLICIT_SPEC_HEAD
class __type_traits<bool> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<char> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<signed char> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<unsigned char> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<short> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<unsigned short> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<int> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<unsigned int> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<long> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<unsigned long> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<float> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<double> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__EXPLICIT_SPEC_HEAD
class __type_traits<long double> {
public:
    typedef __true has_trival_default_ctor;
    typedef __true has_trival_default_dtor;
    typedef __true has_trival_default_cpyctor;
    typedef __true has_trival_default_assign;
    typedef __true is_POD_type;
};

__ASTL_NAMESPACE_END 