/* Copyright (C) 2008 Free Software Foundation, Inc.
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
#include <fcntl.h>
#include <unistd.h>
#include <sysdep.h>

/*
 * Duplicate oldfd to newfd, closing newfd and making it refer to
 * the same open file description as oldfd and setting flags. On
 * error, set errno and return -1.
 */
int __dup3(int oldfd, int newfd, int flags)
{
	int ret = __nacl_irt_dup3(oldfd, newfd, flags);
	if (!ret)
		return newfd;
	errno = ret;
	return -1;
}
libc_hidden_def (__dup3)
weak_alias (__dup3, dup3)
