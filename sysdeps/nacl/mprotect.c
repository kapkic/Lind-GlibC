
#include <errno.h>
#include <sys/mman.h>

#include <irt_syscalls.h>


int __mprotect (void *addr, size_t len, int prot)
{
  int result = __nacl_irt_mprotect (addr, len, prot);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return 0;
}
weak_alias (__mprotect, mprotect)
