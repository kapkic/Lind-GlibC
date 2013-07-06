#ifndef LIND_STRACE_H
#define LIND_STRACE_H


#include <string.h>
#include <lind_syscalls.h>

ssize_t __write(int desc, void const *buf, size_t count);

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define USE_TRACE

#ifdef USE_TRACE
  #define nacl_strace(x) lind_strace(x)
  #define dbp(x)   {__write(2, __FILE__ ":" TOSTRING(__LINE__) ": " x "\n", strlen( __FILE__ ":" TOSTRING(__LINE__) ": "  x "\n")); }
  #define dbg_print(x)   { const char * dbg_message = (x);__write(2, dbg_message, strlen(dbg_message)); }
#else
  #define nacl_strace(x) 
  #define dbp(x)    {;} 
  #define dbg_print(x)    {;} 
#endif

#define print_error(x) lind_strace(x)

#endif // LIND_STRACE_H
