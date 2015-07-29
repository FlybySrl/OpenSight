#ifndef CORE_EXPORT_H
#define CORE_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( core_LIBRARY_STATIC )
    #    define CORE_EXPORT
    #  elif defined( core_LIBRARY_SHARED )
    #    define CORE_EXPORT   __declspec(dllexport)
    #  else
    #    define CORE_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define CORE_EXPORT
#endif

#endif // CORE_EXPORT_H
