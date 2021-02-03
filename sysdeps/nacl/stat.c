#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <kernel_stat.h>
#include <nacl_stat.h>
#include <irt_syscalls.h>

void __nacl_abi_stat_to_stat (struct nacl_abi_stat *nacl_st,
                                struct stat *st)
{
  st->st_dev = nacl_st->nacl_abi_st_dev;
  st->st_mode = nacl_st->nacl_abi_st_mode;
  st->st_nlink = nacl_st->nacl_abi_st_nlink;
  st->st_uid = nacl_st->nacl_abi_st_uid;
  st->st_gid = nacl_st->nacl_abi_st_gid;
  st->st_rdev = nacl_st->nacl_abi_st_rdev;
  st->st_size = nacl_st->nacl_abi_st_size;
  st->st_blksize = nacl_st->nacl_abi_st_blksize;
  st->st_blocks = nacl_st->nacl_abi_st_blocks;
  st->st_atim.tv_sec = nacl_st->nacl_abi_st_atime;
  st->st_atim.tv_nsec = 0;
  st->st_mtim.tv_sec = nacl_st->nacl_abi_st_mtime;
  st->st_mtim.tv_nsec = 0;
  st->st_ctim.tv_sec = nacl_st->nacl_abi_st_ctime;
  st->st_ctim.tv_nsec = 0;
  st->st_ino = nacl_st->nacl_abi_st_ino;
}

int __stat(const char* pathname, struct stat* statbuf)
{
  if (statbuf == NULL) {
    errno = EFAULT;
    return -1;
  }

  struct nacl_abi_stat nacl_buf;
  int result = __nacl_irt_stat(pathname, &nacl_buf);
  if (result != 0) {
    errno = result;
    return -1;
  }
  __nacl_abi_stat_to_stat (&nacl_buf, statbuf);
  return 0;
}

weak_alias(__stat, stat)
