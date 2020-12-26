# pragma once
# include <limits.h>
# include "AMI_stlconfig.h"

# ifdef AMI_STRICT_MODE_ON
#   ifndef AMI_STL_STRICT_MODE
#       pragma message("Amachi STL: strict mode on")
#       define AMI_STL_STRICT_MODE
#   endif
# endif

# ifdef AMI_MEM_SAVING_MODE_ON
#   ifndef AMI_STL_MEM_SAVING
#       pragma message("Amachi STL: memory-saving mode on")
#       define AMI_STL_MEM_SAVING
#   endif
# endif

# if __IS_DEFAULT_MODE_STR_MODE == true
#   ifndef AMI_STL_STRICT_MODE
#       define AMI_STL_STRICT_MODE
#   endif
# endif

# ifndef __THROW_OUT_OF_BOUNDS
#   define __THROW_OUT_OF_BOUNDS throw OUT_OF_BOUND()
# endif

# ifndef __THROW_BAD_ALLOC
#   define __THROW_BAD_ALLOC throw BAD_ALLOC()
# endif

# ifndef __EXPLICIT_SPEC_HEAD
#   define __EXPLICIT_SPEC_HEAD template <>
# endif

typedef unsigned int _AMI_size_t;
typedef signed long int _AMI_ptrdiff_t;