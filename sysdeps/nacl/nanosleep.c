#include <errno.h>
#include <time.h>

#include <irt_syscalls.h>

#include <nacl_syscalls.h>
#include "strace.h"

int __nanosleep (const struct timespec *req, struct timespec *rem)
{
  nacl_strace("nanosleep");
  int result = __nacl_irt_nanosleep (req, rem);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return -result;
}
libc_hidden_def (__nanosleep)
weak_alias (__nanosleep, nanosleep)
