#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <irt_syscalls.h>
#include "lind_util.h"

/* Test for access to FILE.  */
int
__access (const char* file, int type)
{
  if (file == NULL || (type & ~(R_OK|W_OK|X_OK|F_OK)) != 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  /* Since everything is okay, forward to lind server. */
  int return_code = __nacl_irt_access (file, type);

  if (return_code < 0) {
    __set_errno (-return_code);
    return -1;
  }
  return return_code;
}

weak_alias (__access, access)
