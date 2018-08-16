#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

/* Execute `path` with arguments `argv` and environment from `environ'.  */
int
__libc_execv (char const *path, char *const *argv)
{
  int ret;

  if (!path || !argv) {
    __set_errno (EINVAL);
    return -1;
  }

  ret = __nacl_irt_execv(path, argv);

  /* execve should not return.  */
  __set_errno (-ret);
  return -1;
}

weak_alias (__libc_execv, __execv)
weak_alias (__libc_execv, execv)
