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

extern struct list_head freequeue, readyqueue;

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
  if (list_empty(freequeue)) return -1; // NO PROCESS LEFT
  struct list_head *new_task_ptr = freequeue.next; 
  list_del(new_task_ptr);

  struct task_struct *new_task = list_head_to task_struct(new_task_ptr);

  // Copy data from parent to child
  copy_data(current(), new_task,(int) sizeof(union task_union));
  
  allocate_DIR(new_task);
  if (data_frame < 0 || stack_frame < 0) return -1; // No phisical space left
  page_table_entry * n_pt = get_PT(new_task);
  page_table_entry * c_pt = get_PT(current());

  int page;
  for (page = 0; page < NUM_PAG_KERNEL; page++){
     n_pt[1+page].entry = c_pt[1+page].entry;
  }

  for (page = 0; page < NUM_PAGE_CODE; page++){
     n_pt[PAG_LOG_INIT_CODE+page].entry = c_pt[PAG_LOG_INIT_CODE+page].entry;
  }

  for (page = 0; page < NUM_PAGE_DATA; page++){
    int new_frame = alloc_frame();
    set_ss_pag(n_pt, PAG_LOG_INIT_DATA+page, new_frame);
    set_ss_pag(c_pt, PAG_LOG_INIT_DATA+NUM_PAGE_DATA, new_frame);
    copy_data(c_pt[PAG_LOG_INIT_DATA+page].entry.base_addr,
		c_pt[PAG_LOG_INIT_DATA+NUM_PAGE_DATA].entry.base_addr,
		PAGE_SIZE);
    del_ss_pag(c_pt, PAG_LOG_INIT_DATA+NUM_PAGE_DATA);
    set_cr3(get_DIR(current()));
  }
  
  PID = 42;

  list_add_tail(new_task_ptr, readyqueue); 	

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
