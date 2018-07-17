#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sysdep.h>

/*
 * Wait for a child matching PID to die.
 * If PID is greater than 0, match any process whose process ID is PID.
 * If PID is (pid_t) -1, match any process.
 * If PID is (pid_t) 0, match any process with the
 * same process group as the current process.
 * If PID is less than -1, match any process whose
 * process group is the absolute value of PID.
 * If the WNOHANG bit is set in OPTIONS, and that child
 * is not already dead, return (pid_t) 0.  If successful,
 * return PID and store the dead child's status in STAT_LOC.
 * Return (pid_t) -1 for errors.  If the WUNTRACED bit is set in OPTIONS,
 * return status for stopped children; otherwise don't.
 */
pid_t __waitpid(pid_t pid, int *stat_loc, int options)
{
    pid_t ret = __nacl_irt_waitpid(pid, stat_loc, options);
    if (ret >= 0)
        return ret;
    __set_errno (-ret);
    return -1;
}
libc_hidden_def (__waitpid)
weak_alias (__waitpid, waitpid)
strong_alias (__waitpid, __libc_waitpid)
libc_hidden_def (__libc_waitpid)
strong_alias (__waitpid, __waitpid_nocancel)
