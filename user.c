#include <libc.h>
#include <stats.h>
char buff[42];
int pid;

int fact(int i){
	if(i == 0) return 1;
	else return fact(i-1)*i;
}
	int __attribute__ ((__section__(".text.main")))
main(void)
{
	/* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
	/* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	runjp();
	for (;;);
	return 0;
}
