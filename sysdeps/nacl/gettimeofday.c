
#include <errno.h>
#include <time.h>

#include <irt_syscalls.h>

#include <nacl_syscalls.h>
#include "strace.h"

/* Undo the #define in include/sys/time.h */
#undef __gettimeofday

int __gettimeofday (struct timeval *tv, struct timezone *tz)
{
  nacl_strace("gettimeofday");
  int result = __nacl_irt_gettod (tv);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return -result;
}
INTDEF (__gettimeofday)
weak_alias (__gettimeofday, gettimeofday)
