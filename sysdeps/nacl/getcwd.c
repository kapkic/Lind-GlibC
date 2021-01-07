#include <unistd.h>
#include <lind_syscalls.h>

char* __getcwd(char* buf, size_t size) {
    return lind_getcwd(buf, size);
}

weak_alias (__getcwd, getcwd)
