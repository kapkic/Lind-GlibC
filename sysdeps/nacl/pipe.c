#include <errno.h>
#include <unistd.h>
#include <stddef.h>

/* Create a one-way communication channel (__pipe).
   If successful, two file descriptors are stored in PIPEDES;
   bytes written on PIPEDES[1] can be read from PIPEDES[0].
   Returns 0 if successful, -1 if not.  */
int
__pipe (__pipedes)
     int __pipedes[2];
{
  if (__pipedes == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  // yiwen: nacl_irt_pipe was added to perform our IPP(in-process-pipe) function
  int error = __nacl_irt_pipe(__pipedes);
  if (error != 0) {
    errno = error;
    return -1;
  }

  return 0;
}
libc_hidden_def (__pipe)
stub_warning (pipe)

weak_alias (__pipe, pipe)
#include <stub-tag.h>
