#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


ssize_t __pread (int fd, void *buf, size_t size, off_t offset)
{
  size_t nread;
  int result = __nacl_irt_pread (fd, buf, size, &nread, offset);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return nread;
}

weak_alias (__pread, pread)
weak_alias (__pread, __libc_pread)
