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
    write(1, "42", 2);
	for (;;);
 	return 0;
}
