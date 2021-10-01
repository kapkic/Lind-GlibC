#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <irt_syscalls.h>


/* Make a link to FROM called TO.  */
int
__link (const char * from, const char * to) {

  if (from == NULL || to == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }
  /* since everything is okay, forward to lind server. */
  int return_code = __nacl_irt_link(from, to);

  if (return_code < 0) {
    __set_errno ( -1 * return_code);
    return -1;
  } else {
    return return_code;
  }

}

weak_alias (__link, link)
