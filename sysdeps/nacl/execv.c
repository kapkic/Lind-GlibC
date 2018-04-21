#include <errno.h>
#include <unistd.h>
#include <stub-tag.h>

/* Execute PATH with arguments ARGV and environment from `environ'.  */
int
__libc_execv (const char *path, char *const argv[])
{
  int retval;
  retval = 500;
  __nacl_irt_execv();
  return retval;
}

weak_alias (__libc_execv, __execv)
weak_alias (__libc_execv, execv)
stub_warning (execv)
