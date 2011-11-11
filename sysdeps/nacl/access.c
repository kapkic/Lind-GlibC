#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include "strace.h"
#include "nacl_util.h"
#include "lind_syscalls.h"

/* Test for access to FILE.  */
int
__access (const char* file, int type)
{
  if (file == NULL || (type & ~(R_OK|W_OK|X_OK|F_OK)) != 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  nacl_strace(concat("access ",file));

  /* since everything is okay, forward to lind server. */
  int return_code = lind_access_rpc(file, type);

  if (return_code < 0) {
    __set_errno ( -1 * return_code);
    return -1;
  } else {
    return return_code;
  }
}
stub_warning (access)

weak_alias (__access, access)
#include <stub-tag.h>
