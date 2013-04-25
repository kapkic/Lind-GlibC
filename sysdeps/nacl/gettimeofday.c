
#include <errno.h>
#include <time.h>

#include <irt_syscalls.h>


/* Undo the #define in include/sys/time.h */
#undef __gettimeofday

int __gettimeofday (struct timeval *tv, struct timezone *tz)
{
  int result = __nacl_irt_gettod (tv);
  if (result != 0) {
    errno = result;
    return -1;
  }
  if (tz != NULL) {
    tz->tz_dsttime = 0;
    tz->tz_minuteswest = 0;
  }
  return -result;
}
INTDEF (__gettimeofday)
weak_alias (__gettimeofday, gettimeofday)
