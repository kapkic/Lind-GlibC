#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sysdep.h>

/*
 * Duplicate oldfd and return newfd which refers to the same open
 * file description as oldfd. On error, set errno and return -1.
 */
int __dup(int oldfd)
{
    int newfd = -1;
    int ret = __nacl_irt_dup(oldfd, &newfd);
    if (newfd < 0)
        errno = ret;
    return newfd;
}
libc_hidden_def (__dup)
weak_alias (__dup, dup)
