#include <libc.h>

char buff[42];

int pid;

int __attribute__ ((__section__(".text.main")))
main(void)
{
	/* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
	/* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	if (fork()){
		itoa(getpid(), buff);
		write(1, "Soc el proces pare. ", strlen("Soc el proces pare. "));
		write(1, buff, strlen(buff));
		write(1, "\n", 1);
	}
	else{
		itoa(getpid(), buff);
		write(1, "Soc el proces fill. ", strlen("Soc el proces fill. "));
		write(1, buff, strlen(buff));
		write(1, "\n", 1);
	}
	while(1);
	return 0;
}
