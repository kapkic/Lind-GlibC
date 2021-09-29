#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <irt_syscalls.h>

int __gethostname(char *name, size_t len)
{
  return __nacl_irt_gethostname(name, len);
}

weak_alias (__gethostname, gethostname)
