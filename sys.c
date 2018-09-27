/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#define LECTURA 0
#define ESCRIPTURA 1
int zeos_ticks;

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
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

//-1 invalid fd
//-2 invalid addr
//-3 invalid size
//-4 error copy from user

#define CHUNK_SIZE 64
int sys_write(int fd, char* buffer, int size){
  if(check_fd(fd, ESCRIPTURA) < 0) return -1;
  if(buffer == NULL) return -2;
  if(size < 0) return -3;
  char dest[CHUNK_SIZE];
  int i = 0;
  int writen = 0;
  while (i < size-CHUNK_SIZE){
    if(copy_from_user(buffer+i,dest, CHUNK_SIZE) < 0) return -4;
    writen += sys_write_console(dest, CHUNK_SIZE);
    i+=CHUNK_SIZE;
  }

  if(copy_from_user(buffer+i,dest, size%CHUNK_SIZE) < 0) return -4;
  writen += sys_write_console(dest, size%CHUNK_SIZE); 
  return writen;
}
int sys_gettime(){
  return zeos_ticks;
}
