# 1 "wrappers.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "wrappers.S"
# 1 "include/asm.h" 1
# 2 "wrappers.S" 2
# 1 "include/segment.h" 1
# 3 "wrappers.S" 2
# 80 "wrappers.S"
.globl write; .type write, @function; .align 0; write:
 push %ebp
 movl %esp, %ebp
 push %ebx
 movl 8(%ebp), %ebx
 movl 12(%ebp), %ecx
 movl 16(%ebp), %edx
 leal syscall_ret4, %eax; push %eax; movl $4, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret4: pop %ebp; addl $4, %esp;
 cmpl $0, %eax; jge write.no_error; negl %eax; leal errno, %ebx; movl %eax, (%ebx); movl $-1, %eax;
 write.no_error:
 pop %ebx
 pop %ebp
 ret

.globl gettime; .type gettime, @function; .align 0; gettime:
 push %ebp
 movl %esp, %ebp
 leal syscall_ret10, %eax; push %eax; movl $10, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret10: pop %ebp; addl $4, %esp;
 pop %ebp
 ret

.globl getpid; .type getpid, @function; .align 0; getpid:
 push %ebp
 movl %esp, %ebp
 leal syscall_ret20, %eax; push %eax; movl $20, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret20: pop %ebp; addl $4, %esp
 pop %ebp
 ret

.globl fork; .type fork, @function; .align 0; fork:
 push %ebp
 movl %esp, %ebp
 push %ebx
 leal syscall_ret2, %eax; push %eax; movl $2, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret2: pop %ebp; addl $4, %esp
 cmpl $0, %eax; jge fork.no_error; negl %eax; leal errno, %ebx; movl %eax, (%ebx); movl $-1, %eax
 fork.no_error:
 pop %ebx
 pop %ebp
 ret

.globl clone; .type clone, @function; .align 0; clone:
 push %ebp
 movl %esp,% ebp
 push %ebx
 leal syscall_ret19, %eax; push %eax; movl $19, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret19: pop %ebp; addl $4, %esp
 cmpl $0, %eax; jge clone.no_error; negl %eax; leal errno, %ebx; movl %eax, (%ebx); movl $-1, %eax
 clone.no_error:
 pop %ebx
 pop %ebp
 ret

.globl get_stats; .type get_stats, @function; .align 0; get_stats:
 push %ebp
 movl %esp, %ebp
 push %ebx
 movl 8(%ebp), %ebx
 movl 12(%ebp), %ecx
 leal syscall_ret35, %eax; push %eax; movl $35, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret35: pop %ebp; addl $4, %esp
 cmpl $0, %eax; jge get_stats.no_error; negl %eax; leal errno, %ebx; movl %eax, (%ebx); movl $-1, %eax
 get_stats.no_error:
 pop %ebx
 pop %ebp
 ret

.globl exit; .type exit, @function; .align 0; exit:
 push %ebp
 movl %esp, %ebp
 leal syscall_ret1, %eax; push %eax; movl $1, %eax; push %ebp; movl %esp, %ebp; sysenter; syscall_ret1: pop %ebp; addl $4, %esp
 pop %ebp
 ret
