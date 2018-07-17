#include <errno.h>
#include <fcntl.h>
#include <sysdep.h>
#include <unistd.h>

/*
 * Duplicate oldfd to newfd, closing newfd and making it refer to
 * the same open file description as oldfd and setting flags. On
 * error, set errno and return -1.
 */
int __dup3(int oldfd, int newfd, int flags)
{
        int ret = __nacl_irt_dup3(oldfd, newfd, flags);
        if (ret < 0) {
                __set_errno (-ret);
                return -1;
        }
        return ret;
}
libc_hidden_def (__dup3)
weak_alias (__dup3, dup3)
