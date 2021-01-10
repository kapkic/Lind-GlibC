#ifndef _NACL_SYSDEP_H
#define _NACL_SYSDEP_H 1

#if !defined(__ASSEMBLER__)
#include <futex_emulation.h>
#include <irt_syscalls.h>
#include <lowlevellock.h>
#include <lind_syscalls.h>
#include <string.h>

/* Implementation of all syscalls for use in platform- and OS- independent code
   as inline functions.  Each function translates the syscall arguments into IRT
   arguments and allows to intercept each call in user code.
   TODO(khim): implement the interception logic.  */

# define INTERNAL_SYSCALL(name, err, nr, args...) \
  INTERNAL_SYSCALL_ ## name ## _ ## nr (&err , ## args)

# define INTERNAL_SYSCALL_NCS(name, err, nr, args...) \
  INTERNAL_SYSCALL_NCS_ ## nr (name, &err , ## args)

__extern_always_inline int
INTERNAL_SYSCALL_NCS_3 (int syscall_nr, int *err, int id1, int id2, int id3)
{
  *err = (38 /* ENOSYS */);
  return 0;
}

# ifdef __i386__
#  define INTERNAL_SYSCALL_chown_3	INTERNAL_SYSCALL_chown32_3
#  define INTERNAL_SYSCALL_fchown_3	INTERNAL_SYSCALL_fchown32_3
#  define INTERNAL_SYSCALL_getegid_0	INTERNAL_SYSCALL_getegid32_0
#  define INTERNAL_SYSCALL_geteuid_0	INTERNAL_SYSCALL_geteuid32_0
#  define INTERNAL_SYSCALL_getgid_0	INTERNAL_SYSCALL_getgid32_0
#  define INTERNAL_SYSCALL_getgroups_2	INTERNAL_SYSCALL_getgroups32_2
#  define INTERNAL_SYSCALL_getresgid_3	INTERNAL_SYSCALL_getresgid32_3
#  define INTERNAL_SYSCALL_getresuid_3	INTERNAL_SYSCALL_getresuid32_3
#  define INTERNAL_SYSCALL_getuid_0	INTERNAL_SYSCALL_getuid32_0
#  define INTERNAL_SYSCALL_lchown_3	INTERNAL_SYSCALL_lchown32_3
#  define INTERNAL_SYSCALL_setfsgid_1	INTERNAL_SYSCALL_setfsgid32_1
#  define INTERNAL_SYSCALL_setfsuid_1	INTERNAL_SYSCALL_setfsuid32_1
#  define INTERNAL_SYSCALL_setgid_1	INTERNAL_SYSCALL_setgid32_1
#  define INTERNAL_SYSCALL_setgroups_2	INTERNAL_SYSCALL_setgroups32_2
#  define INTERNAL_SYSCALL_setregid_2	INTERNAL_SYSCALL_setregid32_2
#  define INTERNAL_SYSCALL_setresgid_3	INTERNAL_SYSCALL_setresgid32_3
#  define INTERNAL_SYSCALL_setresuid_3	INTERNAL_SYSCALL_setresuid32_3
#  define INTERNAL_SYSCALL_setreuid_2	INTERNAL_SYSCALL_setreuid32_2
#  define INTERNAL_SYSCALL_setuid_1	INTERNAL_SYSCALL_setuid32_1
# endif

__extern_always_inline int
INTERNAL_SYSCALL_access_2 (int *err, const char *pathname, int mode)
{
  lind_strace("access unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_acct_1 (int *err, const char *filename)
{
  lind_strace("acct unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_adjtimex_1 (int *err, struct timex *buf)
{
  lind_strace("adjtimex unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_arch_prctl_2 (int *err, int code,
			    union __attribute__ ((__transparent_union__))
			    {
			      long *parg;
			      long larg;
			      int iarg;
			    } addr)
{
  lind_strace("arch_prctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_bdflush_2 (int *err, int func,
			    union __attribute__ ((__transparent_union__))
			    {
			      long *parg;
			      long larg;
			      int iarg;
			    } data)
{
  lind_strace("bdflush unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

struct __user_cap_header_struct;
struct __user_cap_data_struct;
__extern_always_inline int
INTERNAL_SYSCALL_capget_2 (int *err, struct __user_cap_header_struct *hdrp,
			   struct __user_cap_data_struct *datap)
{
  lind_strace("capget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_capset_2 (int *err, struct __user_cap_header_struct *hdrp,
			   const struct __user_cap_data_struct *datap)
{
  lind_strace("capset unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_chdir_1 (int *err, const char *path)
{
  *err = __nacl_irt_chdir (path);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_chmod_2 (int *err, const char *path, mode_t mode)
{
  lind_strace("chmod unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_chown_3 (int *err, const char *path,
			  uid_t owner, gid_t group)
{
  lind_strace("chown unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_chroot_1 (int *err, const char *path)
{
  lind_strace("chroot unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_getres_2 (int *err, clockid_t clk_id,
				 struct timespec *res)
{
  lind_strace("clock_getres unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_gettime_2 (int *err, clockid_t clk_id,
				  struct timespec *tp)
{
  lind_strace("clock_gettime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_nanosleep_4 (int *err, clockid_t clock_id, int flags,
				    const struct timespec *request,
				    struct timespec *remain)
{
  lind_strace("clock_nanosleep unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_settime_2 (int *err, clockid_t clk_id,
				  const struct timespec *tp)
{
  lind_strace("clock_settime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

struct pthread;
__extern_always_inline pid_t
INTERNAL_SYSCALL_clone_7 (int *err, int (*fn)(void *), void *child_stack,
			  int flags, void *arg, pid_t *ptid,
			  struct pthread *tls, pid_t *ctid)
{
  lind_strace("clone unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_clone_4(int *err, int (*fn)(void *), void *child_stack,
			  int flags, void *arg)
{
  return INTERNAL_SYSCALL_clone_7 (err, fn, child_stack, flags, arg,
				   NULL, NULL, NULL);
}

__extern_always_inline int
INTERNAL_SYSCALL_close_1 (int *err, unsigned int fd)
{
  *err = __nacl_irt_close(fd);
  return 0;
}

__extern_always_inline __caddr_t
INTERNAL_SYSCALL_create_module_2 (int *err, const char *name, size_t size)
{
  lind_strace("create_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_delete_module_4 (int *err, const char *name_user,
				  unsigned int flags,
				  const struct timespec *rqtp,
				  struct timespec *rmtp)
{
  lind_strace("delete_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_create_1 (int *err, int size)
{
  int fd;
  *err = __nacl_irt_epoll_create (size, &fd);
  return fd;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_create1_1 (int *err, int flags)
{
  int fd;
  *err = __nacl_irt_epoll_create1 (flags, &fd);
  return fd;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_ctl_4 (int *err, int epfd, int op, int fd,
			      struct epoll_event *event)
{
  *err = __nacl_irt_epoll_ctl (epfd, op, fd, event);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_pwait_6 (int *err, int epfd, struct epoll_event *events,
				int maxevents, int timeout,
				const sigset_t *sigmask, size_t sigset_size)
{
  int count;
  *err = __nacl_irt_epoll_pwait (epfd, events, maxevents, timeout, sigmask,
                                 sigset_size, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_execve_3 (int *err, const char *filename, char *const argv[],
			   char *const envp[])
{
  lind_strace("execve unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_wait_4 (int *err, int epfd, struct epoll_event *events,
			       int maxevents, int timeout)
{
  int count;
  *err = __nacl_irt_epoll_wait (epfd, events, maxevents, timeout, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_eventfd2_2 (int *err, unsigned int initval, int flags)
{
  lind_strace("eventfd2 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_eventfd_1 (int *err, unsigned int initval)
{
  return INTERNAL_SYSCALL_eventfd2_2 (err, initval, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_faccessat_3 (int *err, int dirfd, const char *pathname,
			      int mode)
{
  lind_strace("faccessat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchdir_1 (int *err, int fd)
{
  lind_strace("fchdir unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchmod_2 (int *err, int fd, mode_t mode)
{
  lind_strace("fchmod unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchmodat_3 (int *err, int dirfd, const char *pathname,
			     mode_t mode)
{
  lind_strace("fchmodat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchown_3 (int *err, int fd,
			   uid_t owner, gid_t group)
{
  lind_strace("fchown unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchownat_5 (int *err, int dirfd, const char *pathname,
			     uid_t owner, gid_t group, int flags)
{
  lind_strace("fchownat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fcntl_3 (int *err, int fd, int cmd, void *arg)
{
  lind_strace("fcntl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fcntl64_3 (int *err, int fd, int cmd,
			    union __attribute__ ((__transparent_union__))
			    {
			      unsigned long ularg;
			      long larg;
			      unsigned int uiarg;
			      int iarg;
			      void *parg;
			    } arg)
{
  lind_strace("fcntl64 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fdatasync_1 (int *err, int fd)
{
  lind_strace("fdatasync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_flock_2 (int *err, int fd, int operation)
{
  lind_strace("flock unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fgetxattr_4 (int *err, int filedes, const char *name,
			      void *value, size_t size)
{
  lind_strace("fgetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_flistxattr_3 (int *err, int filedes, char *list, size_t size)
{
  lind_strace("flistxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fremovexattr_2 (int *err, int filedes, const char *name)
{
  lind_strace("fremovexattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fsetxattr_5 (int *err, int filedes, const char *name,
			      const void *value, size_t size, int flags)
{
  lind_strace("fsetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fsync_1 (int *err, int fd)
{
  lind_strace("fsync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__errordecl (__futex_emulation_unknown_operation,
	     "unknown futex operation or argument");

struct __attribute__ ((__packed__)) decoded_futex_operation
  {
    unsigned int operation	:7;
    unsigned int private	:1;
    unsigned int realtime	:1;
    unsigned int padding	:23;
};

union __attribute__ ((__transparent_union__)) encoded_futex_operation
  {
    unsigned int encoded_futex_operation;
    int const_futex_operation;
    struct decoded_futex_operation decoded_futex_operation;
  };

__extern_always_inline void
INTERNAL_SYSCALL_futex_2 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr,
			  union encoded_futex_operation futex_operation)
{
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_UNLOCK_PI:
	*err = (38 /* ENOSYS */);
	return;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
}

__extern_always_inline unsigned int
INTERNAL_SYSCALL_futex_3 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr,
			  union encoded_futex_operation futex_operation,
			  int val)
{
  int count;
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_WAKE:
	*err = -__nacl_futex_wake (addr.addr, val, __FUTEX_BITSET_MATCH_ANY,
				   &count);
	return count;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
    return 0;
}

__extern_always_inline unsigned int
INTERNAL_SYSCALL_futex_4 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr,
			  union encoded_futex_operation futex_operation,
			  int val1,
			  /* We need to accept 0 here.  May be better to
			     replace 0 with NULL in NPTL code?  */
			  union __attribute__ ((__transparent_union__))
			    {
			      const struct timespec *timeout;
			      int null_timeout;
			    } val2)
{
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_WAIT_ABS:
	*err = -__nacl_futex_wait (addr.addr, val1, __FUTEX_BITSET_MATCH_ANY,
				   val2.timeout);
	return 0;
      /* TODO(khim): hook up PI-locks to some IRT-handleable functions.  */
      case FUTEX_LOCK_PI:
      case FUTEX_UNLOCK_PI:
      case FUTEX_TRYLOCK_PI:
	*err = (38 /* ENOSYS */);
	return 0;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
    return 0;
}

__extern_always_inline unsigned int
INTERNAL_SYSCALL_futex_6 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr1,
			  union encoded_futex_operation futex_operation,
			  int val1,
			  int val2,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr2,
			  int val3)
{
  int count;
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_WAKE_OP:
	*err = -__nacl_futex_wake_op (addr1.addr, addr2.addr,
				      val1, val2, val3, &count);
	return count;
      case FUTEX_CMP_REQUEUE:
	*err = -__nacl_futex_cmp_requeue (addr1.addr, addr2.addr,
					  val1, val2, val3, &count);
	return count;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
    return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_futimesat_3 (int *err, int dirfd, const char *pathname,
			      const struct timeval times[2])
{
  lind_strace("futimesat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

struct kernel_sym;
__extern_always_inline ssize_t
INTERNAL_SYSCALL_get_kernel_syms_1 (int *err, struct kernel_sym *table)
{
  lind_strace("get_kernel_syms unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getcpu_3 (int *err, unsigned *cpu, unsigned *node,
			   struct getcpu_cache *tcache)
{
  lind_strace("getcpu unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

/* NOTE! The user-level library version returns a character pointer.

   The system call just returns the length of the buffer filled (which includes
   the ending '\0' character), or zero in case of error.  */
/*__extern_always_inline int
INTERNAL_SYSCALL_getcwd_2 (int *err, char *buf, size_t size)
{
  int len;
  *err = __nacl_irt_getcwd (buf, size, &len);
  return len;
}*/

__extern_always_inline gid_t
INTERNAL_SYSCALL_getegid_0 (int *err)
{
  lind_strace("getegid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline uid_t
INTERNAL_SYSCALL_geteuid_0 (int *err)
{
  lind_strace("geteuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline gid_t
INTERNAL_SYSCALL_getgid_0 (int *err)
{
  lind_strace("getgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getgroups_2 (int *err, int size, gid_t *list)
{
  lind_strace("getgroups unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getitimer_2 (int *err, int which, struct itimerval *curr_value)
{
  lind_strace("getitimer unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getmsg_4 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int *pflags)
{
  lind_strace("getmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_getpgid_1 (int *err, pid_t pid)
{
  lind_strace("getpgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_getpgrp_0 (int *err)
{
  lind_strace("getpgrp unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getpmsg_5 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int *pband, int *pflags)
{
  lind_strace("getpmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

/* The return value of getpriority syscall is biased by this value
   to avoid returning negative values.  */
__extern_always_inline int
INTERNAL_SYSCALL_getpriority_2 (int *err, int which, int who)
{
  lind_strace("getpriority unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getresgid_3 (int *err, gid_t *rgid, gid_t *egid, gid_t *sgid)
{
  lind_strace("getresgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getresuid_3 (int *err, uid_t *ruid, uid_t *euid, uid_t *ugid)
{
  lind_strace("getresuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getrusage_2 (int *err, int who, struct rusage *usage)
{
  lind_strace("getrusage unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_getsid_1 (int *err, pid_t pid)
{
  lind_strace("getsid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline uid_t
INTERNAL_SYSCALL_getuid_0 (int *err)
{
  lind_strace("getuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getxattr_4 (int *err, const char *path, const char *name,
			     void *value, size_t size)
{
  lind_strace("getxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_open_3 (int *err, const char *pathname, int flags, mode_t mode)
{
  int newfd;
  *err = __nacl_irt_open (pathname, flags, mode, &newfd);
  return newfd;
}

__extern_always_inline int
INTERNAL_SYSCALL_openat_4 (int *err, int dirfd, const char *pathname,
			   int flags, mode_t mode)
{
  lind_strace("openat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_init_module_3 (int *err, void *umod, unsigned long len,
				const char *uargs)
{
  lind_strace("init_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_add_watch_3 (int *err, int fd, const char *pathname,
				      uint32_t mask)
{
  lind_strace("inotify_add_watch unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_init1_1 (int *err, int flags)
{
  lind_strace("inotify_init1 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_init_0 (int * err)
{
  return INTERNAL_SYSCALL_inotify_init1_1 (err, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_rm_watch_2 (int *err, int fd, uint32_t wd)
{
  lind_strace("inotify_rm_watch unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ioctl_3 (int *err, int d, int request,
			  union __attribute__ ((__transparent_union__))
			  {
			    unsigned long ularg;
			    long larg;
			    unsigned int uiarg;
			    int iarg;
			    void *parg;
			  } arg)
{
  lind_strace("ioctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ioperm_3 (int *err, unsigned long from, unsigned long num,
			   int turn_on)
{
  lind_strace("ioperm unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_iopl_1 (int *err, int level)
{
  lind_strace("iopl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ipc_6 (int *err, unsigned int call, int first, int second,
			int third, void *ptr, long fifth)
{
  lind_strace("ipc unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ipc_5 (int *err, unsigned int call, int first, int second,
			int third, void *ptr)
{
  return INTERNAL_SYSCALL_ipc_6 (err, call, first, second, third, ptr, 0);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_kill_2 (int *err, pid_t pid, int sig)
{
  lind_strace("kill unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_laccess_2 (int *err, const char *pathname, int mode)
{
  lind_strace("laccess unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lchown_3 (int *err, const char *path,
			   uid_t owner, gid_t group)
{
  lind_strace("lchown unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lgetxattr_4 (int *err, const char *path, const char *name,
			      void *value, size_t size)
{
  lind_strace("lgetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_link_2 (int *err, const char *oldpath, const char *newpath)
{
  lind_strace("link unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_linkat_5 (int *err, int olddfd, const char *oldname,
			   int newdfd, const char *newname, int flags)
{
  lind_strace("linkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_listxattr_3 (int *err, const char *path, char *list,
			      size_t size)
{
  lind_strace("listxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_llistxattr_3 (int *err, const char *path, char *list,
			       size_t size)
{
  lind_strace("llistxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lremovexattr_2 (int *err, const char *path, const char *name)
{
  lind_strace("lremovexattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lsetxattr_5 (int *err, const char *path, const char *name,
			      const void *value, size_t size, int flags)
{
  lind_strace("lsetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_madvise_3 (int *err, void *addr, size_t length, int advice)
{
  lind_strace("madvise unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mincore_3 (int *err, void *addr, size_t length,
			    unsigned char *vec)
{
  lind_strace("mincore unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mkdir_2 (int *err, const char *pathname, mode_t mode)
{
  *err = __nacl_irt_mkdir (pathname, mode);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mkdirat_3 (int *err, int dirfd, const char *pathname,
			    mode_t mode)
{
  lind_strace("mkdirat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mknod_3 (int *err, const char *pathname,
			  mode_t mode, dev_t dev)
{
  lind_strace("mknod unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mknodat_4 (int *err, int dirfd, const char *pathname,
			    mode_t mode, dev_t dev)
{
  lind_strace("mknodat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mlock_2 (int *err, const void *addr, size_t len)
{
  lind_strace("mlock unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mlockall_1 (int *err, int flags)
{
  lind_strace("mlockall unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_modify_ldt_3 (int *err, int func, void *ptr,
			       unsigned long bytecount)
{
  lind_strace("modify_ldt unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mprotect_3 (int *err, void *addr, size_t len, int prot)
{
  *err = __nacl_irt_mprotect (addr, len, prot);
  return 0;
}

#if !defined (_LIBC) || defined(IS_IN_librt)
__extern_always_inline mqd_t
INTERNAL_SYSCALL_mq_getsetattr_3 (int *err, mqd_t mqdes,
				  struct mq_attr *newattr,
				  struct mq_attr *oldattr)
{
  lind_strace("mq_getsetattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline mqd_t
INTERNAL_SYSCALL_mq_open_4 (int *err, const char *name, int oflag, mode_t mode,
			    struct mq_attr *attr)
{
  lind_strace("mq_open unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mq_notify_2 (int *err, mqd_t mqdes,
			      const struct sigevent *notification)
{
  lind_strace("mq_notify unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_mq_timedreceive_5 (int *err, mqd_t mqdes, char *msg_ptr,
				    size_t msg_len, unsigned *msg_prio,
				    const struct timespec *abs_timeout)
{
  lind_strace("mq_timedreceive unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline mqd_t
INTERNAL_SYSCALL_mq_timedsend_5 (int *err, mqd_t mqdes, const char *msg_ptr,
				 size_t msg_len, unsigned msg_prio,
				 const struct timespec *abs_timeout)
{
  lind_strace("mq_timedsend unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mq_unlink_1 (int *err, const char *name)
{
  lind_strace("mq_unlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}
#endif

__extern_always_inline int
INTERNAL_SYSCALL_mount_5 (int *err, const char *source, const char *target,
			  const char *filesystemtype, unsigned long mountflags,
			  const void *data)
{
  lind_strace("mount unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline void*
INTERNAL_SYSCALL_mremap_5 (int *err, void *old_address, size_t old_size,
			   size_t new_size, int flags, void *new_address)
{
  lind_strace("mremap unimplemented");
  *err = (38 /* ENOSYS */);
  return NULL;
}

__extern_always_inline int
INTERNAL_SYSCALL_msgctl_3 (int *err, int msqid, int cmd, struct msqid_ds *buf)
{
  lind_strace("msgctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_msgget_2 (int *err, key_t key, int msgflg)
{
  lind_strace("msgget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_msgrcv_5 (int *err, int msqid, void *msgp, size_t msgsz,
			   long msgtyp, int msgflg)
{
  lind_strace("msgrcv unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_msgsnd_4 (int *err, int msqid, const void *msgp, size_t msgsz,
			   int msgflg)
{
  lind_strace("msgsnd unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_msync_3 (int *err, void *addr, size_t length, int flags)
{
  lind_strace("msync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_munlock_2 (int *err, const void *addr, size_t len)
{
  lind_strace("munlock unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_munlockall_0 (int *err)
{
  lind_strace("munlockall unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_munmap_2 (int *err, void *addr, size_t length)
{
  *err = __nacl_irt_munmap(addr, length);
  return 0;
}

struct nfsctl_arg;
union nfsctl_res;
__extern_always_inline int
INTERNAL_SYSCALL_nfsservctl_3 (int *err, int cmd, struct nfsctl_arg *argp,
			       union nfsctl_res *resp)
{
  lind_strace("nfsservctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_quotactl_4 (int *err, int cmd, const char *special, int id,
			     __caddr_t addr)
{
  lind_strace("quotactl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_query_module_5 (int *err, const char *name, int which,
				 void *buf, size_t bufsize, size_t *ret)
{
  lind_strace("query_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pause_0 (int *err)
{
  lind_strace("pause unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline long
INTERNAL_SYSCALL_personality_1 (int *err, unsigned long persona)
{
  lind_strace("personality unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pipe2_2 (int *err, int pipefd[2], int flags)
{
  lind_strace("pipe2 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pipe_1 (int *err, int pipefd[2])
{
  return INTERNAL_SYSCALL_pipe2_2 (err, pipefd, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_pivot_root_2 (int *err, const char *new_root,
			       const char *put_old)
{
  lind_strace("pivot_root unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_poll_3 (int *err, struct pollfd *fds, nfds_t nfds, int timeout)
{
  int count;
  *err = __nacl_irt_poll (fds, nfds, timeout, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_ppoll_5 (int *err, struct pollfd *fds, nfds_t nfds,
			  const struct timespec *timeout,
			  const sigset_t *sigmask, size_t sigset_size)
{
  int count;
  *err = __nacl_irt_ppoll (fds, nfds, timeout, sigmask, sigset_size, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_prctl_5 (int *err, int option, unsigned long arg2,
			  unsigned long arg3, unsigned long arg4,
			  unsigned long arg5)
{
  lind_strace("prctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pselect6_6 (int *err, int nfds, fd_set *readfds,
                             fd_set *writefds, fd_set *exceptfds,
                             const struct timeval *timeout,
                             void *sigmask)
{
  int count;
  *err = __nacl_irt_pselect (nfds, readfds, writefds, exceptfds, timeout,
                             sigmask, &count);
  return count;
}

__extern_always_inline long
INTERNAL_SYSCALL_ptrace_4 (int *err, enum __ptrace_request request, pid_t pid,
			   void *addr, void *data)
{
  lind_strace("ptrace unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_putmsg_4 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int flags)
{
  lind_strace("putmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_putpmsg_5 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int band, int flags)
{
  lind_strace("putpmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readahead_3 (int *err, int fd, __off64_t offset, size_t count)
{
  lind_strace("readahead unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readahead_4 (int *err, int fd,
			      __LONG_LONG_PAIR(long offset_high,
					       long offset_low), size_t count)
{
  __off64_t offset = ((__off64_t)offset_high) << 32 | offset_low;
  return INTERNAL_SYSCALL_readahead_3 (err, fd, offset, count);
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readv_3 (int *err, int fd, const
			  struct iovec *iov, int iovcnt)
{
  lind_strace("readv unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readlink_3 (int *err, const char *path,
			     char *buf, size_t bufsiz)
{
  lind_strace("readlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readlinkat_4 (int *err, int dirfd, const char *pathname,
			       char *buf, size_t bufsiz)
{
  lind_strace("readlinkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_reboot_4 (int *err, int magic1, int magic2, int cmd, void *arg)
{
  lind_strace("reboot unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_reboot_3 (int *err, int magic1, int magic2, int howto)
{
  return INTERNAL_SYSCALL_reboot_4 (err, magic1, magic2, howto, NULL);
}

__extern_always_inline int
INTERNAL_SYSCALL_remap_file_pages_5 (int *err, void *addr, size_t size,
				     int prot, ssize_t pgoff, int flags)
{
  lind_strace("remap_file_pages unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_removexattr_2 (int *err, const char *path, const char *name)
{
  lind_strace("removexattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rename_2 (int *err, const char *oldpath, const char *newpath)
{
  lind_strace("rename unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_renameat_4 (int *err, int olddfd, const char *oldname,
			     int newdfd, const char *newname)
{
  lind_strace("renameat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rmdir_1 (int *err, const char *pathname)
{
  *err = __nacl_irt_rmdir (pathname);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigpending_2 (int *err, sigset_t *set, size_t sigsetsize)
{
  lind_strace("rt_sigpending unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigprocmask_4 (int *err, int how, const sigset_t *set,
				   sigset_t *oldset, size_t sigsetsize)
{
  lind_strace("rt_sigprocmask unimplemented");
  *err = (0 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigqueueinfo_3 (int *err, pid_t pid, int sig,
				    siginfo_t *info)
{
  lind_strace("rt_sigqueueinfo unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigsuspend_2 (int *err, const sigset_t *mask,
				  size_t sigsetsize)
{
  lind_strace("rt_sigsuspend unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigtimedwait_4 (int *err, const sigset_t *set,
				    siginfo_t *info,
				    const struct timespec *timeout,
				    size_t sigsetsize)
{
  lind_strace("rt_sigtimedwait unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_getaffinity_3 (int *err, pid_t pid, size_t cpusetsize,
				      cpu_set_t *mask)
{
  lind_strace("sched_getaffinity unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_getparam_2 (int *err, pid_t pid,
				   struct sched_param *param)
{
  lind_strace("sched_getparam unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_get_priority_min_1 (int *err, int policy)
{
  lind_strace("sched_get_priority_min unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_get_priority_max_1 (int *err, int policy)
{
  lind_strace("sched_get_priority_max unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_getscheduler_1 (int *err, pid_t pid)
{
  lind_strace("sched_getscheduler unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_rr_get_interval_2 (int *err, pid_t pid,
					  struct timespec * tp)
{
  lind_strace("sched_rr_get_interval unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_setaffinity_3 (int *err, pid_t pid, size_t cpusetsize,
				      const cpu_set_t *mask)
{
  lind_strace("sched_setaffinity unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_setparam_2 (int *err, pid_t pid,
				   struct sched_param *param)
{
  lind_strace("sched_setparam unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_setscheduler_3 (int *err, pid_t pid, int policy,
				       const struct sched_param *param)
{
  lind_strace("sched_setscheduler unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

#ifdef __i386__
#define INTERNAL_SYSCALL_select_5 INTERNAL_SYSCALL__newselect_5
#endif
__extern_always_inline int
INTERNAL_SYSCALL_select_5 (int *err, int nfds, fd_set *readfds,
			   fd_set *writefds, fd_set *exceptfds,
			   const struct timeval *timeout)
{
  int count;
  *err = __nacl_irt_select (nfds, readfds, writefds, exceptfds, timeout, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_semctl_4 (int *err, int semid, int semnum, int cmd,
#ifdef _SEM_SEMUN_UNDEFINED
			   int semun)
#else
			   union semun semun)
#endif
{
  lind_strace("semctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semget_3 (int *err, key_t key, int nsems, int semflg)
{
  lind_strace("semget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semtimedop_4 (int *err, int semid, struct sembuf *sops,
			       unsigned nsops, struct timespec *timeout)
{
  lind_strace("semtimedop unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semop_3 (int *err, int semid, struct sembuf *sops,
			  unsigned nsops)
{
  return INTERNAL_SYSCALL_semtimedop_4 (err, semid, sops, nsops, NULL);
}

__extern_always_inline int
INTERNAL_SYSCALL_setdomainname_2 (int *err, const char *name, size_t len)
{
  lind_strace("setdomainname unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setfsgid_1 (int *err, gid_t gid)
{
  lind_strace("setfsgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setfsuid_1 (int *err, uid_t uid)
{
  lind_strace("setfsuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setgid_1 (int *err, gid_t gid)
{
  lind_strace("setgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setgroups_2 (int *err, int size, const gid_t *list)
{
  lind_strace("setgroups unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sethostname_2 (int *err, const char *name, size_t len)
{
  lind_strace("sethostname unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setitimer_3 (int *err, int which,
			      const struct itimerval *new_value,
			      struct itimerval *old_value)
{
  lind_strace("setitimer unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setpgid_2 (int *err, pid_t pid, pid_t pgid)
{
  lind_strace("setpgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setpriority_3 (int *err, int which, int who, int prio)
{
  lind_strace("setpriority unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setregid_2 (int *err, gid_t rgid, gid_t egid)
{
  lind_strace("setregid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setresgid_3 (int *err, gid_t rgid, gid_t egid, gid_t sgid)
{
  lind_strace("setresgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setresuid_3 (int *err, uid_t ruid, uid_t euid, uid_t suid)
{
  lind_strace("setresuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setreuid_2 (int *err, uid_t ruid, uid_t euid)
{
  lind_strace("setreuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_settimeofday_2 (int *err, const struct timeval *tv,
				 const struct timezone *tz)
{
  lind_strace("settimeofday unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_set_robust_list_2 (int *err, struct robust_list_head *head,
				    size_t len)
{
  lind_strace("set_robust_list unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_setsid_0 (int *err)
{
  lind_strace("setsid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setuid_1 (int *err, uid_t uid)
{
  lind_strace("setuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setxattr_5 (int *err, const char *path, const char *name,
			     const void *value, size_t size, int flags)
{
  lind_strace("setxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline void*
INTERNAL_SYSCALL_shmat_3 (int *err, int shmid, const void *shmaddr, int shmflg)
{
  lind_strace("shmat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shmctl_3 (int *err, int shmid, int cmd, struct shmid_ds *buf)
{
  lind_strace("shmctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shmdt_1 (int *err, const void *shmaddr)
{
  lind_strace("shmdt unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shmget_3 (int *err, key_t key, size_t size, int shmflg)
{
  lind_strace("shmget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sigaltstack_2 (int *err, const stack_t *ss, stack_t *oss)
{
  lind_strace("sigaltstack unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_signalfd4_4 (int *err, int fd, const sigset_t *mask,
			      size_t sigsetsize, int flags)
{
  lind_strace("signalfd4 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_signalfd_3 (int *err, int fd, const sigset_t *mask,
			     size_t sigsetsize)
{
  return INTERNAL_SYSCALL_signalfd4_4 (err, fd, mask, sigsetsize, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_socket_3 (int *err, int domain, int type, int protocol)
{
  int sd;
  *err = __nacl_irt_socket (domain, type, protocol, &sd);
  return sd;
}

__extern_always_inline int
INTERNAL_SYSCALL_accept_3 (int *err, int sockfd, struct sockaddr* addr,
                           socklen_t* addr_len)
{
  int sd;
  *err = __nacl_irt_accept (sockfd, addr, addr_len, &sd);
  return sd;
}

__extern_always_inline int
INTERNAL_SYSCALL_bind_3 (int *err, int sockfd, struct sockaddr* addr,
                         socklen_t addr_len)
{
  *err = __nacl_irt_bind (sockfd, addr, addr_len);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getpeername_3 (int *err, int sockfd, struct sockaddr* addr,
                                socklen_t* addr_len)
{
  *err = __nacl_irt_getpeername (sockfd, addr, addr_len);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getsockname_3 (int *err, int sockfd, struct sockaddr* addr,
                                socklen_t* addr_len)
{
  *err = __nacl_irt_getsockname (sockfd, addr, addr_len);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getsockopt_5 (int *err, int sockfd, int level, int optname,
                               void *optval, socklen_t *optlen)
{
  *err = __nacl_irt_getsockopt (sockfd, level, optname, optval, optlen);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setsockopt_5 (int *err, int sockfd, int level, int optname,
                               const void *optval, socklen_t optlen)
{
  *err = __nacl_irt_setsockopt (sockfd, level, optname, optval, optlen);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_listen_2 (int *err, int sockfd, int backlog)
{
  *err = __nacl_irt_listen (sockfd, backlog);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_connect_3 (int *err, int sockfd, struct sockaddr* addr,
                            socklen_t addr_len)
{
  *err = __nacl_irt_connect (sockfd, addr, addr_len);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_socketpair_4 (int *err, int domain, int type, int protocol,
                             int sv[2])
{
  *err = __nacl_irt_socketpair (domain, type, protocol, sv);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shutdown_2 (int *err, int sockfd, int how)
{
  *err = __nacl_irt_shutdown (sockfd, how);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_send_4 (int *err, int sockfd, const void *buf, size_t len, int flags)
{
  int ret;
  *err = __nacl_irt_send (sockfd, buf, len, flags, &ret);
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_sendto_6 (int *err, int sockfd, const void *buf, size_t len,
                           int flags, const struct sockaddr *dest_addr,
						   socklen_t addrlen)
{
  int ret;
  *err = __nacl_irt_sendto (sockfd, buf, len, flags, dest_addr, addrlen, &ret);
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_recv_4 (int *err, int sockfd, void *buf, size_t len, int flags)
{
  int ret;
  *err = __nacl_irt_recv (sockfd, buf, len, flags, &ret);
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_recvfrom_6 (int *err, int sockfd, void *buf, size_t len, int flags,
                           struct sockaddr *dest_addr, socklen_t *addrlen)
{
  int ret;
  *err = __nacl_irt_recvfrom (sockfd, buf, len, flags, dest_addr, addrlen, &ret);
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_sendmsg_3 (int *err, int sockfd, const struct msghdr *msg, int flags)
{
  int ret;
  *err = __nacl_irt_sendmsg (sockfd, msg, flags, &ret);
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_recvmsg_3 (int *err, int sockfd, struct msghdr *msg, int flags)
{
  int ret;
  *err = __nacl_irt_recvmsg (sockfd, msg, flags, &ret);
  return ret;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_splice_6 (int *err, int fd_in, loff_t *off_in, int fd_out,
			   loff_t *off_out, size_t len, unsigned int flags)
{
  lind_strace("splice unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_stime_1 (int *err, time_t *t)
{
  lind_strace("stime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_swapoff_1 (int *err, const char *path)
{
  lind_strace("swapoff unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_swapon_2 (int *err, const char *path, int swapflags)
{
  lind_strace("swapon unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_symlink_2 (int *err, const char *oldpath, const char *newpath)
{
  lind_strace("symlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_symlinkat_3 (int *err, const char *oldpath,
			      int newdirfd, const char *newpath)
{
  lind_strace("symlinkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sync_0 (int *err)
{
  lind_strace("sync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sync_file_range_6 (int *err, int fd,
				    __LONG_LONG_PAIR(long offset_high,
						     long offset_low),
				    __LONG_LONG_PAIR(long nbytes_high,
						     long nbytes_low),
				    unsigned int flags)
{
#if 0
  __off64_t offset = ((__off64_t)offset_high) << 32 | offset_low;
  __off64_t nbytes = ((__off64_t)nbytes_high) << 32 | nbytes_low;
#endif
  lind_strace("sync_file_range unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL__sysctl_1 (int *err, struct __sysctl_args *args)
{
  lind_strace("sysctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sysinfo_1 (int *err, struct sysinfo *info)
{
  lind_strace("sysinfo unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_tee_4 (int *err, int fd_in, int fd_out, size_t len,
			unsigned int flags)
{
  lind_strace("tee unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_syslog_3 (int *err, int type, char *bufp, int len)
{
  lind_strace("syslog unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_tgkill_3 (int *err, gid_t tgid, pid_t tid, int sig)
{
  lind_strace("tgkill unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_create_3 (int *err, clockid_t clockid,
				 struct sigevent *evp,
				 __kernel_timer_t *timerid)
{
  lind_strace("timer_create unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_delete_1 (int *err, __kernel_timer_t timerid)
{
  lind_strace("timer_delete unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_getoverrun_1 (int *err, __kernel_timer_t timerid)
{
  lind_strace("timer_getoverrun unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_gettime_2 (int *err, __kernel_timer_t timerid,
				  struct itimerspec *curr_value)
{
  lind_strace("timer_gettime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_settime_4 (int *err, __kernel_timer_t timerid, int flags,
				  const struct itimerspec *new_value,
				  struct itimerspec * old_value)
{
  lind_strace("timer_settime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timerfd_create_2 (int *err, int clockid, int flags)
{
  lind_strace("timerfd_create unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timerfd_gettime_2 (int *err, int fd,
				    struct itimerspec *curr_value)
{
  lind_strace("timerfd_gettime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timerfd_settime_4 (int *err, int fd, int flags,
				    const struct itimerspec *new_value,
				    struct itimerspec *old_value)
{
  lind_strace("timerfd_settime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline clock_t
INTERNAL_SYSCALL_times_1 (int *err, struct tms *buf)
{
  lind_strace("times unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_tkill_2 (int *err, pid_t tid, int sig)
{
  lind_strace("tkill unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline mode_t
INTERNAL_SYSCALL_umask_1 (int *err, mode_t mask)
{
  lind_strace("umask unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_umount2_2 (int *err, const char *target, int flags)
{
  lind_strace("umount2 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_umount_1 (int *err, const char *target)
{
  return INTERNAL_SYSCALL_umount2_2 (err, target, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_uname_1 (int *err, struct utsname *buf)
{
  //lind_strace("uname unimplemented");
  //*err = (38 /* ENOSYS */);
#define CPSTR(d, s) memcpy(d, s, sizeof(s))
  CPSTR(buf->sysname, "Linux");
  CPSTR(buf->nodename, "ubuntu");
  CPSTR(buf->release, "3.8.0-35-generic");
  CPSTR(buf->version, "#50-Ubuntu SMP Tue Dec 3 01:24:59 UTC 2013");
  CPSTR(buf->machine, "x86_64");
#undef CPSTR
  *err = 0;
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_unlink_1 (int *err, const char *pathname)
{
  lind_strace("unlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_unlinkat_3 (int *err, int dirfd, const char *pathname,
			     int flags)
{
  lind_strace("unlinkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_unshare_1 (int *err, int flags)
{
  lind_strace("unshare unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_uselib_1 (int *err, const char *library)
{
  lind_strace("uselib unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ustat_2 (int *err, dev_t dev, struct ustat *ubuf)
{
  lind_strace("ustat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_utime_2 (int *err, const char *filename,
		          const struct utimbuf *times)
{
  lind_strace("utime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_utimes_2 (int *err, const char *filename,
			   const struct timeval times[2])
{
  lind_strace("utimes unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_utimensat_4 (int *err, int dirfd, const char *pathname,
			      const struct timespec times[2], int flags)
{
  lind_strace("utimensat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_vhangup_0 (int *err)
{
  lind_strace("vhangup unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

#ifdef __i386__
__extern_always_inline int
INTERNAL_SYSCALL_vm86_2 (int *err, unsigned long fn,
			 struct vm86plus_struct *v86)
{
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_vm86old_1 (int *err, struct vm86_struct *info)
{
  *err = (38 /* ENOSYS */);
  return 0;
}
#endif

__extern_always_inline ssize_t
INTERNAL_SYSCALL_vmsplice_4 (int *err, int fd, const struct iovec *iov,
			     unsigned long nr_segs, unsigned int flags)
{
  lind_strace("vmsplice unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_wait3_3 (int *err, int *status, int options,
			  struct rusage *rusage)
{
  lind_strace("wait3 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_wait4_4 (int *err, pid_t pid, int *status, int options,
			  struct rusage *rusage)
{
  lind_strace("wait4 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_write_3 (int *err, int fd, const void *buf, size_t count)
{
  size_t nwrote;
  *err = __nacl_irt_write (fd, buf, count, &nwrote);
  return nwrote;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_writev_3 (int *err, int fd, const
			   struct iovec *iov, int iovcnt)
{
  lind_strace("writev unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

# ifdef __i386__
#  undef INTERNAL_SYSCALL_chown_3
#  undef INTERNAL_SYSCALL_fchown_3
#  undef INTERNAL_SYSCALL_getegid_0
#  undef INTERNAL_SYSCALL_geteuid_0
#  undef INTERNAL_SYSCALL_getgid_0
#  undef INTERNAL_SYSCALL_getgroups_2
#  undef INTERNAL_SYSCALL_getresgid_3
#  undef INTERNAL_SYSCALL_getresuid_3
#  undef INTERNAL_SYSCALL_getuid_0
#  undef INTERNAL_SYSCALL_lchown_3
#  undef INTERNAL_SYSCALL_setfsgid_1
#  undef INTERNAL_SYSCALL_setfsuid_1
#  undef INTERNAL_SYSCALL_setgid_1
#  undef INTERNAL_SYSCALL_setgroups_2
#  undef INTERNAL_SYSCALL_setregid_2
#  undef INTERNAL_SYSCALL_setresgid_3
#  undef INTERNAL_SYSCALL_setresuid_3
#  undef INTERNAL_SYSCALL_setreuid_2
#  undef INTERNAL_SYSCALL_setuid_1
# endif
#endif

#include_next <sysdep.h>

#if !defined(__ASSEMBLER__) && defined(THREAD_SELF) && defined(CLOCK_IDFIELD_SIZE)
#include <tls.h>

/*
 * We don't support redefinition of this function. We always use 30 bits
 * of the address of pthread structure as TID.
 */
__extern_always_inline pid_t
INTERNAL_SYSCALL_gettid_0 (int *err)
{
  *err = 0;
  /* Native Client does not have a notion of a thread ID, so we make
     one up.  This must be small enough to leave space for number
     identifying the clock.  Use CLOCK_IDFIELD_SIZE to guarantee
     that.  */
  return ((unsigned int) THREAD_SELF) >> CLOCK_IDFIELD_SIZE;
}

/* We can not return error code - this function is not supposed to fail.
   It should return pid (which is equal to tid for the main process).
   It's only ever called from main process so we just return TID.  */
__extern_always_inline int
INTERNAL_SYSCALL_set_tid_address_1 (int *err, volatile int *tidptr)
{
  return INTERNAL_SYSCALL_gettid_0 (err);
}
#endif

#undef INTERNAL_SYSCALL_DECL
# define INTERNAL_SYSCALL_DECL(err) int err

#undef INTERNAL_SYSCALL_ERRNO
# define INTERNAL_SYSCALL_ERRNO(val, err) (err)

#undef INTERNAL_SYSCALL_ERROR_P
# define INTERNAL_SYSCALL_ERROR_P(val, err) (err)

/*
 * Define a macro which expands inline into the wrapper code for an IRT call.
 */
# undef INLINE_SYSCALL
# define INLINE_SYSCALL(name, nr, args...) \
  ({									      \
    INTERNAL_SYSCALL_DECL (err);					      \
    unsigned long int resultvar = INTERNAL_SYSCALL (name, err, nr , ## args); \
    if (__builtin_expect (err, 0))					      \
      {									      \
	__set_errno (err);						      \
	resultvar = (unsigned long int) -1;				      \
      }									      \
    (long int) resultvar; })

#undef INTERNAL_VSYSCALL
# define INTERNAL_VSYSCALL INTERNAL_SYSCALL

/*
 * Nacl uses AT_SYSINFO for IRT. Thus sysinfo can never be usable
 * and it's safe to disable this machinery.
 */
#undef NEED_DL_SYSINFO

#ifndef __x86_64__
#undef	PSEUDO
#define	PSEUDO(name, syscall_name, args)	\
  .text;					\
  ENTRY (name)					\
    mov $-38, %eax;				\
  L(pseudo_end):				\
    NACLRET

#undef	PSEUDO_END
#define	PSEUDO_END(name)			\
    SYSCALL_ERROR_HANDLER			\
  END (name)

#undef  PSEUDO_NOERRNO
#define PSEUDO_NOERRNO(name, syscall_name, args)\
  .text;					\
  ENTRY (name)					\
    mov $-38, %eax

#undef  PSEUDO_END_NOERRNO
#define PSEUDO_END_NOERRNO(name)		\
  END (name)

#undef ret_NOERRNO
#define ret_NOERRNO NACLRET

/* The function has to return the error code.  */
#undef  PSEUDO_ERRVAL
#define PSEUDO_ERRVAL(name, syscall_name, args)	\
  .text;					\
  ENTRY (name)					\
    mov $38, %eax

#undef  PSEUDO_END_ERRVAL
#define PSEUDO_END_ERRVAL(name)			\
  END (name)

#undef SYSCALL_ERROR_HANDLER_TLS_STORE
#define SYSCALL_ERROR_HANDLER_TLS_STORE(src, destoff)	\
  movl %gs:0, %eax;					\
  movl src, (%eax,destoff)

#endif
#endif
