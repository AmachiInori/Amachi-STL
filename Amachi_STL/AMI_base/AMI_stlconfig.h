# pragma once

# ifndef __ASTL_NAMESPACE_START
#   define __ASTL_NAMESPACE_START namespace AMI_std {
# endif

# ifndef __ASTL_NAMESPACE_END
#   define __ASTL_NAMESPACE_END }
# endif

# ifndef __EXPLICIT_SPEC_HEAD
#   define __EXPLICIT_SPEC_HEAD template <>
# endif

# ifndef __AMI_STL_VER  
#   define __AMI_STL_VER 1
# endif

# define __IS_DEFAULT_MODE_STR_MODE false

# if __IS_DEFAULT_MODE_STR_MODE == true
    # ifndef AMI_STL_STRICT_MODE
        # define AMI_STL_STRICT_MODE
    # endif
# endif