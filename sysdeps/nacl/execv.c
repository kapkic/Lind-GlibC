#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

/* Execute `path` with arguments `argv` and environment from `environ'.  */
int
__libc_execv (const char *path, char *const argv[])
{
  int i;
  int ret;
  char argv_send[100] = "";
  char envp_send[100] = "";
  char const *argv_ptr;
  char const *envp_ptr;
  char **envp = __environ;

  if (!path || !argv || !envp) {
    __set_errno (EINVAL);
    return -1;
  }

  i = 0;
  for (;;) {
    if (!argv[i]) {
      strcat(argv_send, "\0");
      break;
    }
    strcat(argv_send, argv[i]);
    strcat(argv_send, " ");
    i++;
  }

  i = 0;
  for (;;) {
    if (!envp[i]) {
      strcat(envp_send, "\0");
      break;
    }
    strcat(envp_send, envp[i]);
    strcat(envp_send, " ");
    i++;
  }

  argv_ptr = argv_send;
  envp_ptr = envp_send;

  ret = __nacl_irt_execve(path, argv_ptr, envp_ptr);

  /* execve should not return.  */
  __set_errno (-ret);
  return -1;
}

weak_alias (__libc_execv, __execv)
weak_alias (__libc_execv, execv)
