#include <unistd.h>
#include <errno.h>
#include <nacl_syscalls.h>
#include "lind_util.h"
#include "lind_strace.h"
#include "lind_syscalls.h"

pid_t __getpid ()
{
  pid_t lind_pid = -1;

  int rc = lind_getpid(&lind_pid);

  if (rc != 0) {
    __set_errno(rc);
    return -1;
  }
  return lind_pid;
}
libc_hidden_def (__getpid)
weak_alias (__getpid, getpid)
libc_hidden_def (getpid)
