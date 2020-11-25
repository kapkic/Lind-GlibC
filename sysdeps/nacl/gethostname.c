#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <irt_syscalls.h>

int __gethostname(char *name, size_t len)
{
  return __nacl_irt_gethostname(name, len);
}

libc_hidden_def (__getpid)
weak_alias (__getpid, getpid)
libc_hidden_weak (getpid)
