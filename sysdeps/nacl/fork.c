#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

unsigned long int *__fork_generation_pointer;

/*
 * Clone the calling process, creating an exact copy.
 * Return -1 for errors, 0 to the new process,
 * and the process ID of the new process to the old process.
 */
int __libc_fork(void)
{
   int pid = __nacl_irt_fork();
   if (!pid && __fork_generation_pointer)
      *__fork_generation_pointer += 4;
   return pid;
}
libc_hidden_def (__libc_fork)
weak_alias (__libc_fork, __fork)
libc_hidden_def (__fork)
weak_alias (__libc_fork, fork)
