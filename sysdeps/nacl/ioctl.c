#include <errno.h>
#include <stdarg.h>
#include <sys/ioctl.h>

#include "lind_syscalls.h"
#include "lind_util.h"

int
__ioctl (int fd, unsigned long int request, ...) {
    
    int result;
  
    if (fd < 0) {
      __set_errno (EBADF);
      return -1;
    }

    int result = -1;
    if (request == FIONBIO) {
      /* This command has a single long arg */
      va_list ap;
      va_start (ap, request);
      void *arg = va_arg (ap, void *);
      
      result = lind_ioctl(fd, request, arg);

    } else {
      /*  right now repy does not support any other commands */
      __set_errno (ENOSYS);
      return -1;
    }
    
    return result;
    
}

libc_hidden_def (__ioctl)
weak_alias (__ioctl, ioctl)
strong_alias (__ioctl, __libc_ioctl)
strong_alias (__ioctl, __ioctl_nocancel)
