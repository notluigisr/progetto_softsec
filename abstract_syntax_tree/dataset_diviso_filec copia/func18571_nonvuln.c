    
    inline const char *stros() {
#if defined(linux) || defined(__linux) || defined(__linux__)
      static const char *const str = "STR";
#elif defined(sun) || defined(__sun)
      static const char *const str = "STR";
#elif defined(BSD) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined (__DragonFly__)
      static const char *const str = "STR";
#elif defined(sgi) || defined(__sgi)
      static const char *const str = "STR";
#elif defined(__MACOSX__) || defined(__APPLE__)
      static const char *const str = "STR";
#elif defined(unix) || defined(__unix) || defined(__unix__)
      static const char *const str = "STR";
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) || \
  defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
      static const char *const str = "STR";
#else
      const char
        *const _str1 = std::getenv("STR"),
        *const _str2 = _str1?_str1:std::getenv("STR"),
        *const str = _str2?_str2:"STR";
#endif
      return str;