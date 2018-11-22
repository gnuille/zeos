#include <libc.h>
#include <stats.h>
char buff[42];
int pid;

#if 0
void fact(){
	int i = 2000;
	while(i--) write(1,"HOla bon dia, soc molt feliz\n", strlen("HOla bon dia, soc molt feliz\n"));
	exit();
}

#endif

	int __attribute__ ((__section__(".text.main")))
main(void)
{
	/* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
	/* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
#if 0
	char stack[2000];
	write(1, "\nArreglar al clone. Buscar TODO a sys.c", strlen("\nArreglar al clone. Buscar TODO a sys.c"));
	clone(fact, &stack[1999]);
	int i;
	for(i = 0; i < 1500; i++) write(1,"CONVISC AMB EL MEU THREAD FILL\n", strlen("CONVISC AMB EL MEU THREAD FILL\n"));
#endif
	runjp();
	for (;;);
 	return 0;
}
