/*
 * lind_file.h
 *
 *  Created on: Apr 2, 2013
 *      Author: sji
 */

#ifndef LIND_FILE_H_
#define LIND_FILE_H_

struct lind_file
{
    int fd;
    int isLindFd;
};

extern unsigned int max_nacl_fd;

void init_lind_file_map(void);
void add_lind_file(struct lind_file* f);
struct lind_file* get_lind_file(int fd);
void delete_lind_file(int fd);
int is_lind_file(const char* filename);

#endif /* LIND_FILE_H_ */
