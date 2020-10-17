# pragma once
# include <limits.h>
# include "AMI_stlconfig.h"
# ifndef INT_MAX
#   define INT_MAX 0xffff
# endif
# ifndef UINT_MAX
#   define UINT_MAX 0xffffffff
# endif

typedef unsigned int _AMI_size_t;
typedef signed long int _AMI_ptrdiff_t;