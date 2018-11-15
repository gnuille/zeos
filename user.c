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
	struct stats st;
	int i;
	int res;
	for(i = 0; i<1000000; i++){
		if(i%2){
			res = getpid();
		}else{
			res = fact(10);		
		}
	
	}
	res = get_stats(getpid(), &st);
	char buff[100];
	itoa(st.user_ticks, &buff);
	write(1, "User ticks:", strlen("User ticks:"));
	write(1, &buff, strlen(&buff));
	write(1, "\nSystem ticks:", strlen("\nSystem ticks:"));
	itoa(st.system_ticks, &buff);
	write(1, &buff, strlen(&buff));
	while(1);
	return 0;
}
