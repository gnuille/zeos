/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */

#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>
#include <errno.h>

int write(int fd, const char *buffer, int size);

void itoa(int a, char *b);

int strlen(char *a);

int getpid();

int fork();

int clone(void (* function)(void), void *stack);

int sem_init(int n_sem, unsigned int value);

int sem_wait(int n_sem);

int sem_signal(int n_sem);

int sem_destroy(int n_sem);

void exit();

int gettime();

int get_stats(int pid, struct stats * st);

static const char ESRCH_msg[] = "No such process.";
static const char EBADF_msg[] = "fd is not a valid file descriptor or is not open for writing.";
static const char EAGAIN_msg[] = "Try again";

static const char ENOMEM_msg[] = "Out of memory, cannot allocate structures.";

static const char EFAULT_msg[] = "buf is outside your accessible address space.";
static const char EINVAL_msg[] = "size contains an invalid value.";

void perror(void);

#endif  /* __LIBC_H__ */
