#ifndef _LIND_SYSCALLS_H_
#define _LIND_SYSCALLS_H_




#include <sys/types.h>
#include <nacl_stat.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/epoll.h>
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
#define LIND_safe_net_epoll_create      56
#define LIND_safe_net_epoll_ctl         57
#define LIND_safe_net_epoll_wait        58

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

#define SET_ERR_AND_RETURN(x) \
    do { \
        int result = (x); \
        if (result < 0) { \
            __set_errno(-result); \
            return -1; \
        } \
        return result; \
    } while (0)




/* int lind_open_rpc (const char * filename, int flags, int mode); */
/* int lind_read_rpc(int handle, int size, void * where_to); */
/* int lind_lseek_rpc(int fd, off_t offset, int whence, off_t* ret); */
/* int lind_fxstat_rpc(int fd, int vers, struct stat *buf); */
/* int lind_fstatfs_rpc (int fd, struct statfs *buf); */
/* int lind_close_rpc(int fd); */
/* ssize_t lind_write_rpc(int desc, void const *buf, size_t count); */
//int lind_ioctl_rpc (int fd, unsigned long int request, ...);
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
//int lind_comp_rpc(int request, int nbytes, void *buf);

/* int lind_dup_rpc(int oldfd); */
/* int lind_dup2_rpc(int oldfd, int newfd); */
//int lind_fcntl_rpc (int fd, int cmd, long set_op);
/* int lind_statfs_rpc (const char * path, struct statfs *buf); */

int lind_access (int version, const char *file);
int lind_unlink (const char *name);
int lind_link (const char *from, const char *to);
int lind_chdir (const char *name);
int lind_mkdir (int mode, const char *path);
int lind_rmdir (const char *path);
int lind_xstat (int version, const char *path, struct stat *buf);
int lind_open (int flags, int mode, const char *path);
int lind_close (int fd);
int lind_read (int fd, int size, void *buf);
int lind_write (int fd, size_t count, const void *buf);
int lind_lseek (off_t offset, int fd, int whence, off_t * ret);
int lind_fxstat (int fd, int version, struct stat *buf);
int lind_fstatfs (int fd, struct statfs *buf);
int lind_statfs (const char *path, struct statfs *buf);
int lind_noop (void);
int lind_getpid (pid_t * buf);
int lind_dup (int oldfd);
int lind_dup2 (int oldfd, int newfd);
int lind_getdents (int fd, size_t nbytes, char *buf);
int lind_fcntl_get (int fd, int cmd);
int lind_fcntl_set (int fd, int cmd, long set_op);
int lind_socket (int domain, int type, int protocol);
int lind_bind (int sockfd, socklen_t addrlen, const struct sockaddr *addr);
int lind_send (int sockfd, size_t len, int flags, const void *buf);
int lind_recv (int sockfd, size_t len, int flags, void *buf);
int lind_connect (int sockfd, socklen_t addrlen, const struct sockaddr *src_addr);
int lind_listen (int sockfd, int backlog);
int lind_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
int lind_accept (int sockfd, int flags, struct sockaddr *addr, socklen_t *addrlen);
int lind_getsockname (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out);
int lind_getpeername (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out);
int lind_setsockopt (int sockfd, int level, int optname, socklen_t optlen, const void *optval);
int lind_getsockopt (int sockfd, int level, int optname, socklen_t optlen, void *optval);
int lind_shutdown (int sockfd, int how);
int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout, struct select_results *result);
int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs);
int lind_recvfrom (int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t * addrlen_out, void *buf, struct sockaddr *src_addr);
int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out);
int lind_socketpair (int domain, int type, int protocol, int *fds);
int lind_getuid (uid_t * buf);
int lind_geteuid (uid_t * buf);
int lind_getgid (gid_t * buf);
int lind_getegid (gid_t * buf);
int lind_flock (int fd, int operation);
int lind_strace (char* str);
int lind_epoll_create (int size);
int lind_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event);
int lind_epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);

#endif /* _LIND_SYSCALLS_H_ */

