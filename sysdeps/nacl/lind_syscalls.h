#ifndef _LIND_SYSCALLS_H_
#define _LIND_SYSCALLS_H_




#include <sys/types.h>
/* #include <kernel_stat.h> */
#include <nacl_stat.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <unistd.h>

#define LIND_debug_noop                 1
#define LIND_safe_fs_access             2
#define LIND_debug_trace                3
#define LIND_safe_fs_unlink             4
#define LIND_safe_fs_link               5
#define LIND_safe_fs_chdir              6
#define LIND_safe_fs_mkdir              7
#define LIND_safe_fs_rmdir              8
#define LIND_safe_fs_xstat              9
#define LIND_safe_fs_open               10
#define LIND_safe_fs_close              11
#define LIND_safe_fs_read               12
#define LIND_safe_fs_write              13
#define LIND_safe_fs_lseek              14
#define LIND_fs_ioctl                   15
#define LIND_safe_fs_fxstat             17
#define LIND_safe_fs_fstatfs            19
#define LIND_safe_fs_getdents           23
#define LIND_safe_fs_dup                24
#define LIND_safe_fs_dup2               25
#define LIND_safe_fs_statfs             26
#define LIND_safe_fs_fcntl              28

#define LIND_sys_getpid                 31

#define LIND_safe_net_socket            32
#define LIND_safe_net_bind              33
#define LIND_safe_net_send              34
#define LIND_safe_net_sendto            35
#define LIND_safe_net_recv              36
#define LIND_safe_net_recvfrom          37
#define LIND_safe_net_connect           38
#define LIND_safe_net_listen            39
#define LIND_safe_net_accept            40
#define LIND_safe_net_getpeername       41
#define LIND_safe_net_getsockname       42
#define LIND_safe_net_getsockopt        43
#define LIND_safe_net_setsockopt        44
#define LIND_safe_net_shutdown          45
#define LIND_safe_net_select            46
#define LIND_safe_net_getifaddrs        47
#define LIND_safe_net_poll              48
#define LIND_safe_net_socketpair        49
#define LIND_safe_sys_getuid            50
#define LIND_safe_sys_geteuid           51
#define LIND_safe_sys_getgid            52
#define LIND_safe_sys_getegid           53
#define LIND_safe_fs_flock              54
#define LIND_safe_fs_rename             55

#define LIND_comp_cia                   105
#define LIND_comp_call                  106
#define LIND_comp_accept                107
#define LIND_comp_recv                  108


struct select_results {
    struct timeval used_t;
    fd_set r;
    fd_set w;
    fd_set e;
};




/* int lind_open_rpc (const char * filename, int flags, int mode); */
/* int lind_read_rpc(int handle, int size, void * where_to); */
/* int lind_lseek_rpc(int fd, off_t offset, int whence, off_t* ret); */
/* int lind_fxstat_rpc(int fd, int vers, struct stat *buf); */
/* int lind_fstatfs_rpc (int fd, struct statfs *buf); */
/* int lind_close_rpc(int fd); */
/* ssize_t lind_write_rpc(int desc, void const *buf, size_t count); */
int lind_ioctl_rpc (int fd, unsigned long int request, ...);
/* int lind_access_rpc(const char * file, int type); */
/* int lind_unlink_rpc(const char * name); */
/* int lind_link_rpc(const char * from, const char * to); */
/* int lind_chdir_rpc(const char * name); */
/* int lind_mkdir_rpc (const char* path, mode_t mode); */
/* int lind_rmdir_rpc (const char* path); */
/* int lind_noop_rpc (void); */
/* int lind_getpid_rpc(pid_t * pid_buf ); */
/* int lind_xstat_rpc (int version, const char *path, struct stat *buf); */
/* ssize_t lind_getdents_rpc(int fd, char *buf, size_t nbytes); */
int lind_comp_rpc(int request, int nbytes, void *buf);

/* int lind_dup_rpc(int oldfd); */
/* int lind_dup2_rpc(int oldfd, int newfd); */
int lind_fcntl_rpc (int fd, int cmd, long set_op);
/* int lind_statfs_rpc (const char * path, struct statfs *buf); */


#include "lind_rpc_gen.h"

#endif /* _LIND_SYSCALLS_H_ */

