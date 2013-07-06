#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <nacl_syscalls.h>

#include <lind_syscalls.h>
#include <lind_strace.h>
#include <lind_util.h>
#include <component.h>

#include <nacl_stat.h>


#define MAX_FILENAME_LENGTH 512

#define FMT_INT "<i"
#define FMT_UINT "<I"
#define FMT_LONG "<q"
#define FMT_ULONG "<Q"
#define FMT_STR(len) #len "s"


/* struct lind_open_rpc_s { */
/*   int flags; */
/*   int mode; */
/*   size_t filename_len; */
/* }; */

/* struct lind_rw_rpc_s { */
/*   int handle; */
/*   int size; */
/* }; */


/* struct lind_lseek_rpc_s { */
/*   int fd; */
/*   int whence; */
/*   off_t offset; */

/* }; */

struct lind_fd_rpc_s {
    int fd;
};



/** Send an open request to the lind server.
 filename is the string path to the file to open*/
/* int lind_open_rpc (const char * filename, int flags, int mode) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */

/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   struct lind_open_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_open_rpc_s)); */
  
/*   /\* setup arguments *\/ */
/*   int return_code = -1; */
/*   args.flags = flags; */
/*   args.mode = mode; */
/*   size_t filename_len = strlen(filename); */
/*   args.filename_len = filename_len; */
/*   size_t filename_siz = filename_len + 1;  */
 
/*   const char * filename_len_str = nacl_itoa(args.filename_len); */
/*   /\* <i<i<i(STRLEN)s *\/ */
/*   request.format = combine(5, FMT_INT, FMT_INT, FMT_INT, filename_len_str, "s"); */
/*   request.call_number = NACL_sys_open; */

/*   request.message.len = sizeof(struct lind_open_rpc_s); */
/*   request.message.body = &args; */
  
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, filename, filename_siz); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */


/*   return return_code; */

/* } */


/* int lind_read_rpc(int handle, int size, void * where_to) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_rw_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_rw_rpc_s)); */

/*   int return_code = -1; */
/*   args.handle = handle; */
/*   args.size = size; */

/*   request.call_number = NACL_sys_read; */
/*   request.format = "<i<i"; */

/*   request.message.len = sizeof(struct lind_rw_rpc_s); */
/*   request.message.body = &args; */
 

/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) <= size); */
/*     memcpy( where_to, reply.contents, return_code); */
/*   } */

/*   return return_code; */

/* } */



/* struct lind_fxstat_rpc_s { */
/*   int fd; */
/*   int vers; */
/* }; */


/* int lind_fxstat_rpc(int fd, int vers, struct stat *buf) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_fxstat_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_fxstat_rpc_s)); */

/*   int return_code = -1; */
/*   args.fd = fd; */
/*   args.vers = vers; */

/*   request.call_number = NACL_sys_fstat; */
/*   request.format = FMT_INT FMT_INT; */

/*   request.message.len = sizeof(struct lind_fxstat_rpc_s); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) == sizeof(struct stat)); */
/*     memcpy(buf, reply.contents, sizeof(struct stat)); */
/*   } */

/*   return return_code; */

/* } */



/* lseek system call.   Has three arguments (int fd, off_t offset, int whence)
 * returns a off_t (__SQUAD_TYPE) which is a 64 bit signed type. */
/* int lind_lseek_rpc(int fd, off_t offset, int whence, off_t* ret_loc) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */

/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   struct lind_lseek_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_lseek_rpc_s)); */

/*   int return_code = -1; */
/*   args.fd = fd; */
/*   args.offset = offset; */
/*   args.whence = whence; */

/*   request.call_number = NACL_sys_lseek; */
/*   /\* int fd, int whence, long (as string) *\/ */
/*   request.format = FMT_INT FMT_INT FMT_LONG; */

/*   request.message.len = sizeof( struct lind_lseek_rpc_s ); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) == sizeof(off_t)); */
/*     memcpy(ret_loc, reply.contents, CONTENTS_SIZ(reply)); */

/*   } */
  
/*   return return_code; */

/* } */


/* int lind_close_rpc(int fd) { */
/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_fd_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_fd_rpc_s)); */

/*   int return_code = -1; */
/*   args.fd = fd; */

/*   request.call_number = NACL_sys_close; */
/*   request.format = "<i"; */

/*   request.message.len = sizeof(struct lind_fd_rpc_s); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */

/* ssize_t lind_write_rpc(int desc, void const *buf, size_t count) { */
/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_rw_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_rw_rpc_s)); */
/*   int return_code = -1; */
/*   args.handle = desc; */
/*   args.size = count; */
/*   request.call_number = NACL_sys_write; */
/*   request.format = concat(concat("<i<I", nacl_itoa(count-1)),"s");  */
/*   request.message.len = sizeof(struct lind_rw_rpc_s); */
/*   request.message.body = &args; */
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, buf, count); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */


/*   return return_code; */
/* } */


struct lind_ioctl_rpc_s {
  int fd;
  unsigned long int request;
};



//int lind_ioctl_rpc (int fd, unsigned long int ioctl_request, ...) {
//
//  lind_request request;
//  memset(&request, 0, sizeof(request));
//  lind_reply reply;
//  memset(&reply, 0, sizeof(reply));
//  struct lind_ioctl_rpc_s args;
//  memset(&args, 0, sizeof(struct lind_ioctl_rpc_s));
//
//  int return_code = -1;
//  args.fd = fd;
//  args.request = ioctl_request;
//
//  request.call_number = NACL_sys_ioctl;
//  request.format = FMT_INT FMT_ULONG;
//
//  request.message.len = sizeof(struct lind_ioctl_rpc_s);
//  request.message.body = &args;
//
//  nacl_rpc_syscall_proxy(&request, &reply, 0);
//
//  /* on error return negative so we can set ERRNO. */
//  if (reply.is_error) {
//    return_code = reply.return_code * -1;
//  } else {
//    return_code = reply.return_code;
//  }
//
//  return return_code;
//
//}


/* struct lind_access_rpc_s { */
/*   int type; */
/* }; */



/* /\** Send access call to RePy via lind RPC.  file is the name of the file to check */
/*  type is the access mode ( W_OK, R_OK, X_OK or an | of them). *\/ */
/* int lind_access_rpc (const char * file, int type) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_access_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_access_rpc_s)); */

/*   int return_code = -1; */
/*   args.type = type; */
/*   request.call_number = NACL_sys_access; */


/*   /\* Now build the format string which is <iLENGTHs *\/ */
/*   size_t file_name_length = strlen(file); */
/*   size_t file_name_size = file_name_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(file_name_length); */
/*   const char * str_len_s = concat(str_len,"s"); */
/*   request.format = concat(FMT_INT, str_len_s); */
/*   free( (void*) str_len); */
/*   free( (void*) str_len_s); */

/*   request.message.len = sizeof( struct lind_access_rpc_s ); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, file, file_name_size); */

/*   /\* concat malloced this earlier. *\/ */
/*   free( (void*)request.format ); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


/** Send unlink call to RePy via lind RPC.  Name is a path */
/* int lind_unlink_rpc (const char * name) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
  
/*   int return_code = -1; */
/*   request.call_number = NACL_sys_unlink; */

/*   /\* Now build the format string which is LENGTHs *\/ */
/*   size_t file_name_length = strlen(name); */
/*   size_t file_name_size = file_name_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(file_name_length); */
/*   const char * str_len_s = combine(2, str_len, "s");  */
/*   request.format = str_len_s; */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, name, file_name_size); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


/* /\** Send link call to RePy via lind RPC.  old name and new name are file paths*\/ */
/* int lind_link_rpc (const char * from, const char * to) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
  
/*   int return_code = -1; */
  
/*   request.call_number = NACL_sys_link; */

/*   /\* Now build the format string which is LENGTHsLENGTHs *\/ */
/*   size_t from_length = strlen(from); */
/*   size_t from_size = from_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(from_length); */

/*   size_t to_length = strlen(to); */
/*   size_t to_size = to_length + 1; /\* size in bytes *\/ */
/*   const char * new_str_len = nacl_itoa(to_length); */


/*   request.format = combine(4, str_len, "s", new_str_len, "s"); */
/*   /\* free( (void*) str_len); *\/ */
/*   /\* free( (void*) str_len_s); *\/ */
/*   /\* free( (void*) new_str_len_s); *\/ */
/*   /\* free( (void*) new_str_len); *\/ */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 2, from, from_size, to, to_size); */

/*   /\* concat malloced this earlier. *\/ */
/*   /\* free( (void*)request.format ); *\/ */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


/* /\** Send chdir call to RePy via lind RPC.  Name is a path *\/ */
/* int lind_chdir_rpc (const char * name) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   int return_code = -1; */
/*   request.call_number = NACL_sys_chdir; */

/*   /\* Now build the format string which is LENGTHs *\/ */
/*   size_t file_name_length = strlen(name); */
/*   size_t file_name_size = file_name_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(file_name_length); */
/*   const char * str_len_s = combine(2, str_len, "s");  */
/*   request.format = str_len_s; */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, name, file_name_size); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */

/* struct lind_mkdir_rpc_s { */
/*   mode_t mode; */
/* }; */


/* /\** Send mkdir call to RePy via rind RPC.  Path is a path *\/ */
/* int lind_mkdir_rpc (const char * path, mode_t mode) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   struct lind_mkdir_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_mkdir_rpc_s)); */


/*   int return_code = -1; */
/*   request.call_number = NACL_sys_mkdir; */
  
/*   args.mode = mode; */

/*   /\* Now build the format string which is LENGTHs *\/ */
/*   size_t file_path_length = strlen(path); */
/*   size_t file_path_size = file_path_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(file_path_length); */
/*   const char * str_len_s = combine(3, FMT_INT, str_len, "s");  */
/*   request.format = str_len_s; */

/*   request.message.len = sizeof(args); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, path, file_path_size); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */
/* } */


/* /\** Send rmdir call to RePy via Lind RPC.  Path is a path *\/ */
/* int lind_rmdir_rpc (const char * path) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
  
/*   int return_code = -1; */
/*   request.call_number = NACL_sys_rmdir; */

/*   /\* Now build the format string which is LENGTHs *\/ */
/*   size_t file_path_length = strlen(path); */
/*   size_t file_path_size = file_path_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(file_path_length); */
/*   const char * str_len_s = combine(2, str_len, "s");  */
/*   request.format = str_len_s; */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, path, file_path_size); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


/** Send noop call to RePy via lind RPC.  Path is a path */
/* int lind_noop_rpc (void) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
  
/*   int return_code = -1; */
/*   request.call_number = NACL_sys_null; */
/*   request.format = (char*) ""; */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


/** Send getpid call to RePy via lind RPC.  Path is a path */
/* int lind_getpid_rpc (pid_t* buffer) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
  
/*   int return_code = -1; */
/*   request.call_number = NACL_sys_getpid; */
/*   request.format = (char*) ""; */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert(CONTENTS_SIZ(reply) == sizeof(pid_t)); */
/*     memcpy(buffer, reply.contents, sizeof(pid_t)); */
/*   } */
  
/*   return return_code; */

/* } */

/* struct lind_xstat_rpc_s { */
/*   int version; */
/* }; */


/* int lind_xstat_rpc (int version, const char *path, struct stat *buf) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */

/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   struct lind_xstat_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_xstat_rpc_s)); */
  
/*   /\* setup arguments *\/ */
/*   int return_code = -1; */
/*   args.version = version; */
/*   size_t path_len = strlen(path); */
/*   size_t path_siz = path_len + 1;  */
 
/*   const char * path_len_str = nacl_itoa(path_len); */
/*   /\* <i(STRLEN)s *\/ */
/*   request.format = combine(3, FMT_INT, path_len_str, "s"); */
/*   request.call_number = NACL_sys_xstat; */

/*   request.message.len = sizeof(struct lind_xstat_rpc_s); */
/*   request.message.body = &args; */
  
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, path, path_siz); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) == sizeof(struct stat)); */
/*     memcpy(buf, reply.contents, CONTENTS_SIZ(reply)); */
/*   } */

/*   return return_code; */
/* } */


/* struct lind_getdents_rpc_s { */
/*   int fd; */
/*   size_t nbytes; */
/* }; */

/* /\** For now we exclude basep. */
/*  *\/ */
/* ssize_t lind_getdents_rpc (int fd, char *buf, size_t nbytes) { */

/*  lind_request request; */
/*   memset(&request, 0, sizeof(request)); */

/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   struct lind_getdents_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_getdents_rpc_s)); */
  
/*   /\* setup arguments *\/ */
/*   int return_code = -1; */
/*   args.fd = fd; */
/*   args.nbytes = nbytes; */
 
/*   /\* <i(STRLEN)s *\/ */
/*   request.format = FMT_INT FMT_INT; */
/*   request.call_number = NACL_sys_getdents; */

/*   request.message.len = sizeof(struct lind_getdents_rpc_s); */
/*   request.message.body = &args; */
  
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) <= nbytes); */
/*     memcpy(buf, reply.contents, CONTENTS_SIZ(reply)); */
/*   } */

/*   return return_code; */

/* } */


#define MIN(X,Y) ( (X) < (Y) ? (X) : (Y))

int lind_comp_rpc(int request_num, int nbytes, void *buf) {
  int return_code = -1;

  /* lind_request request; */
  /* memset(&request, 0, sizeof(request)); */

  /* lind_reply reply; */
  /* memset(&reply, 0, sizeof(reply)); */

  /* switch(request_num) { */

  /*   case LIND_CIA_IOCTL: */
  /*     request.format = FMT_INT FMT_INT; */
  /*     request.call_number = NACL_sys_comp_cia; */
  /*     request.message.len = nbytes; */
  /*     request.message.body = buf; */
  /*     nacl_rpc_syscall_proxy(&request, &reply, 0); */
  /*     break; */

  /*   case LIND_CALL_IOCTL:; */
  /*     struct call_s * call_args = (struct call_s *) buf; */
  /*     /\* string part of struct is everything execpt the first 2 ints, and the null terminator. *\/ */
  /*     request.format = combine(3, FMT_INT FMT_UINT FMT_UINT, nacl_itoa((int)(call_args->siz)-1), "s"); */
  /*     request.call_number = NACL_sys_comp_call; */
  /*     request.message.len = sizeof(struct call_s); */
  /*     request.message.body = buf; */
  /*     nacl_rpc_syscall_proxy(&request, &reply, 1, call_args->message, call_args->siz); */
  /*     break; */

  /*   case LIND_ACCEPT_IOCTL: */
  /*     request.format = FMT_INT FMT_INT FMT_INT; */
  /*     request.call_number = NACL_sys_comp_accept; */
  /*     request.message.len = nbytes; */
  /*     request.message.body = buf; */
  /*     nacl_rpc_syscall_proxy(&request, &reply, 0); */
  /*     break; */
  /* } */

  /* /\* on error return negative so we can set ERRNO. *\/   */
  /* if (reply.is_error) { */
  /*   return_code = reply.return_code * -1; */
  /* } else { */
  /*   return_code = reply.return_code; */

  /*   if (request_num == LIND_ACCEPT_IOCTL) { */
      
  /*     struct comp_accept_s * accept_args = (struct comp_accept_s *) buf; */
  /*     int content_size = return_code; */
  /*     int buff_size = accept_args->max; */
  /*     int min_size = MIN(content_size, buff_size); */
  /*     assert( CONTENTS_SIZ(reply) <= min_size); */
  /*     memcpy(accept_args->buff, reply.contents, min_size); */
  /*   } */
  /* } */
  
  return return_code;
}


/* int lind_fstatfs_rpc (int fd, struct statfs *buf) { */
/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */

/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   struct lind_fd_rpc_s args; */
/*   memset(&args, 0, sizeof(args)); */
  
/*   /\* setup arguments *\/ */
/*   int return_code = -1; */
/*   args.fd = fd; */

/*   request.format = FMT_INT; */
/*   request.call_number = NACL_sys_fstatfs; */

/*   request.message.len = sizeof(struct lind_fd_rpc_s); */
/*   request.message.body = &args; */
  
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) == sizeof(struct statfs)); */
/*     memcpy(buf, reply.contents, CONTENTS_SIZ(reply)); */
/*   } */

/*   return return_code; */
/* } */


/* int lind_dup_rpc(int oldfd) { */
/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_fd_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_fd_rpc_s)); */

/*   int return_code = -1; */
/*   args.fd = oldfd; */

/*   request.call_number = NACL_sys_dup; */
/*   request.format = "<i"; */

/*   request.message.len = sizeof(struct lind_fd_rpc_s); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


/* struct lind_dup2_rpc_s { */
/*   int fd; */
/*   int fd2; */
/* }; */



/* int lind_dup2_rpc(int oldfd, int newfd) { */
/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */
/*   struct lind_dup2_rpc_s args; */
/*   memset(&args, 0, sizeof(struct lind_dup2_rpc_s)); */

/*   int return_code = -1; */
/*   args.fd = oldfd; */
/*   args.fd2 = newfd; */

/*   request.call_number = NACL_sys_dup2; */
/*   request.format = FMT_INT FMT_INT; */

/*   request.message.len = sizeof(struct lind_dup2_rpc_s); */
/*   request.message.body = &args; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 0); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*   } */
  
/*   return return_code; */

/* } */


struct lind_fcntl_rpc_s {
  int fd;
  int cmd;
};



//int lind_fcntl_noop_rpc (int fd, int cmd)  {
//
//  lind_request request;
//  memset(&request, 0, sizeof(request));
//  lind_reply reply;
//  memset(&reply, 0, sizeof(reply));
//  struct lind_fcntl_rpc_s args;
//  memset(&args, 0, sizeof(struct lind_fcntl_rpc_s));
//
//  int return_code = -1;
//  args.fd = fd;
//  args.cmd = cmd;
//
//  request.call_number = LIND_safe_fs_fcntl;
//  request.format = FMT_INT FMT_INT;
//
//  request.message.len = sizeof(struct lind_fcntl_rpc_s);
//  request.message.body = &args;
//
//  nacl_rpc_syscall_proxy(&request, &reply, 0);
//
//  /* on error return negative so we can set ERRNO. */
//  if (reply.is_error) {
//    return_code = reply.return_code * -1;
//  } else {
//    return_code = reply.return_code;
//  }
//
//  return return_code;
//
//}

struct lind_fcntl_op_rpc_s {
  int fd;
  int cmd;
  long set_op;
};


//int lind_fcntl_op_rpc (int fd, int cmd, long set_op)  {
//
//  lind_request request;
//  memset(&request, 0, sizeof(request));
//  lind_reply reply;
//  memset(&reply, 0, sizeof(reply));
//  struct lind_fcntl_op_rpc_s args;
//  memset(&args, 0, sizeof(struct lind_fcntl_op_rpc_s));
//
//  int return_code = -1;
//  args.fd = fd;
//  args.cmd = cmd;
//  args.set_op = set_op;
//
//  request.call_number = LIND_safe_fs_fcntl;
//  request.format = FMT_INT FMT_INT FMT_LONG;
//
//  request.message.len = sizeof(struct lind_fcntl_op_rpc_s);
//  request.message.body = &args;
//
//  nacl_rpc_syscall_proxy(&request, &reply, 0);
//
//  /* on error return negative so we can set ERRNO. */
//  if (reply.is_error) {
//    return_code = reply.return_code * -1;
//  } else {
//    return_code = reply.return_code;
//  }
//  return return_code;
//}

//int lind_fcntl_rpc (int fd, int cmd, long set_op)  {
//  /* We break this one up to send with and without the argument. */
//  if (cmd == F_GETFD || cmd == F_GETFL || cmd == F_GETOWN ) {
//    /* these commands don't have an arg */
//    return lind_fcntl_noop_rpc(fd, cmd);
//
//  } else if (cmd == F_SETFD || cmd == F_SETFL || cmd == F_SETOWN ) {
//    /* These commands have a single long arg */
//    return lind_fcntl_op_rpc(fd, cmd, set_op);
//  } else {
//    return -1;
//  }
//
//}


/* int lind_statfs_rpc (const char * path, struct statfs *buf) { */

/*   lind_request request; */
/*   memset(&request, 0, sizeof(request)); */
/*   lind_reply reply; */
/*   memset(&reply, 0, sizeof(reply)); */

/*   int return_code = -1; */
/*   request.call_number = NACL_sys_statfs; */

/*   /\* Now build the format string which is LENGTHs *\/ */
/*   size_t file_name_length = strlen(path); */
/*   size_t file_name_size = file_name_length + 1; /\* size in bytes *\/ */
/*   const char * str_len = nacl_itoa(file_name_length); */
/*   const char * str_len_s = combine(2, str_len, "s");  */
/*   request.format = str_len_s; */

/*   request.message.len = 0; */
/*   request.message.body = NULL; */
 
/*   nacl_rpc_syscall_proxy(&request, &reply, 1, path, file_name_size); */

/*   /\* on error return negative so we can set ERRNO. *\/   */
/*   if (reply.is_error) { */
/*     return_code = reply.return_code * -1; */
/*   } else { */
/*     return_code = reply.return_code; */
/*     assert( CONTENTS_SIZ(reply) == sizeof(struct statfs)); */
/*     memcpy(buf, reply.contents, CONTENTS_SIZ(reply)); */
/*   } */
  
/*   return return_code; */

/* } */




typedef enum _LindArgType {AT_INT, AT_STRING, AT_STRING_OPTIONAL, AT_DATA, AT_DATA_OPTIONAL} LindArgType;

typedef struct _LindArg
{
    LindArgType arg_type;
    uint64_t ptr;
    uint64_t len;
} LindArg;

int lind_access (int version, const char *file)
{
    LindArg in_args[2] = {{AT_INT, version, 0}, {AT_STRING, (uintptr_t)file, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_access, 2, in_args, 0, NULL);
}

int lind_unlink (const char *name)
{
    LindArg in_args[1] = {{AT_STRING,(uintptr_t) name, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_unlink, 1, in_args, 0, NULL);
}

int lind_link (const char *from, const char *to)
{
    LindArg in_args[2] = {{AT_STRING, (uintptr_t)from, 0}, {AT_STRING, (uintptr_t)to, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_link, 2, in_args, 0, NULL);
}

int lind_chdir (const char *name)
{
    LindArg in_args[1] = {{AT_STRING, (uintptr_t)name, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_chdir, 1, in_args, 0, NULL);
}

int lind_mkdir (int mode, const char *path)
{
    LindArg in_args[2] = {{AT_INT, mode, 0}, {AT_STRING, (uintptr_t)path, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_mkdir, 2, in_args, 0, NULL);
}

int lind_rmdir (const char *path)
{
    LindArg in_args[1] = {{AT_STRING, (uintptr_t)path, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_xstat, 1, in_args, 0, NULL);
}

int lind_xstat (int version, const char *path, struct stat *buf)
{
    LindArg in_args[2] = {{AT_INT, version, 0}, {AT_STRING, (uintptr_t)path, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(struct stat)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_xstat, 2, in_args, 1, out_args);
}

int lind_open (int flags, int mode, const char *path)
{
    LindArg in_args[3] = {{AT_INT, flags, 0}, {AT_INT, mode, 0}, {AT_STRING, (uintptr_t)path, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_open, 3, in_args, 0, NULL);
}

int lind_close (int fd)
{
    LindArg in_args[1] = {{AT_INT, fd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_close, 1, in_args, 0, NULL);
}

int lind_read (int fd, int size, void *buf)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, size, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, size}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_read, 2, in_args, 1, out_args);
}

int lind_write (int fd, size_t count, const void *buf)
{
    LindArg in_args[3] = {{AT_INT, fd, 0}, {AT_INT, count, 0}, {AT_DATA, (uintptr_t)buf, count}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_write, 3, in_args, 0, NULL);
}

int lind_lseek (off_t offset, int fd, int whence, off_t * ret)
{
    LindArg in_args[3] = {{AT_INT, offset, 0}, {AT_INT, fd, 0}, {AT_INT, whence, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)ret, sizeof(off_t)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_lseek, 3, in_args, 1, out_args);
}

int lind_fxstat (int fd, int version, struct stat *buf)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, version, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(struct stat)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_fxstat, 2, in_args, 1, out_args);
}

int lind_fstatfs (int fd, struct statfs *buf)
{
    LindArg in_args[1] = {{AT_INT, fd, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(struct statfs)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_fstatfs, 1, in_args, 1, out_args);
}

int lind_statfs (const char *path, struct statfs *buf)
{
    LindArg in_args[1] = {{AT_STRING, (uintptr_t)path, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(struct statfs)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_statfs, 1, in_args, 1, out_args);
}

int lind_noop (void)
{
    return NACL_SYSCALL(lind_api)(LIND_debug_noop, 0, NULL, 0, NULL);
}

int lind_getpid (pid_t* buf)
{
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(pid_t)}};
    return NACL_SYSCALL(lind_api)(LIND_sys_getpid, 0, NULL, 1, out_args);
}

int lind_dup (int oldfd)
{
    LindArg in_args[1] = {{AT_INT, oldfd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_dup, 2, in_args, 0, NULL);
}

int lind_dup2 (int oldfd, int newfd)
{
    LindArg in_args[2] = {{AT_INT, oldfd, 0}, {AT_INT, newfd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_dup2, 2, in_args, 0, NULL);
}

int lind_getdents (int fd, size_t nbytes, char *buf)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, nbytes, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, nbytes}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_getdents, 2, in_args, 1, out_args);
}

int lind_fcntl_get (int fd, int cmd)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, cmd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_fcntl, 2, in_args, 0, NULL);
}

int lind_fcntl_set (int fd, int cmd, long set_op)
{
    LindArg in_args[3] = {{AT_INT, fd, 0}, {AT_INT, cmd, 0}, {AT_INT, set_op, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_fcntl, 3, in_args, 0, NULL);
}

int lind_socket (int domain, int type, int protocol)
{
    LindArg in_args[3] = {{AT_INT, domain, 0}, {AT_INT, type, 0}, {AT_INT, protocol, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_socket, 3, in_args, 0, NULL);
}

int lind_bind (int sockfd, socklen_t addrlen, const struct sockaddr *addr)
{
    LindArg in_args[3] = {{AT_INT, sockfd, 0}, {AT_INT, addrlen, 0}, {AT_DATA, (uintptr_t)addr, addrlen}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_send, 3, in_args, 0, NULL);
}

int lind_send (int sockfd, size_t len, int flags, const void *buf)
{
    LindArg in_args[4] = {{AT_INT, sockfd, 0}, {AT_INT, len, 0}, {AT_INT, flags, 0}, {AT_DATA, (uintptr_t)buf, len}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_send, 4, in_args, 0, NULL);
}

int lind_recv (int sockfd, size_t len, int flags, void *buf)
{
    LindArg in_args[3] = {{AT_INT, sockfd, 0}, {AT_INT, len, 0}, {AT_INT, flags, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, len}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_recv, 3, in_args, 1, out_args);
}

int lind_connect (int sockfd, socklen_t addrlen, const struct sockaddr *src_addr)
{
    LindArg in_args[3] = {{AT_INT, sockfd, 0}, {AT_INT, addrlen, 0}, {AT_DATA, (uintptr_t)src_addr, addrlen}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_connect, 3, in_args, 0, NULL);
}

int lind_listen (int sockfd, int backlog)
{
    LindArg in_args[2] = {{AT_INT, sockfd, 0}, {AT_INT, backlog, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_listen, 2, in_args, 0, NULL);
}

int lind_sendto (int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in *dest_addr, const void *buf)
{
    return 0;
}

int lind_accept (int sockfd, socklen_t addrlen)
{
    LindArg in_args[2] = {{AT_INT, sockfd, 0}, {AT_INT, addrlen, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_accept, 2, in_args, 0, NULL);
}

int lind_getpeername (int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t * addrlen_out)
{
    return 0;
}

int lind_setsockopt (int sockfd, int level, int optname, socklen_t optlen, const void *optval)
{
    LindArg in_args[5] = {{AT_INT, sockfd, 0}, {AT_INT, level, 0}, {AT_INT, optname, 0}, {AT_INT, optlen, 0}, {AT_DATA, (uintptr_t)optval, optlen}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_setsockopt, 4, in_args, 0, NULL);
}

int lind_getsockopt (int sockfd, int level, int optname, socklen_t optlen, void *optval)
{
    LindArg in_args[4] = {{AT_INT, sockfd, 0}, {AT_INT, level, 0}, {AT_INT, optname, 0}, {AT_INT, optlen, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)optval, optlen}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_getsockopt, 4, in_args, 1, out_args);
}

int lind_shutdown (int sockfd, int how)
{
    LindArg in_args[2] = {{AT_INT, sockfd, 0}, {AT_INT, how, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_shutdown, 2, in_args, 0, NULL);
}

int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout, struct select_results *result)
{
    LindArg in_args[5] = {{AT_INT, nfds, 0}, {AT_DATA_OPTIONAL, (uintptr_t)readfds, sizeof(fd_set)},
            {AT_DATA_OPTIONAL, (uintptr_t)writefds, sizeof(fd_set)}, {AT_DATA_OPTIONAL, (uintptr_t)exceptfds, sizeof(fd_set)},
            {AT_DATA_OPTIONAL, (uintptr_t)timeout, sizeof(struct timeval)}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)result, sizeof(struct select_results)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_select, 5, in_args, 1, out_args);
}

int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs)
{
    LindArg in_args[1] = {{AT_INT, ifaddrs_buf_siz, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)ifaddrs, ifaddrs_buf_siz}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_getifaddrs, 1, in_args, 1, out_args);
}

int lind_recvfrom (int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t * addrlen_out, void *buf, struct sockaddr *src_addr)
{
    LindArg in_args[4] = {{AT_INT, sockfd, 0}, {AT_INT, len, 0}, {AT_INT, flags, 0}, {AT_INT, addrlen, 0}};
    LindArg out_args[3] = {{AT_DATA, (uintptr_t)addrlen_out, sizeof(socklen_t)}, {AT_DATA, (uintptr_t)buf, sizeof(len)}, {AT_DATA, (uintptr_t)src_addr, sizeof(addrlen)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_recvfrom, 4, in_args, 3, out_args);
}

int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out)
{
    LindArg in_args[3] = {{AT_INT, nfds, 0}, {AT_INT, timeout, 0}, {AT_DATA, (uintptr_t)fds_in, sizeof(struct pollfd)*nfds}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)fds_out, sizeof(struct pollfd)*nfds}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_poll, 3, in_args, 1, out_args);
}

int lind_socketpair (int domain, int type, int protocol, int *fds)
{
    LindArg in_args[3] = {{AT_INT, domain, 0}, {AT_INT, type, 0}, {AT_INT, protocol, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)fds, sizeof(int)*2}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_socketpair, 3, in_args, 1, out_args);
}

int lind_getuid (uid_t * buf)
{
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(uid_t)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_sys_getuid, 0, NULL, 1, out_args);
}

int lind_geteuid (uid_t * buf)
{
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(uid_t)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_sys_geteuid, 0, NULL, 1, out_args);
}

int lind_getgid (gid_t * buf)
{
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(gid_t)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_sys_getgid, 0, NULL, 1, out_args);
}

int lind_getegid (gid_t * buf)
{
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, sizeof(gid_t)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_sys_getegid, 0, NULL, 1, out_args);
}

int lind_flock (int fd, int operation)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, operation, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_flock, 2, in_args, 0, NULL);
}

int lind_strace (char* str)
{
    LindArg in_args[1] = {{AT_STRING, (uintptr_t)str, 0}};
    return NACL_SYSCALL(lind_api)(LIND_debug_trace, 1, in_args, 0, NULL);
}
