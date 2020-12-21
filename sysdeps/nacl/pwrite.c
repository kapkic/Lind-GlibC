#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

#include <irt_syscalls.h>


ssize_t __pwrite(int desc, void const *buf, size_t count, off_t offset)
{
  size_t nwrite;
  int result = __nacl_irt_pwrite (desc, buf, count, &nwrite, off_t offset);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return nwrite;
}

weak_alias (__pwrite, pwrite)
