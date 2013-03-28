#include <errno.h>
#include <unistd.h>

#include <irt_syscalls.h>

#include <nacl_syscalls.h>
#include "strace.h"
#include "nacl_util.h"
#include "lind_syscalls.h"

int __close (int fd)
{
  int result;
  if (is_system_handle(fd)) {
    result = __nacl_irt_close (fd);
  } else {
    result = lind_close_rpc(fd);
  }
  if (result != 0) {
    if(is_system_handle(fd))
      errno = result;
    else
      errno = -result;
    return -1;
  }
  return -result;
}
libc_hidden_def (__close)
weak_alias (__close, close)
strong_alias (__close, __libc_close)
strong_alias (__close, __close_nocancel)
