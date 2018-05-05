#include <errno.h>
#include <unistd.h>

/*
 * returns the pid of the calling process
 */
int
__getpid (void)
{
  return __nacl_irt_getpid();
}

libc_hidden_def (__getpid)
weak_alias (__getpid, getpid)
strong_alias (__getpid, __libc_getpid)
libc_hidden_weak (getpid)
