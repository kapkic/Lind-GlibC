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

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <errno.h>
#include <sysdep.h>

struct rusage;

/* Wait for a child to die.  When one does, put its status in *STAT_LOC
   and return its process ID.  For errors, return (pid_t) -1.  */
pid_t __libc_wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)
{
    /*
     * TODO: implement wait4() properly -jp
     */
    pid_t ret = __nacl_irt_wait4(pid, wstatus, options, rusage);
    if (ret < 0) {
      __set_errno (-ret);
      return -1;
    }
    return ret;
}
weak_alias (__libc_wait4, __wait4)
weak_alias (__libc_wait4, wait4)
