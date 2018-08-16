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
#include <sysdep.h>

/*
 * Replace the current process, executing `path` with arguments `argv` and
 * environment `envp`.  `argv` and `envp` are terminated by NULL pointers.
 */
int
__execve (char const *path, char *const *argv, char *const *envp)
{
  int ret;
  if (!path || !argv || !envp) {
    __set_errno (EINVAL);
    return -1;
  }
  ret = __nacl_irt_execve(path, argv, envp);

  /* execve should not return.  */
  __set_errno (-ret);
  return -1;
}

weak_alias (__execve, execve)
