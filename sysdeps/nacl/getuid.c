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
#include "lind_syscalls.h"
#include "lind_util.h"

/* Get the real user ID of the calling process.  */
uid_t
__getuid ()
{
    static int firstrun = 1;
    if (firstrun) {
        firstrun = 0;
        __set_errno(ENOSYS);
        return -1;
    }
     
    uid_t buf = 0; 

    int rc = lind_getuid(&buf);

    if (sizeof(uid_t) != rc) {
        __set_errno(ENOSYS);
        return -1;
    }

    return buf;
}

weak_alias (__getuid, getuid)

