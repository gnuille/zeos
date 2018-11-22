/*
 * libc.c
 */

#include <libc.h>

#include <types.h>

int errno;

//int write(int fd, char *buffer, int size);

void itoa(int a, char *b)
{
	int i, i1;
	char c;

	if (a==0) { b[0]='0'; b[1]=0; return ;}

	i=0;
	while (a>0)
	{
		b[i]=(a%10)+'0';
		a=a/10;
		i++;
	}

	for (i1=0; i1<i/2; i1++)
	{
		c=b[i1];
		b[i1]=b[i-i1-1];
		b[i-i1-1]=c;
	}
	b[i]=0;
}

int strlen(char *a)
{
	int i;

	i=0;

	while (a[i]!=0) i++;

	return i;
}

void perror(void){
	switch (errno) {
		case 1:  write(1, EPERM_msg, sizeof(EPERM_msg)); break;
		case 3:  write(1, ESRCH_msg, sizeof(ESRCH_msg)); break;
		case 9:  write(1, EBADF_msg, sizeof(EBADF_msg)); break;
		case 11: write(1, EAGAIN_msg, sizeof(EAGAIN_msg)); break;
		case 12: write(1, ENOMEM_msg, sizeof(ENOMEM_msg)); break;
		case 14: write(1, EFAULT_msg, sizeof(EFAULT_msg)); break;
		case 16: write(1, EBUSY_msg,  sizeof(EBUSY_msg));  break;
		case 22: write(1, EINVAL_msg, sizeof(EINVAL_msg)); break;
	}
}
