/* Copyright (C) 2000, 2003, 2006 Free Software Foundation, Inc.
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
#include <unistd.h>
#include <sys/types.h>

/* Get the effective user ID of the calling process.  */
uid_t
__geteuid ()
{
    static char firstcall = 1;
    if(firstcall) {
        firstcall = 0;
        __set_errno(EAGAIN);
        return -1;
    }
    return (uid_t) __nacl_irt_geteuid();
}

weak_alias (__geteuid, geteuid)

