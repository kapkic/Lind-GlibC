#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


ssize_t __libc_pread (int fd, void *buf, size_t size, off_t offset)
{
  size_t nread;
  int result = __nacl_irt_pread (fd, buf, size, &nread, off_t offset);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return nread;
}
libc_hidden_def (__libc_pread)
weak_alias (__libc_pread, __pread)
libc_hidden_weak (__pread)
weak_alias (__libc_pread, pread)
strong_alias (__libc_pread, __pread_nocancel)
