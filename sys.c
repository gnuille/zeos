/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <errno.h>

#define LECTURA 0
#define ESCRIPTURA 1
int zeos_ticks;

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -EBADF;
  if (permissions!=ESCRIPTURA) return -EACCES;
  return 0;
}

int sys_ni_syscall()
{
	return -38; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork()
{
  int PID=-1;

  // creates the child process

  return PID;
}

void sys_exit()
{
}

#define CHUNK_SIZE 64
int sys_write(int fd, char* buffer, int size){
  int err;
  if((err=check_fd(fd, ESCRIPTURA)) < 0) return err;
  if(buffer == NULL) return -EFAULT;
  if(size < 0) return -EINVAL;
  char dest[CHUNK_SIZE];
  int i = 0;
  int writen = 0;
  while (i < size-CHUNK_SIZE){
    copy_from_user(buffer+i,dest, CHUNK_SIZE);
    writen += sys_write_console(dest, CHUNK_SIZE);
    i+=CHUNK_SIZE;
  }

  copy_from_user(buffer+i,dest, size%CHUNK_SIZE);
  writen += sys_write_console(dest, size%CHUNK_SIZE); 
  return writen;
}
int sys_gettime(){
  return zeos_ticks;
}
