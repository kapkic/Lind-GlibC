/* Copyright (C) 1991, 1995, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

/* Replace the current process, executing PATH with arguments ARGV and
   environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  */
int
__execve (path, argv, envp)
     const char *path;
     char *const argv[];
     char *const envp[];
{
  int retval = 0;
  char argv_send[100] = "";
  char envp_send[100] = ""; 
  const char *argv_ptr;
  const char *envp_ptr;

  if (path == NULL || argv == NULL || envp == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  int i;
  for (i = 0; ; i++) {
    if (argv[i] == NULL) {
      strcat(argv_send, "\0");
      break; 
    }
    else {
      strcat(argv_send, argv[i]);
      strcat(argv_send, " ");
    }
  }

  for (i = 0; ; i++) {
    if (envp[i] == NULL) {
      strcat(envp_send, "\0");
      break; 
    }
    else {
      strcat(envp_send, envp[i]);
      strcat(envp_send, " ");
    }
  }

  argv_ptr = argv_send;
  envp_ptr = envp_send;

  retval = __nacl_irt_execve(path, argv_ptr, envp_ptr);

  __set_errno (ENOSYS);
  return retval;
}
stub_warning (execve)

weak_alias (__execve, execve)
#include <stub-tag.h>
