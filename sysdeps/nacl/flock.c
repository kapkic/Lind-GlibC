/* Copyright (C) 1992, 1995, 1996, 1997 Free Software Foundation, Inc.
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
#include <sys/file.h>
#include <irt_syscalls.h>

/* Apply or remove an advisory lock, according to OPERATION,
   on the file FD refers to.  */
int
__flock (fd, operation)
     int fd;
     int operation;
{
 int result = __nacl_irt_flock(fd, operation);
 if (result < 0) {
    __set_errno (-result);
    return -1;
 }
 else{
 return result;
 }
}

weak_alias (__flock, flock)

