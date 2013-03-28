
rtld-installed-name = $(patsubst %.$(NACL_FAKE_SONAME),%.1,$(ld.so-version))

ifeq ($(subdir),io)
sysdep_routines += lind_rpc nacl_util lind_syscalls lind_rpc_gen lindlock
endif

# ifeq ($(subdir),socket)
# sysdep_routines += socket
# endif



# Remove libpthread.so's version of a function that is also provided
# by libc.so.
libpthread-routines := $(filter-out pt-vfork,$(libpthread-routines))

# In case of NaCl any program which wants to call syscalls must be linked with
# ld.so explicitly.
LDLIBS-nscd += $(elfobjdir)/ld.so
