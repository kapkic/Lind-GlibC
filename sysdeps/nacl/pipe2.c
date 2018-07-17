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
  if (!pipedes) {
    __set_errno (EINVAL);
    return -1;
  }
  __set_errno (ENOSYS);
  return -1;
}
libc_hidden_def (__pipe2)
weak_alias (__pipe2, pipe2)
stub_warning (pipe2)
#include <stub-tag.h>
