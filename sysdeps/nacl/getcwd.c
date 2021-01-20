#include <unistd.h>
#include <irt_syscalls.h>

void __getcwd(char* buf, size_t size) {
    __nacl_irt_getcwd(buf, size);
}

weak_alias (__getcwd, getcwd)
