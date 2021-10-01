#include <errno.h>
#include <stddef.h>
#include <unistd.h>

/* Remove the link named NAME.  */
int
__unlink (const char * name)  {
  if (name == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }
  /* since everything is okay, forward to lind server. */
  int return_code = __nacl_irt_unlink(name);

  if (return_code < 0) {
    __set_errno ( -1 * return_code);
    return -1;
  } else {
    return return_code;
  }
}

weak_alias (__unlink, unlink)
