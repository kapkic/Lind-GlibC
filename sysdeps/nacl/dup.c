#include <errno.h>
#include <fcntl.h>
#include <sysdep.h>
#include <unistd.h>

/*
 * Duplicate oldfd and return newfd which refers to the same open
 * file description as oldfd. On error, set errno and return -1.
 */
int __dup(int oldfd)
{
    int ret = __nacl_irt_dup(oldfd);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}
libc_hidden_def (__dup)
weak_alias (__dup, dup)
