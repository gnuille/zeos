#include <libc.h>
#include <stats.h>
char buff[42];
int get_stats(int pid, struct stats *st);
int pid;

	int __attribute__ ((__section__(".text.main")))
main(void)
{
	/* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
	/* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
	if (fork()){
		while(1) write(1, "1", strlen("1"));
	}else{
		if(fork()){
			exit();

			while(1) write(1, "jdjasiodioasu2", strlen("jdjasiodioasu2"));
		}else{
			if (fork()){
				while(1) write(1, "3", strlen("3"));
			}
			while(1) write(1, "2", strlen("2"));
		}	
	}
	while(1);
	return 0;
}
