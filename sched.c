/*
 * sched.c - initializes struct for task 0 anda task 1
 */
#include <libc.h>
#include <sched.h>
#include <mm.h>
#include <io.h>
#include <stats.h>
#include <utils.h>
/**
 * Container for the Task array and 2 additional pages (the first and the last one)
 * to protect against out of bound accesses.
 */
union task_union protected_tasks[NR_TASKS+2]
__attribute__((__section__(".data.task")));

int MAX_PID = 42;
int quantum_left;

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

unsigned long  getEbp();

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
	struct list_head *ff = list_first(&freequeue);
	list_del(ff);
	struct task_struct *idle_ts = list_head_to_task_struct(ff);
	idle_ts -> PID = 0;
	union task_union *tmp = (union task_union *) idle_ts;
	tmp->stack[KERNEL_STACK_SIZE-1] = (unsigned long) cpu_idle;
	tmp->stack[KERNEL_STACK_SIZE-2] = (unsigned long) 0;
	idle_ts -> kernel_esp = &tmp->stack[KERNEL_STACK_SIZE-2];
	allocate_DIR(idle_ts);   
	idle_task = idle_ts;
}

void init_task1(void)
{
	struct list_head *ff = list_first(&freequeue);
	list_del(ff);
	
	struct task_struct *task1_ts = list_head_to_task_struct(ff);
	task1_ts -> PID = MAX_PID++;

	allocate_DIR(task1_ts);
	set_user_pages(task1_ts);

	tss.esp0 = (unsigned long) KERNEL_ESP((union task_union *) task1_ts);
	task1_ts -> kernel_esp = (unsigned long *) KERNEL_ESP((union task_union *) task1_ts);
	writeMsr(0x175, KERNEL_ESP((union task_union *) task1_ts)); 
	task1_ts -> ticks = 0;
	task1_ts -> quantum = 12;
	quantum_left = 12;
	task1_ts -> state = ST_RUN;
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
	tss.esp0 =  KERNEL_ESP(t);
 //(unsigned long) t -> task.kernel_esp;
	writeMsr(0x175, (int) KERNEL_ESP(t));

	set_cr3(t -> task.dir_pages_baseAddr);

	current() -> kernel_esp = (unsigned long *) getEbp(); 

	setEsp(t -> task.kernel_esp);

	return;          
}         

void update_sched_data_rr(void){
	current()->ticks++;
	quantum_left--;
}

int needs_sched_rr(void){
	return quantum_left <= 0 && !list_empty(&readyqueue); 
        //return current()->quantum && !(current()->ticks % current()->quantum) && !list_empty(&readyqueue);
}

void update_process_state_rr(struct task_struct *t, struct list_head *dst_queue){
	if( t->state != ST_RUN ) list_del(&t->list);
	if( dst_queue == NULL ){
		t->state = ST_RUN;
	}else
	{
		list_add_tail(&t->list, dst_queue);	
		if( dst_queue == &readyqueue ) {
			t->state = ST_READY;
		}
	} 
}
void sched_next_rr(void){
	if (!list_empty(&readyqueue)){
		struct list_head* next = list_first(&readyqueue);
		struct task_struct* nextt = list_head_to_task_struct(next);

		struct stats st;
	        st = current()->stats;
		st.system_ticks += get_ticks() - st.elapsed_total_ticks;
		st.elapsed_total_ticks = get_ticks();
		update_process_state_rr(current(), &readyqueue);

		st = nextt->stats;
		st.ready_ticks += get_ticks() - st.elapsed_total_ticks;
		st.elapsed_total_ticks = get_ticks();
		update_process_state_rr(nextt, NULL);

		quantum_left = nextt->quantum;
		task_switch((union task_union * ) nextt);
	}
}

int get_quantum( struct task_struct *t ){
	return t->quantum;
}

void set_quantum( struct task_struct *t, int new_quantum ){
	t->quantum = new_quantum;
}

void update_entry_system(){
	struct stats st;
	st = current()->stats;
	st.user_ticks += get_ticks() - st.elapsed_total_ticks;
	st.elapsed_total_ticks = get_ticks();
}

void update_leave_system(){
	struct stats st;
	st = current()->stats;
	st.system_ticks += get_ticks() - st.elapsed_total_ticks;
	st.elapsed_total_ticks = get_ticks();
}
