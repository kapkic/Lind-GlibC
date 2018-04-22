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

#include <sys/wait.h>
#include <errno.h>
#include <sysdep.h>

/* Wait for a child to die.  When one does, put its status in *STAT_LOC
   and return its process ID.  For errors, return (pid_t) -1.  */
pid_t __wait(int *stat_loc)
{
	pid_t ret = __nacl_irt_waitpid(WAIT_ANY, stat_loc, 0);
	if (!ret)
		return 0;
	errno = ret;
	return (pid_t)-1;
}
libc_hidden_def (__wait)
weak_alias (__wait, wait)
strong_alias (__wait, __libc_wait)
libc_hidden_def (__libc_wait)
