#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
   write(1, 0, 10);
   perror();
   char buffer[64];
   while(1);
   /*while(1){
           int i = gettime();
           itoa(i, buffer);
	   write(1, buffer, sizeof(buffer)); 
   }*/
   return 0;
}
