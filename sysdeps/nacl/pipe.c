#include <errno.h>
#include <unistd.h>
#include <stddef.h>
#include <sysdep.h>

/*
 * Create a one-way communication channel (__pipe).
 * If successful, two file descriptors are stored in pipedes;
 * bytes written on pipedes[1] can be read from pipedes[0].
 * Returns 0 if successful or -1 if on ret.
 */
int
__pipe (int __pipedes[static 2])
{
  int ret;

  if (!__pipedes) {
    __set_errno (EINVAL);
    return -1;
  }

  ret = __nacl_irt_pipe(__pipedes);
  if (ret) {
    __set_errno (-ret);
    return -1;
  }

  return 0;
}

libc_hidden_def (__pipe)
weak_alias (__pipe, pipe)
