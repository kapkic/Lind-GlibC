#include <errno.h>
#include <stddef.h>
#include <unistd.h>

int
__select (int nfds, fd_set *restrict readfds,
		     fd_set *__restrict writefds,
		     fd_set *__restrict exceptfds,
		     struct timeval *__restrict timeout)
{
  int result = __nacl_irt_select (nfds, readfds, writefds, exceptfds, timeout);
  if (result < 0) {
     __set_errno (-result);
     return -1;
  } else {
      return result;
  }
}

libc_hidden_def (__select)
weak_alias (__select, select)
