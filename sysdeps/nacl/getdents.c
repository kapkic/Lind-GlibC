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

#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include "lind_syscalls.h"
#include "strace.h"

/* CM: I think this file can be deleted? It is reaplaced by the nacl versions */

/* ssize_t */
/* __getdirentries (int fd, char *buf, size_t nbytes, off_t *basep) { */
/*   nacl_strace("getdents"); */
/*   /\* See comment above about this file not being used. *\/ */
/*   ssize_t result = lind_getdents_rpc(fd, buf, nbytes, basep); */
/*   return result; */

/* } */
/* weak_alias (__getdirentries, getdirentries) */
