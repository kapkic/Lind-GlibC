#include <errno.h>
#include <stddef.h>
#include <unistd.h>

int
__poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
  int result = __nacl_irt_poll (fds, nfds, timeout);
  if (result < 0) {
     __set_errno (-result);
     return -1;
  } else {
      return result;
  }
}

libc_hidden_def (__poll)
weak_alias (__poll, poll)