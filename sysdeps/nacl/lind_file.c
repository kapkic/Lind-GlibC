
#include <stdlib.h>
#include <string.h>
#include <lind_file.h>
#include <lind_rpc.h>
#include <unistd.h>

#define HASHSIZE (0xff)

unsigned int max_nacl_fd;

struct lind_file_node
{
    struct lind_file f;
    struct lind_file_node* next;
};

struct lind_file_node* lind_file_map[HASHSIZE];

void init_lind_file_map(void)
{
    memset(lind_file_map, 0, sizeof(lind_file_map));
    //stdin, stdout, stderr
    add_lind_file_interal(STDIN_FILENO, 0);
    add_lind_file_interal(STDOUT_FILENO, 0);
    add_lind_file_interal(STDERR_FILENO, 0);
    //NaCl descriptors for Lind RPC
    add_lind_file_interal(NACL_PLUGIN_BOUND_SOCK, 0);
    add_lind_file_interal(NACL_PLUGIN_ASYNC_FROM_CHILD_FD, 0);
    add_lind_file_interal(NACL_PLUGIN_ASYNC_TO_CHILD_FD, 0);
}

void add_lind_file_interal(int fd, int isLindFd)
{
    int ind = fd % HASHSIZE;
    struct lind_file_node* new_node = malloc(sizeof(struct lind_file_node));
    new_node->f.fd = fd;
    new_node->f.isLindFd = isLindFd;
    new_node->next = lind_file_map[ind];
    lind_file_map[ind] = new_node;
}

void add_lind_file(struct lind_file* f)
{
    add_lind_file_interal(f->fd, f->isLindFd);
}

struct lind_file* get_lind_file(int fd)
{
    int ind = fd % HASHSIZE;
    struct lind_file_node* node = lind_file_map[ind];
    for(; node!=NULL; node=node->next) {
        if(node->f.fd == fd) {
            return &node->f;
        }
    }
    return NULL;
}

void delete_lind_file(int fd)
{
    int ind = fd % HASHSIZE;
    struct lind_file_node** node = &lind_file_map[ind];
    for(; (*node)!=NULL; *node=(*node)->next) {
        if((*node)->f.fd == fd) {
            struct lind_file_node* next = (*node)->next;
            free(*node);
            *node = next;
            return;
        }
    }
}

int is_lind_file(const char* filename)
{
    int len = strlen(filename)-1;
    if(len>4 && filename[len-4] == '.' && filename[len-3] == 'n' &&
            filename[len-2] == 'e' && filename[len-1] == 'x' &&
            filename[len] == 'e') {
        return 0;
    }
    if(strstr(filename, ".so")) {
        return 0;
    }
    /*
    if(len>0 && filename[len]>='0' && filename[len]<='9') {
        --len;
        while(len>0 && filename[len]>='0' && filename[len]<='9') {
            --len;
        }
        if(filename[len--]!='.') {
            return 1;
        }
    }
    if(len>2 && filename[len-2] == '.' && filename[len-1] == 's' &&
            filename[len] == 'o') {
        return 0;
    }*/
    return 1;
}
