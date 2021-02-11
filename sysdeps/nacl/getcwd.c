#include <unistd.h>
#include <irt_syscalls.h>

char* __getcwd(char* buf, size_t size) {
    return __nacl_irt_getcwd(buf, size);
}

weak_alias (__getcwd, getcwd)
