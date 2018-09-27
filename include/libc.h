/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */

#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>

int write(int fd, char *buffer, int size);

void itoa(int a, char *b);

int strlen(char *a);

int getpid();

int fork();

void exit();

int gettime();

static const char wrong_fd[] = "fd is not a valid file descriptor or is not open for writing.";
static const char buff_not_acc[] = "buf is outside your accessible address space.";
static const char invalid_size[] = "size contains an invalid value.";

void perror(void);

#endif  /* __LIBC_H__ */
