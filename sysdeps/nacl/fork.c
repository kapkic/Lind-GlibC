#include <errno.h>
#include <unistd.h>

unsigned long int *__fork_generation_pointer;

/* Clone the calling process, creating an exact copy.
   Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
int
__fork ()
{
   int pid;
   pid = __nacl_irt_fork();
   return pid;
}

libc_hidden_def (__fork)
weak_alias (__fork, fork)
