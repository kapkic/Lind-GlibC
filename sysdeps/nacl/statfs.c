/* statfs -- Return information about the filesystem on which FILE resides.
   Copyright (C) 1996, 1997, 2002 Free Software Foundation, Inc.
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
#include <sys/statfs.h>
#include <stddef.h>
#include <irt_syscalls.h>

/* Return information about the filesystem on which FILE resides.  */
int
__statfs (const char *file, struct statfs *buf)
{
  int result;
  result = __nacl_irt_statfs(file, buf);
  if (result < 0) {
    errno = -result;
    result = -1;
  }
  return result;

}
libc_hidden_def (__statfs)
weak_alias (__statfs, statfs)

