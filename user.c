#include <libc.h>
#include <stats.h>
char buff[42];
int pid;

int fact(){
	int a;
	for (int i = 0; i < 10; ++i) write(1, "Hola", 5);
	exit();
}

	int __attribute__ ((__section__(".text.main")))
main(void)
{
	/* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
	/* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	char stack[200];
	write(1, "\nArreglar al clone. Buscar TODO a sys.c", strlen("\nArreglar al clone. Buscar TODO a sys.c"));
	clone(fact, stack);

//	runjp();
	for (;;);
	return 0;
}
