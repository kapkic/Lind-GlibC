#include <errno.h>
#include <fcntl.h>
#include <irt.h>
#include <sysdep.h>
#include <unistd.h>

/*
 * returns the ppid of the calling process
 */
pid_t
__getppid (void)
{
  return __nacl_irt_getppid();
}

/* libc_hidden_def (__getppid) */
/* weak_alias (__getppid, __libc_getppid) */
weak_alias (__getppid, getppid)
