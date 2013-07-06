#include <errno.h>
#include <sys/statfs.h>
#include <stddef.h>

#include "lind_util.h"
#include "lind_strace.h"
#include "lind_syscalls.h"

/* Return information about the filesystem on which FD resides.  */
int
__fstatfs (int fd, struct statfs *buf)
{
 
  if (is_system_handle(fd)) {

       __set_errno (ENOSYS);
       return -1;
  }
  
  int lind_rc = lind_fstatfs(fd, buf);
  
  if (lind_rc < 0) {
    __set_errno (-lind_rc);
     return -1;
  }
   __set_errno (ENOSYS);
   return 0;
}

weak_alias (__fstatfs, fstatfs)
