# 1 "entry.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "entry.S"




# 1 "include/asm.h" 1
# 6 "entry.S" 2
# 1 "include/segment.h" 1
# 7 "entry.S" 2
# 70 "entry.S"
.globl writeMsr; .type writeMsr, @function; .align 0; writeMsr:
      push %ebp
      movl %esp, %ebp
      movl 8(%ebp), %ecx
      movl 12(%ebp), %eax
      movl $0, %edx
      wrmsr
      pop %ebp
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

.globl clock_handler; .type clock_handler, @function; .align 0; clock_handler:
      pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es;
      movb $0x20, %al; outb %al, $0x20;;
      call clock_routine;
      popl %ebx; popl %ecx; popl %edx; popl %esi; popl %edi; popl %ebp; popl %eax; popl %ds; popl %es; popl %fs; popl %gs;
      iret;

.globl task_switch; .type task_switch, @function; .align 0; task_switch:
      pushl %ebp;
      movl %esp, %ebp;
      pushl %esi;
      pushl %edi;
      pushl %ebx;
      pushl 8(%ebp);
      call inner_task_switch;
      addl $4, %esp;
      popl %ebx;
      popl %edi;
      popl %esi;
      movl %ebp, %esp;
      popl %ebp;
      ret;

.globl setEsp; .type setEsp, @function; .align 0; setEsp:
      movl 4(%esp), %esp
      popl %ebp;
      ret;

.globl getEbp; .type getEbp, @function; .align 0; getEbp:
      movl %ebp, %eax
      ret;
