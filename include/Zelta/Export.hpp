#ifndef ZELTALIB_EXPORT
#define ZELTALIB_EXPORT

#ifdef _WIN32
#define EXPORT __declspec(dllexport) 
#else
#define EXPORT
#endif

#endif
