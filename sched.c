/*
 * sched.c - initializes struct for task 0 anda task 1
 */
#include <libc.h>
#include <sched.h>
#include <mm.h>
#include <io.h>

/**
 * Container for the Task array and 2 additional pages (the first and the last one)
 * to protect against out of bound accesses.
 */
union task_union protected_tasks[NR_TASKS+2]
  __attribute__((__section__(".data.task")));

int MAX_PID = 42;

union task_union *task = &protected_tasks[1]; /* == union task_union task[NR_TASKS] */

struct list_head freequeue, readyqueue;

struct task_struct * idle_task;

#if 1
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
#endif

extern struct list_head blocked;


void writeMsr(int msr, int data);

void setEsp(unsigned long * data);

unsigned long * getEbp();

/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) 
{
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) 
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


int allocate_DIR(struct task_struct *t) 
{
	int pos;

	pos = ((int)t-(int)task)/sizeof(union task_union);

	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos]; 

	return 1;
}

void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
		printk("0");
	}
}

void init_idle (void)
{
    struct list_head *ff = freequeue.next;
    list_del(ff);
    list_add_tail(ff, &readyqueue);
    struct task_struct *idle_ts = list_head_to_task_struct(ff);
    idle_ts -> PID = 0;
    ((unsigned long *) idle_ts)[KERNEL_STACK_SIZE-1] = (unsigned long) cpu_idle;
    ((unsigned long *) idle_ts)[KERNEL_STACK_SIZE-2] = (unsigned long) 0;
    idle_ts -> kernel_esp = (unsigned long *) &(((unsigned long *)idle_ts)[KERNEL_STACK_SIZE-2]);
    allocate_DIR(idle_ts);   
    idle_task = idle_ts; 
    ++MAX_PID;
}

void init_task1(void)
{
    struct list_head *ff = freequeue.next;
    list_del(ff);
    list_add_tail(ff, &readyqueue);

    struct task_struct *task1_ts = list_head_to_task_struct(ff);
    task1_ts -> PID = MAX_PID++;
    
    allocate_DIR(task1_ts);
    set_user_pages(task1_ts);
    
    tss.esp0 = (unsigned long) KERNEL_ESP((union task_union *) task1_ts);
    task1_ts -> kernel_esp = (unsigned long *) KERNEL_ESP((union task_union *) task1_ts);
    writeMsr(0x175, KERNEL_ESP((union task_union *) task1_ts)); 

    set_cr3(task1_ts->dir_pages_baseAddr); 
}

void init_sched(){

}

struct task_struct* current()
{
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %00"
	: "=g" (ret_value)
  );
  return (struct task_struct*)(ret_value&0xfffff000);
}

void init_free_queue(){
    int i;
    INIT_LIST_HEAD(&freequeue);        
    for (i = 0; i < NR_TASKS; ++i){
        task[i].task.PID = -1;
        list_add_tail(&task[i].task.list, &freequeue);
    }
}

void init_ready_queue(){
    INIT_LIST_HEAD(&readyqueue);
}

void inner_task_switch(union task_union*t){
    tss.esp0 = (unsigned long) t -> task.kernel_esp;
    writeMsr(0x175, (int) t -> task.kernel_esp);

    set_cr3(t -> task.dir_pages_baseAddr);

    current() -> kernel_esp = getEbp(); 
    
    setEsp(t -> task.kernel_esp);

    return;          
}         
          
