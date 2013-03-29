#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>
#include "lind_rpc.h"
#include "lind_syscalls.h"
#include "lind_strace.h"
#include "lind_util.h"
#include "nacl_syscalls.h"
#include "component.h"
#include <nacl_stat.h>
#include <sys/statfs.h>
#include <sys/stat.h>
int lind_access_rpc(int version, const char * file);
int lind_unlink_rpc(const char * name);
int lind_link_rpc(const char * from, const char * to);
int lind_chdir_rpc(const char * name);
int lind_mkdir_rpc(int mode, const char * path);
int lind_rmdir_rpc(const char * path);
int lind_xstat_rpc(int version, const char * path, struct stat * buf);
int lind_open_rpc(int fd, int mode, const char * path);
int lind_close_rpc(int fd);
int lind_read_rpc(int fd, int size, void * buf);
int lind_write_rpc(int desc, size_t count, const void * buf);
int lind_lseek_rpc(off_t offset, int fd, int whence, off_t* ret);
int lind_fxstat_rpc(int fd, int version, struct stat * buf);
int lind_fstatfs_rpc(int fd, struct statfs * buf);
int lind_statfs_rpc(const char * path, struct statfs * buf);
int lind_noop_rpc(void);
int lind_getpid_rpc(pid_t * buf);
int lind_dup_rpc(int oldfd);
int lind_dup2_rpc(int oldfd, int newfd);
int lind_getdents_rpc(int fd, size_t nbytes, char * buf);
int lind_fcntl_get_rpc(int fd, int cmd);
int lind_fcntl_set_rpc(int fd, int cmd, long set_op);
int lind_socket_rpc(int domain, int type, int protocol);
int lind_bind_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * addr);
int lind_send_rpc(int sockfd, size_t len, int flags, const void * buf);
int lind_recv_rpc(int sockfd, size_t len, int flags, void * buf);
int lind_connect_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * src_addr);
int lind_listen_rpc(int sockfd, int backlog);
int lind_sendto_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in * dest_addr, const void * buf);
int lind_accept_rpc(int sockfd, socklen_t addrlen);
int lind_getpeername_rpc(int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t * addrlen_out);
int lind_setsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, const void * optval);
int lind_getsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, void * optval);
int lind_shutdown_rpc(int sockfd, int how);
int lind_select_rpc(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval * timeout, struct select_results * result);
int lind_getifaddrs_rpc(int ifaddrs_buf_siz, void * ifaddrs);
int lind_recvfrom_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t* addrlen_out, void * buf, struct sockaddr * src_addr);
int lind_poll_rpc(int nfds, int timeout, struct pollfd * fds_in, struct pollfd * fds_out);
int lind_socketpair_rpc(int domain, int type, int protocol, int * fds);
int lind_getuid_rpc(uid_t * buf);
int lind_geteuid_rpc(uid_t * buf);
int lind_getgid_rpc(gid_t * buf);
int lind_getegid_rpc(gid_t * buf);
int lind_flock_rpc(int fd, int operation);
#define SET_ERR_AND_RETURN(x)			\
int result = 1;					\
result = x;					\
 if (result < 0) {				\
 __set_errno(-result);				\
 return -1;					\
 }						\
 return result					

/* This file is auto-generated! do not edit it manually!*/

int lind_access_rpc(int version, const char * file);
int lind_unlink_rpc(const char * name);
int lind_link_rpc(const char * from, const char * to);
int lind_chdir_rpc(const char * name);
int lind_mkdir_rpc(int mode, const char * path);
int lind_rmdir_rpc(const char * path);
int lind_xstat_rpc(int version, const char * path, struct stat * buf);
int lind_open_rpc(int fd, int mode, const char * path);
int lind_close_rpc(int fd);
int lind_read_rpc(int fd, int size, void * buf);
int lind_write_rpc(int desc, size_t count, const void * buf);
int lind_lseek_rpc(off_t offset, int fd, int whence, off_t* ret);
int lind_fxstat_rpc(int fd, int version, struct stat * buf);
int lind_fstatfs_rpc(int fd, struct statfs * buf);
int lind_statfs_rpc(const char * path, struct statfs * buf);
int lind_noop_rpc(void);
int lind_getpid_rpc(pid_t * buf);
int lind_dup_rpc(int oldfd);
int lind_dup2_rpc(int oldfd, int newfd);
int lind_getdents_rpc(int fd, size_t nbytes, char * buf);
int lind_fcntl_get_rpc(int fd, int cmd);
int lind_fcntl_set_rpc(int fd, int cmd, long set_op);
int lind_socket_rpc(int domain, int type, int protocol);
int lind_bind_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * addr);
int lind_send_rpc(int sockfd, size_t len, int flags, const void * buf);
int lind_recv_rpc(int sockfd, size_t len, int flags, void * buf);
int lind_connect_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * src_addr);
int lind_listen_rpc(int sockfd, int backlog);
int lind_sendto_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in * dest_addr, const void * buf);
int lind_accept_rpc(int sockfd, socklen_t addrlen);
int lind_getpeername_rpc(int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t * addrlen_out);
int lind_setsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, const void * optval);
int lind_getsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, void * optval);
int lind_shutdown_rpc(int sockfd, int how);
int lind_select_rpc(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval * timeout, struct select_results * result);
int lind_getifaddrs_rpc(int ifaddrs_buf_siz, void * ifaddrs);
int lind_recvfrom_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t* addrlen_out, void * buf, struct sockaddr * src_addr);
int lind_poll_rpc(int nfds, int timeout, struct pollfd * fds_in, struct pollfd * fds_out);
int lind_socketpair_rpc(int domain, int type, int protocol, int * fds);
int lind_getuid_rpc(uid_t * buf);
int lind_geteuid_rpc(uid_t * buf);
int lind_getgid_rpc(gid_t * buf);
int lind_getegid_rpc(gid_t * buf);
int lind_flock_rpc(int fd, int operation);
