#include <errno.h>
#include <unistd.h>
#include <stddef.h>
#include <sysdep.h>

/*
 * Create a one-way communication channel (__pipe).  If successful,
 * two file descriptors are stored in PIPEDES; bytes written on
 * PIPEDES[1] can be read from PIPEDES[0].  Apply FLAGS to the new
 * file descriptors.  Returns 0 if successful, -1 if not.
 */
int
__pipe2 (int pipedes[static 2], int flags)
{
  int ret;

  if (!pipedes) {
    __set_errno (EINVAL);
    return -1;
  }

  /* pipe2() with `flags == 0` is equivalent to pipe() */
  if (!flags) {
    ret = __nacl_irt_pipe(pipedes);
  } else {
    ret = __nacl_irt_pipe2(pipedes, flags);
  }

  if (ret) {
    __set_errno (-ret);
    return -1;
  }

  return 0;
}
libc_hidden_def (__pipe2)
weak_alias (__pipe2, pipe2)
