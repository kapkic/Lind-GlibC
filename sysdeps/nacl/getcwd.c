#include <unistd.h>
#include <lind_syscalls.h>

char* __getcwd(char* buf, size_t size) {
    int error = lind_getcwd(buf, size);
    if(error==0){
        return buf;
    } 
    else { 
        __set_errno (error);
        return NULL;
    }
}

weak_alias (__getcwd, getcwd)
