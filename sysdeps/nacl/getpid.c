#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * returns the pid of the calling process
 */
pid_t
__getpid (void)
{
  return __nacl_irt_getpid();
}

libc_hidden_def (__getpid)
weak_alias (__getpid, getpid)
libc_hidden_weak (getpid)
