# 1 "entry.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "entry.S"




# 1 "include/asm.h" 1
# 6 "entry.S" 2
# 1 "include/segment.h" 1
# 7 "entry.S" 2
# 70 "entry.S"
.globl setMsr; .type setMsr, @function; .align 0; setMsr:
      movl $0x174, %ecx;
      movl $0x10, %eax;
      movl $0, %edx;
      wrmsr;
      movl 0x175, %ecx;
      movl $0x30, %eax
      movl $0, %edx;
      wrmsr;
      movl 0x176, %ecx;
      leal syscall_handler_sysenter, %eax;
      movl $0, %edx;
      wrmsr;
      ret
.globl keyboard_handler; .type keyboard_handler, @function; .align 0; keyboard_handler:
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es;
      movb $0x20, %al; outb %al, $0x20;;
      call keyboard_routine;
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
      iret;

.globl system_call_handler; .type system_call_handler, @function; .align 0; system_call_handler:
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es;
      cmpl $0, %eax;
      jl error;
      cmpl $MAX_SYSCALL, %eax;
      jg error;
      call *sys_call_table(,%eax,4);
      jmp fin;
error:
      movl $-38, %eax;

fin: movl %eax, 18(%esp);
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
      iret;

.globl syscall_handler_sysenter; .type syscall_handler_sysenter, @function; .align 0; syscall_handler_sysenter:
      push $0x2B;
      push %ebp;
      pushfl
      push $0x23
      push 4(%ebp)
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
      cmpl $0, %eax
      jl sysenter_error
      cmpl $MAX_SYSCALL, %eax
      jg sysenter_error
      call *sys_call_table(,%eax,0x04)
      jmp sysenter_fin
  sysenter_error:
      movl $-38, %eax
  sysenter_fin:
      movl %eax, 0x18(%esp)
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs
      movl (%esp), %edx
      movl 12(%esp), %ecx
      sti
      sysexit
