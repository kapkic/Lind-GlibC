#include <errno.h>
#include <unistd.h>

#include <irt_syscalls.h>

int __chdir(const char* pathname)
{
  int result = __nacl_irt_chdir(pathname);
  if (result != 0) {
    errno = result;
  }
  return result;
}

weak_alias (__chdir, chdir)
