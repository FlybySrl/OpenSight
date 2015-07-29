#ifndef CORE_APP_EXPORT_H
#define CORE_APP_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( core_app_LIBRARY_STATIC )
    #    define CORE_APP_EXPORT
    #  elif defined( core_app_LIBRARY_SHARED )
    #    define CORE_APP_EXPORT   __declspec(dllexport)
    #  else
    #    define CORE_APP_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define CORE_APP_EXPORT
#endif

#endif // CORE_APP_EXPORT_H
