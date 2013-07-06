#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <nacl_stat.h>
#include <nacl_syscalls.h>
#define stat nacl_abi_stat
#include <irt.h>
#undef stat
#include <irt_syscalls.h>
#ifdef IS_IN_rtld
#include <ldsodefs.h>
#endif
#include "trusted-dirs.h"

static void nacl_irt_exit (int status) {
  NACL_SYSCALL (exit) (status);
  while (1) (*(void (*)(void)) 0) ();  /* Crash.  */
}

static int nacl_irt_gettod (struct timeval *tv) {
  return -NACL_SYSCALL (gettimeofday) (tv, NULL);
}

static int nacl_irt_clock (clock_t *ticks) {
  *ticks = NACL_SYSCALL (clock) ();  /* Cannot fail.  */
  return 0;
}

static int nacl_irt_nanosleep (const struct timespec *req,
                               struct timespec *rem) {
  return -NACL_SYSCALL (nanosleep) (req, rem);
}

static int nacl_irt_sched_yield (void) {
  return -NACL_SYSCALL (sched_yield) ();
}

static int nacl_irt_sysconf (int name, int *value) {
  return -NACL_SYSCALL (sysconf) (name, value);
}

static int nacl_irt_open (const char *pathname, int oflag, mode_t cmode,
                          int *newfd) {
  int rv = NACL_SYSCALL (open) (pathname, oflag, cmode);
  if (rv < 0)
    return -rv;
  *newfd = rv;
  return 0;
}

static int nacl_irt_close (int fd) {
  return -NACL_SYSCALL (close) (fd);
}

static int nacl_irt_read (int fd, void *buf, size_t count, size_t *nread) {
  int rv = NACL_SYSCALL (read) (fd, buf, count);
  if (rv < 0)
    return -rv;
  *nread = rv;
  return 0;
}

static int nacl_irt_write (int fd, const void *buf, size_t count,
                           size_t *nwrote) {
  int rv = NACL_SYSCALL (write) (fd, buf, count);
  if (rv < 0)
    return -rv;
  *nwrote = rv;
  return 0;
}

static int nacl_irt_seek (int fd, nacl_abi_off_t offset, int whence,
                          off_t *new_offset) {
  int rv = NACL_SYSCALL (lseek) (fd, &offset, whence);
  if (rv < 0)
    return -rv;
  *new_offset = offset;
  return 0;
}

static int nacl_irt_dup (int fd, int *newfd) {
  int rv = NACL_SYSCALL (dup) (fd);
  if (rv < 0)
    return -rv;
  *newfd = rv;
  return 0;
}

static int nacl_irt_dup2 (int fd, int newfd) {
  int rv = NACL_SYSCALL (dup2) (fd, newfd);
  if (rv < 0)
    return -rv;
  return 0;
}

static int nacl_irt_fstat (int fd, struct nacl_abi_stat *st) {
  return -NACL_SYSCALL (fstat) (fd, st);
}

static int nacl_irt_stat (const char *pathname, struct nacl_abi_stat *st) {
  return -NACL_SYSCALL (stat) (pathname, st);
}

static int nacl_irt_getdents (int fd, struct dirent *buf, size_t count,
                              size_t *nread) {
  int rv = NACL_SYSCALL (getdents) (fd, buf, count);
  if (rv < 0)
    return -rv;
  *nread = rv;
  return 0;
}

static int nacl_irt_sysbrk (void **newbrk) {
  /*
   * The syscall does not actually indicate error.  It just returns the
   * new current value, which is unchanged if something went wrong.
   * But if the requested value was below the end of the data segment,
   * the new value will be greater, but this is not "going wrong".
   * Here we just approximate a saner interface: you get what you requested,
   * you did a "probe" request passing NULL in, or it's an error.
   * TODO(mcgrathr): this interface should just go away!!
   */
  void *requested = *newbrk;
  void *got = NACL_SYSCALL (sysbrk) (requested);

  if (got == requested || requested == NULL) {
    *newbrk = got;
    return 0;
  }

  return (12 /* ENOSYS */);
}

static int nacl_irt_mmap (void **addr, size_t len,
                          int prot, int flags, int fd, off_t off) {
  uint32_t rv = (uintptr_t) NACL_SYSCALL (mmap) (*addr, len, prot, flags,
                                                 fd, &off);
  if ((uint32_t) rv > 0xffff0000u)
    return -(int32_t) rv;
  *addr = (void *) (uintptr_t) rv;
  return 0;
}

static int nacl_irt_munmap (void *addr, size_t len) {
  return -NACL_SYSCALL (munmap) (addr, len);
}

static int nacl_irt_mprotect (void *addr, size_t len, int prot) {
  return -NACL_SYSCALL (mprotect) (addr, len, prot);
}

static int nacl_irt_dyncode_create(void *dest, const void *src, size_t size) {
  return -NACL_SYSCALL(dyncode_create)(dest, src, size);
}

static int nacl_irt_dyncode_modify(void *dest, const void *src, size_t size) {
  return -NACL_SYSCALL(dyncode_modify)(dest, src, size);
}

static int nacl_irt_dyncode_delete(void *dest, size_t size) {
  return -NACL_SYSCALL(dyncode_delete)(dest, size);
}

static int nacl_irt_thread_create (void *start_user_address, void *stack,
                                   void *thread_ptr) {
  return -NACL_SYSCALL (thread_create) (start_user_address, stack,
                                        thread_ptr, 0);
}

static void nacl_irt_thread_exit (int32_t *stack_flag) {
  NACL_SYSCALL (thread_exit) (stack_flag);
  while (1) (*(void (*)(void)) 0) ();  /* Crash.  */
}

static int nacl_irt_thread_nice (const int nice) {
  return -NACL_SYSCALL (thread_nice) (nice);
}

static int nacl_irt_mutex_create (int *mutex_handle) {
  int rv = NACL_SYSCALL (mutex_create) ();
  if (rv < 0)
    return -rv;
  *mutex_handle = rv;
  return 0;
}

/*
 * Today a mutex handle is just an fd and we destroy it with close.
 * But this might not always be so.
 */
static int nacl_irt_mutex_destroy (int mutex_handle) {
  return -NACL_SYSCALL (close) (mutex_handle);
}

static int nacl_irt_mutex_lock (int mutex_handle) {
  return -NACL_SYSCALL (mutex_lock) (mutex_handle);
}

static int nacl_irt_mutex_unlock(int mutex_handle) {
  return -NACL_SYSCALL (mutex_unlock) (mutex_handle);
}

static int nacl_irt_mutex_trylock(int mutex_handle) {
  return -NACL_SYSCALL (mutex_trylock) (mutex_handle);
}

static int nacl_irt_cond_create (int *cond_handle) {
  int rv = NACL_SYSCALL (cond_create) ();
  if (rv < 0)
    return -rv;
  *cond_handle = rv;
  return 0;
}

/*
 * Today a cond handle is just an fd and we destroy it with close.
 * But this might not always be so.
 */
static int nacl_irt_cond_destroy (int cond_handle) {
  return -NACL_SYSCALL (close) (cond_handle);
}

static int nacl_irt_cond_signal (int cond_handle) {
  return -NACL_SYSCALL (cond_signal) (cond_handle);
}

static int nacl_irt_cond_broadcast (int cond_handle) {
  return -NACL_SYSCALL (cond_broadcast) (cond_handle);
}

static int nacl_irt_cond_wait (int cond_handle, int mutex_handle) {
  return -NACL_SYSCALL (cond_wait) (cond_handle, mutex_handle);
}

static int nacl_irt_cond_timed_wait_abs (int cond_handle, int mutex_handle,
                                         const struct timespec *abstime) {
  return -NACL_SYSCALL (cond_timed_wait_abs) (cond_handle, mutex_handle,
                                              abstime);
}

static int nacl_irt_tls_init (void *tdb) {
  return -NACL_SYSCALL (tls_init) (tdb);
}

static void *nacl_irt_tls_get (void) {
  return NACL_SYSCALL (tls_get) ();
}

static int nacl_irt_open_as_resource (const char *pathname, int *newfd) {
  return __nacl_irt_open (pathname, O_RDONLY, 0, newfd);
}

/* Load files from DL_DST_LIB using IRT's open_resource. Other paths
   will be processed using regular open syscall.

   Note: nacl_mount may change this logic if needed.  */
static int (*___nacl_irt_open_resource) (const char* file, int *fd);
static int nacl_irt_open_resource (const char *pathname, int *newfd) {
  if (memcmp (DL_DST_LIB "/", pathname, sizeof (DL_DST_LIB)))
    return __nacl_irt_open (pathname, O_RDONLY, 0, newfd);
  else
    return ___nacl_irt_open_resource (pathname + sizeof (DL_DST_LIB) - 1,
				      newfd);
}

static int nacl_irt_clock_getres(clockid_t clk_id,
                                 struct timespec *res) {
  return -NACL_SYSCALL (clock_getres) (clk_id, res);
}

static int nacl_irt_clock_gettime(clockid_t clk_id,
                                  struct timespec *tp) {
  return -NACL_SYSCALL (clock_gettime) (clk_id, tp);
}

static size_t no_interface (const char *interface_ident,
                            void *table, size_t tablesize) {
  return 0;
}

static int not_implemented() {
  return (38 /* ENOSYS */);
}

size_t (*__nacl_irt_query) (const char *interface_ident,
			    void *table, size_t tablesize);

int (*__nacl_irt_mkdir) (const char* pathname, mode_t mode);
int (*__nacl_irt_rmdir) (const char* pathname);
int (*__nacl_irt_chdir) (const char* pathname);
int (*__nacl_irt_getcwd) (char* buf, size_t size, int *len);

void (*__nacl_irt_exit) (int status);
int (*__nacl_irt_gettod) (struct timeval *tv);
int (*__nacl_irt_clock) (clock_t *ticks);
int (*__nacl_irt_nanosleep) (const struct timespec *req, struct timespec *rem);
int (*__nacl_irt_sched_yield) (void);
int (*__nacl_irt_sysconf) (int name, int *value);

int (*__nacl_irt_open) (const char *pathname, int oflag, mode_t cmode,
			int *newfd);
int (*__nacl_irt_close) (int fd);
int (*__nacl_irt_read) (int fd, void *buf, size_t count, size_t *nread);
int (*__nacl_irt_write) (int fd, const void *buf, size_t count, size_t *nwrote);
int (*__nacl_irt_seek) (int fd, off_t offset, int whence, off_t *new_offset);
int (*__nacl_irt_dup) (int fd, int *newfd);
int (*__nacl_irt_dup2) (int fd, int newfd);
int (*__nacl_irt_fstat) (int fd, struct nacl_abi_stat *);
int (*__nacl_irt_stat) (const char *pathname, struct nacl_abi_stat *);
int (*__nacl_irt_getdents) (int fd, struct dirent *, size_t count,
			    size_t *nread);
int (*__nacl_irt_socket) (int domain, int type, int protocol, int *sd);
int (*__nacl_irt_accept) (int sockfd, struct sockaddr *addr,
                          socklen_t *addrlen, int *sd);
int (*__nacl_irt_bind) (int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int (*__nacl_irt_listen) (int sockfd, int backlog);
int (*__nacl_irt_connect) (int sockfd, const struct sockaddr *addr,
                           socklen_t addrlen);
int (*__nacl_irt_send) (int sockfd, const void *buf, size_t len, int flags,
                        int *count);
int (*__nacl_irt_sendmsg) (int sockfd, const struct msghdr *msg, int flags,
                           int *count);
int (*__nacl_irt_sendto) (int sockfd, const void *buf, size_t len, int flags,
                          const struct sockaddr *dest_addr, socklen_t addrlen,
						  int *count);
int (*__nacl_irt_recv) (int sockfd, void *buf, size_t len, int flags, int *count);
int (*__nacl_irt_recvmsg) (int sockfd, struct msghdr *msg, int flags, int *count);
int (*__nacl_irt_recvfrom) (int sockfd, void *buf, size_t len, int flags,
                            struct sockaddr *dest_addr, socklen_t* addrlen, int *count);

int (*__nacl_irt_epoll_create) (int size, int *fd);
int (*__nacl_irt_epoll_create1) (int flags, int *fd);
int (*__nacl_irt_epoll_ctl) (int epfd, int op, int fd,
                             struct epoll_event *event);
int (*__nacl_irt_epoll_pwait) (int epfd, struct epoll_event *events,
    int maxevents, int timeout, const sigset_t *sigmask, size_t sigset_size,
	int *count);
int (*__nacl_irt_epoll_wait) (int epfd, struct epoll_event *events,
                                int maxevents, int timeout, int *count);
int (*__nacl_irt_poll) (struct pollfd *fds, nfds_t nfds,
                          int timeout, int *count);
int (*__nacl_irt_ppoll) (struct pollfd *fds, nfds_t nfds,
    const struct timespec *timeout, const sigset_t *sigmask,
	size_t sigset_size, int *count);
int (*__nacl_irt_select) (int nfds, fd_set *readfds,
    fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout,
	int *count);
int (*__nacl_irt_pselect) (int nfds, fd_set *readfds,
    fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout,
	void* sigmask, int *count);
int (*__nacl_irt_getpeername) (int sockfd, struct sockaddr *addr,
                               socklen_t *addrlen);
int (*__nacl_irt_getsockname) (int sockfd, struct sockaddr *addr,
                               socklen_t *addrlen);
int (*__nacl_irt_getsockopt) (int sockfd, int level, int optname,
               void *optval, socklen_t *optlen);
int (*__nacl_irt_setsockopt) (int sockfd, int level, int optname,
               const void *optval, socklen_t optlen);
int (*__nacl_irt_socketpair) (int domain, int type, int protocol, int sv[2]);
int (*__nacl_irt_shutdown) (int sockfd, int how);


int (*__nacl_irt_sysbrk) (void **newbrk);
int (*__nacl_irt_mmap) (void **addr, size_t len, int prot, int flags,
			int fd, off_t off);
int (*__nacl_irt_munmap) (void *addr, size_t len);
int (*__nacl_irt_mprotect) (void *addr, size_t len, int prot);

int (*__nacl_irt_dyncode_create) (void *dest, const void *src, size_t size);
int (*__nacl_irt_dyncode_modify) (void *dest, const void *src, size_t size);
int (*__nacl_irt_dyncode_delete) (void *dest, size_t size);

int (*__nacl_irt_thread_create) (void *start_user_address, void *stack,
				 void *thread_ptr);
void (*__nacl_irt_thread_exit) (int32_t *stack_flag);
int (*__nacl_irt_thread_nice) (const int nice);

int (*__nacl_irt_mutex_create) (int *mutex_handle);
int (*__nacl_irt_mutex_destroy) (int mutex_handle);
int (*__nacl_irt_mutex_lock) (int mutex_handle);
int (*__nacl_irt_mutex_unlock) (int mutex_handle);
int (*__nacl_irt_mutex_trylock) (int mutex_handle);

int (*__nacl_irt_cond_create) (int *cond_handle);
int (*__nacl_irt_cond_destroy) (int cond_handle);
int (*__nacl_irt_cond_signal) (int cond_handle);
int (*__nacl_irt_cond_broadcast) (int cond_handle);
int (*__nacl_irt_cond_wait) (int cond_handle, int mutex_handle);
int (*__nacl_irt_cond_timed_wait_abs) (int cond_handle, int mutex_handle,
				       const struct timespec *abstime);

int (*__nacl_irt_tls_init) (void *tdb);
void *(*__nacl_irt_tls_get) (void);

int (*__nacl_irt_open_resource) (const char* file, int *fd);

int (*__nacl_irt_clock_getres) (clockid_t clk_id, struct timespec *res);
int (*__nacl_irt_clock_gettime) (clockid_t clk_id, struct timespec *tp);

#define LIND

#ifdef LIND
#include <lind_syscalls.h>
#include <lind_file.h>
size_t (*saved_nacl_irt_query)(const char *interface_ident, void *table, size_t tablesize);

static int nacl_irt_mkdir_lind (const char* pathname, mode_t mode)
{
    return -lind_mkdir(mode, pathname);
}

static int nacl_irt_rmdir_lind (const char* pathname)
{
    return -lind_rmdir(pathname);
}

static int nacl_irt_chdir_lind (const char* pathname)
{
    return -lind_chdir(pathname);
}

static void __nacl_abi_stat_from_stat(struct nacl_abi_stat *nacl_st, struct stat *st)
{
#define copy_element(from, to) \
    (nacl_st->to) = (st->from);
  copy_element(st_dev, nacl_abi_st_dev);
  copy_element(st_mode, nacl_abi_st_mode);
  copy_element(st_nlink, nacl_abi_st_nlink);
  copy_element(st_uid, nacl_abi_st_uid);
  copy_element(st_gid, nacl_abi_st_gid);
  copy_element(st_rdev, nacl_abi_st_rdev);
  copy_element(st_size, nacl_abi_st_size);
  copy_element(st_blksize, nacl_abi_st_blksize);
  copy_element(st_blocks, nacl_abi_st_blocks);
  copy_element(st_atim.tv_sec, nacl_abi_st_atime);
  copy_element(st_mtim.tv_sec, nacl_abi_st_mtime);
  copy_element(st_ctim.tv_sec, nacl_abi_st_ctime);
  copy_element(st_ino, nacl_abi_st_ino);
#undef copy_element
}

static int nacl_irt_stat_lind (const char *pathname, struct nacl_abi_stat *st) {
    int lind_fd = is_lind_file(pathname);
    if(lind_fd) {
        struct stat _stat;
        //version fixed to 1
        int rc = -lind_xstat(1, pathname, &_stat);
        __nacl_abi_stat_from_stat(st, &_stat);
        return rc;
    } else {
        return -NACL_SYSCALL (stat) (pathname, st);
    }
}

static int nacl_irt_fstat_lind (int fd, struct nacl_abi_stat *st) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    if(lf->isLindFd) {
        struct stat _stat;
        //version fixed to 1
        int rc = -lind_fxstat(fd, 1, &_stat);
        __nacl_abi_stat_from_stat(st, &_stat);
        return rc;
    } else {
        return -NACL_SYSCALL (fstat) (fd, st);
    }
}

static int nacl_irt_open_lind (const char *pathname, int oflag, mode_t cmode,
                          int *newfd) {
    int lind_fd = is_lind_file(pathname);
    int rv = 0;
    static unsigned int open_count = 0;
    if(lind_fd) {
        rv = lind_open(oflag, cmode, pathname);
    } else {
        if(open_count++<max_nacl_fd) {
            rv = NACL_SYSCALL (open) (pathname, oflag, cmode);
        } else {
            return 1; //TODO: some other value?
        }
    }
    if (rv < 0)
      return -rv;
    struct lind_file lf;
    lf.fd = rv;
    lf.isLindFd = lind_fd;
    add_lind_file(&lf);
    *newfd = rv;
    return 0;
}

static int nacl_irt_close_lind (int fd) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    int is_lind_file = lf->isLindFd;
    delete_lind_file(fd);
    if(is_lind_file) {
        return -lind_close (fd);
    } else {
        return -NACL_SYSCALL (close) (fd);
    }
}

static int nacl_irt_read_lind (int fd, void *buf, size_t count, size_t *nread) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    int rv = 0;
    if(lf->isLindFd) {
        rv = lind_read (fd, count, buf);
    } else {
        rv = NACL_SYSCALL (read) (fd, buf, count);
    }
    if (rv < 0)
        return -rv;
    *nread = rv;
    return 0;
}

static int nacl_irt_write_lind (int fd, const void *buf, size_t count,
                           size_t *nwrote) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    int rv;
    if(lf->isLindFd) {
        rv = lind_write (fd, count, buf);
    } else {
        rv = NACL_SYSCALL (write) (fd, buf, count);
    }
    if (rv < 0)
        return -rv;
    *nwrote = rv;
    return 0;
}

static int nacl_irt_seek_lind (int fd, nacl_abi_off_t offset, int whence,
                          off_t *new_offset) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    off_t returned_offset = 0;
    int rv;
    if(lf->isLindFd) {
        rv = lind_lseek (offset, fd, whence, &returned_offset);
    } else {
        rv = NACL_SYSCALL (lseek) (fd, &offset, whence);
    }
    if (rv < 0)
      return -rv;
    *new_offset = returned_offset;
    return 0;
}

static int nacl_irt_dup_lind (int fd, int *newfd) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    int rv = 0;
    if(lf->isLindFd) {
        rv = lind_dup (fd);
    } else {
        rv = NACL_SYSCALL (dup) (fd);
    }
    if (rv < 0)
      return -rv;
    *newfd = rv;
    return 0;
}

static int nacl_irt_dup2_lind (int fd, int newfd) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    int rv = 0;
    if(lf->isLindFd) {
        rv = lind_dup2 (fd, newfd);
    } else {
        rv = NACL_SYSCALL (dup2) (fd, newfd);
    }
    if (rv < 0)
        return -rv;
    return 0;
}

static int nacl_irt_getdents_lind (int fd, struct dirent *buf, size_t count,
                              size_t *nread) {
    struct lind_file* lf = NULL;
    if((lf=get_lind_file(fd))==NULL) {
        return 1; //TODO: find another value
    }
    int rv = 0;
    if(lf->isLindFd) {
        rv = lind_getdents (fd, count, buf);
    } else {
        rv = NACL_SYSCALL (getdents) (fd, buf, count);
    }
    if (rv < 0)
      return -rv;
    *nread = rv;
    return 0;
}

#endif

void
init_irt_table (void)
{
#ifdef LIND
    saved_nacl_irt_query = __nacl_irt_query;
    //currently we manually bind all IRT calls
    __nacl_irt_query = 0;
    max_nacl_fd = 50;
#endif
  union {
    struct nacl_irt_basic nacl_irt_basic;
    struct nacl_irt_fdio nacl_irt_fdio;
    struct nacl_irt_filename nacl_irt_filename;
    struct nacl_irt_memory_v0_2 nacl_irt_memory;
    struct nacl_irt_dyncode nacl_irt_dyncode;
    struct nacl_irt_thread nacl_irt_thread;
    struct nacl_irt_mutex nacl_irt_mutex;
    struct nacl_irt_cond nacl_irt_cond;
    struct nacl_irt_tls nacl_irt_tls;
    struct nacl_irt_resource_open nacl_irt_resource_open;
    struct nacl_irt_clock nacl_irt_clock;
  } u;

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_BASIC_v0_1, &u.nacl_irt_basic,
			sizeof(u.nacl_irt_basic)) == sizeof(u.nacl_irt_basic))
    {
      __nacl_irt_exit = u.nacl_irt_basic.exit;
      __nacl_irt_gettod = u.nacl_irt_basic.gettod;
      __nacl_irt_clock = u.nacl_irt_basic.clock;
      __nacl_irt_nanosleep = u.nacl_irt_basic.nanosleep;
      __nacl_irt_sched_yield = u.nacl_irt_basic.sched_yield;
      __nacl_irt_sysconf = u.nacl_irt_basic.sysconf;
    }
  else
    {
      __nacl_irt_exit = nacl_irt_exit;
      __nacl_irt_gettod = nacl_irt_gettod;
      __nacl_irt_clock = nacl_irt_clock;
      __nacl_irt_nanosleep = nacl_irt_nanosleep;
      __nacl_irt_sched_yield = nacl_irt_sched_yield;
      __nacl_irt_sysconf = nacl_irt_sysconf;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_FDIO_v0_1, &u.nacl_irt_fdio,
		        sizeof(u.nacl_irt_fdio)) == sizeof(u.nacl_irt_fdio))
    {
      __nacl_irt_close = u.nacl_irt_fdio.close;
      __nacl_irt_dup = u.nacl_irt_fdio.dup;
      __nacl_irt_dup2 = u.nacl_irt_fdio.dup2;
      __nacl_irt_read = u.nacl_irt_fdio.read;
      __nacl_irt_write = u.nacl_irt_fdio.write;
      __nacl_irt_seek = u.nacl_irt_fdio.seek;
      __nacl_irt_fstat = u.nacl_irt_fdio.fstat;
      __nacl_irt_getdents = u.nacl_irt_fdio.getdents;
    }
  else
    {
#ifndef LIND
      __nacl_irt_close = nacl_irt_close;
      __nacl_irt_dup = nacl_irt_dup;
      __nacl_irt_dup2 = nacl_irt_dup2;
      __nacl_irt_read = nacl_irt_read;
      __nacl_irt_write = nacl_irt_write;
      __nacl_irt_seek = nacl_irt_seek;
      __nacl_irt_fstat = nacl_irt_fstat;
      __nacl_irt_getdents = nacl_irt_getdents;
#else
      __nacl_irt_close = nacl_irt_close_lind;
      __nacl_irt_dup = nacl_irt_dup_lind;
      __nacl_irt_dup2 = nacl_irt_dup2_lind;
      __nacl_irt_read = nacl_irt_read_lind;
      __nacl_irt_write = nacl_irt_write_lind;
      __nacl_irt_seek = nacl_irt_seek_lind;
      __nacl_irt_fstat = nacl_irt_fstat_lind;
      __nacl_irt_getdents = nacl_irt_getdents_lind;
#endif
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_FILENAME_v0_1, &u.nacl_irt_filename,
		    sizeof(u.nacl_irt_filename)) == sizeof(u.nacl_irt_filename))
    {
      __nacl_irt_open = u.nacl_irt_filename.open;
      __nacl_irt_stat = u.nacl_irt_filename.nacl_abi_stat;
    }
  else
    {
#ifndef LIND
      __nacl_irt_open = nacl_irt_open;
      __nacl_irt_stat = nacl_irt_stat;
#else
      __nacl_irt_open = nacl_irt_open_lind;
      __nacl_irt_stat = nacl_irt_stat_lind;
#endif
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_MEMORY_v0_2, &u.nacl_irt_memory,
		        sizeof(u.nacl_irt_memory)) == sizeof(u.nacl_irt_memory))
    {
      __nacl_irt_sysbrk = u.nacl_irt_memory.sysbrk;
      __nacl_irt_mmap = u.nacl_irt_memory.mmap;
      __nacl_irt_munmap = u.nacl_irt_memory.munmap;
      __nacl_irt_mprotect = u.nacl_irt_memory.mprotect;
    }
  else if (__nacl_irt_query &&
           __nacl_irt_query (NACL_IRT_MEMORY_v0_1, &u.nacl_irt_memory,
                             sizeof(struct nacl_irt_memory_v0_1)) ==
               sizeof(struct nacl_irt_memory_v0_1))
    {
      __nacl_irt_sysbrk = u.nacl_irt_memory.sysbrk;
      __nacl_irt_mmap = u.nacl_irt_memory.mmap;
      __nacl_irt_munmap = u.nacl_irt_memory.munmap;
      __nacl_irt_mprotect = not_implemented;
    }
  else
    {
      __nacl_irt_sysbrk = nacl_irt_sysbrk;
      __nacl_irt_mmap = nacl_irt_mmap;
      __nacl_irt_munmap = nacl_irt_munmap;
      __nacl_irt_mprotect = nacl_irt_mprotect;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_DYNCODE_v0_1, &u.nacl_irt_dyncode,
		      sizeof(u.nacl_irt_dyncode)) == sizeof(u.nacl_irt_dyncode))
    {
      __nacl_irt_dyncode_create = u.nacl_irt_dyncode.dyncode_create;
      __nacl_irt_dyncode_modify = u.nacl_irt_dyncode.dyncode_modify;
      __nacl_irt_dyncode_delete = u.nacl_irt_dyncode.dyncode_delete;
    }
  else
    {
      __nacl_irt_dyncode_create = nacl_irt_dyncode_create;
      __nacl_irt_dyncode_modify = nacl_irt_dyncode_modify;
      __nacl_irt_dyncode_delete = nacl_irt_dyncode_delete;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_THREAD_v0_1, &u.nacl_irt_thread,
			sizeof(u.nacl_irt_thread)) == sizeof(u.nacl_irt_thread))
    {
      __nacl_irt_thread_create = u.nacl_irt_thread.thread_create;
      __nacl_irt_thread_exit = u.nacl_irt_thread.thread_exit;
      __nacl_irt_thread_nice = u.nacl_irt_thread.thread_nice;
    }
  else
    {
      __nacl_irt_thread_create = nacl_irt_thread_create;
      __nacl_irt_thread_exit = nacl_irt_thread_exit;
      __nacl_irt_thread_nice = nacl_irt_thread_nice;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_MUTEX_v0_1, &u.nacl_irt_mutex,
		        sizeof(u.nacl_irt_mutex)) == sizeof(u.nacl_irt_mutex))
    {
      __nacl_irt_mutex_create = u.nacl_irt_mutex.mutex_create;
      __nacl_irt_mutex_destroy = u.nacl_irt_mutex.mutex_destroy;
      __nacl_irt_mutex_lock = u.nacl_irt_mutex.mutex_lock;
      __nacl_irt_mutex_unlock = u.nacl_irt_mutex.mutex_unlock;
      __nacl_irt_mutex_trylock = u.nacl_irt_mutex.mutex_trylock;
    }
  else
    {
      __nacl_irt_mutex_create = nacl_irt_mutex_create;
      __nacl_irt_mutex_destroy = nacl_irt_mutex_destroy;
      __nacl_irt_mutex_lock = nacl_irt_mutex_lock;
      __nacl_irt_mutex_unlock = nacl_irt_mutex_unlock;
      __nacl_irt_mutex_trylock = nacl_irt_mutex_trylock;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_COND_v0_1, &u.nacl_irt_cond,
		        sizeof(u.nacl_irt_cond)) == sizeof(u.nacl_irt_cond))
    {
      __nacl_irt_cond_create = u.nacl_irt_cond.cond_create;
      __nacl_irt_cond_destroy = u.nacl_irt_cond.cond_destroy;
      __nacl_irt_cond_signal = u.nacl_irt_cond.cond_signal;
      __nacl_irt_cond_broadcast = u.nacl_irt_cond.cond_broadcast;
      __nacl_irt_cond_wait = u.nacl_irt_cond.cond_wait;
      __nacl_irt_cond_timed_wait_abs = u.nacl_irt_cond.cond_timed_wait_abs;
    }
  else
    {
      __nacl_irt_cond_create = nacl_irt_cond_create;
      __nacl_irt_cond_destroy = nacl_irt_cond_destroy;
      __nacl_irt_cond_signal = nacl_irt_cond_signal;
      __nacl_irt_cond_broadcast = nacl_irt_cond_broadcast;
      __nacl_irt_cond_wait = nacl_irt_cond_wait;
      __nacl_irt_cond_timed_wait_abs = nacl_irt_cond_timed_wait_abs;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_TLS_v0_1, &u.nacl_irt_tls,
		        sizeof(u.nacl_irt_tls)) == sizeof(u.nacl_irt_tls))
    {
      __nacl_irt_tls_init = u.nacl_irt_tls.tls_init;
      __nacl_irt_tls_get = u.nacl_irt_tls.tls_get;
    }
  else
    {
      __nacl_irt_tls_init = nacl_irt_tls_init;
      __nacl_irt_tls_get = nacl_irt_tls_get;
    }

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_RESOURCE_OPEN_v0_1, &u.nacl_irt_resource_open,
	  sizeof(u.nacl_irt_resource_open)) == sizeof(u.nacl_irt_resource_open))
    {
      ___nacl_irt_open_resource = u.nacl_irt_resource_open.open_resource;
      __nacl_irt_open_resource = nacl_irt_open_resource;
#ifdef IS_IN_rtld
      if (_dl_argc == 1)
        {
          static const char *argv[] =
	    {
	      DL_DST_LIB "/runnable-ld.so",
	      DL_DST_LIB "/main.nexe",
	      0
	    };
          _dl_argc = 2;
          _dl_argv = (char **)argv;
        }
#endif
    }
  else
    __nacl_irt_open_resource = nacl_irt_open_as_resource;

  if (__nacl_irt_query &&
      __nacl_irt_query (NACL_IRT_CLOCK_v0_1, &u.nacl_irt_clock,
      sizeof(u.nacl_irt_clock)) == sizeof(u.nacl_irt_clock))
    {
      __nacl_irt_clock_getres = u.nacl_irt_clock.getres;
      __nacl_irt_clock_gettime = u.nacl_irt_clock.gettime;
    }
  else
    {
      __nacl_irt_clock_getres = nacl_irt_clock_getres;
      __nacl_irt_clock_gettime = nacl_irt_clock_gettime;
    }

  if (!__nacl_irt_query)
    __nacl_irt_query = no_interface;

#ifndef LIND
  __nacl_irt_mkdir = not_implemented;
  __nacl_irt_chdir = not_implemented;
  __nacl_irt_rmdir = not_implemented;
#else
  __nacl_irt_mkdir = nacl_irt_mkdir_lind;
  __nacl_irt_chdir = nacl_irt_chdir_lind;
  __nacl_irt_rmdir = nacl_irt_rmdir_lind;
#endif
  __nacl_irt_getcwd = not_implemented;

  __nacl_irt_epoll_create = not_implemented;
  __nacl_irt_epoll_create1 = not_implemented;
  __nacl_irt_epoll_ctl = not_implemented;
  __nacl_irt_epoll_pwait = not_implemented;
  __nacl_irt_epoll_wait = not_implemented;
  __nacl_irt_poll = not_implemented;
  __nacl_irt_ppoll = not_implemented;
  __nacl_irt_socket = not_implemented;
  __nacl_irt_accept = not_implemented;
  __nacl_irt_bind = not_implemented;
  __nacl_irt_listen = not_implemented;
  __nacl_irt_connect = not_implemented;
  __nacl_irt_send = not_implemented;
  __nacl_irt_sendmsg = not_implemented;
  __nacl_irt_sendto = not_implemented;
  __nacl_irt_recv = not_implemented;
  __nacl_irt_recvmsg = not_implemented;
  __nacl_irt_recvfrom = not_implemented;
  __nacl_irt_select = not_implemented;
  __nacl_irt_pselect = not_implemented;
  __nacl_irt_getpeername = not_implemented;
  __nacl_irt_getsockname = not_implemented;
  __nacl_irt_getsockopt = not_implemented;
  __nacl_irt_setsockopt = not_implemented;
  __nacl_irt_socketpair = not_implemented;
  __nacl_irt_shutdown = not_implemented;
}

size_t nacl_interface_query(const char *interface_ident,
                            void *table, size_t tablesize) {
  return (*__nacl_irt_query)(interface_ident, table, tablesize);
}
