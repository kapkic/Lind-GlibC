#include <errno.h>
#include <unistd.h>

int
__getpid ()
{
  int pid;
  int error = __nacl_irt_getpid(&pid);
  if (error != 0) {
    errno = error;
    return -1;
  }
  return pid;
}

libc_hidden_def (__getpid)
stub_warning (getpid)
weak_alias (__getpid, getpid)
libc_hidden_weak (getpid)
