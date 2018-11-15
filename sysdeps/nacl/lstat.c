
#include <errno.h>
#include <irt_syscalls.h>

#undef lstat
#undef __lstat
int __lstat (__const char *path, struct stat *buf)
{
  if (buf == NULL || path == NULL)
    {
      errno = EFAULT;
      return -1;
    }
  struct nacl_abi_stat st;
  int result = __nacl_irt_lstat (path, &st);

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  __nacl_abi_stat_to_stat (&st, buf);
  return 0;
}
libc_hidden_proto (__lstat)
weak_alias (__lstat, lstat)
