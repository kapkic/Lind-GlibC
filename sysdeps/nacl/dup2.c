#include <errno.h>
#include <fcntl.h>
#include <sysdep.h>
#include <unistd.h>

/*
 * Duplicate oldfd to newfd, closing newfd and making it refer to
 * the same open file description as oldfd. On error, set errno
 * and return -1.
 */
int __dup2(int oldfd, int newfd)
{
        int ret = __nacl_irt_dup2(oldfd, newfd);
        if (ret < 0) {
                __set_errno (-ret);
                return -1;
        }
        return ret;
}
libc_hidden_def (__dup2)
weak_alias (__dup2, dup2)
