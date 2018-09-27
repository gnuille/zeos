# 1 "wrappers.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrappers.S"
# 1 "include/asm.h" 1
# 2 "wrappers.S" 2
# 1 "include/segment.h" 1
# 3 "wrappers.S" 2
# 61 "wrappers.S"
.globl write; .type write, @function; .align 0; write:
      push %ebp
      movl %esp, %ebp
      push %ebx
      movl 8(%ebp), %ebx
      movl 12(%ebp), %ecx
      movl 16(%ebp), %edx
#retur adress load
      leal return4, %eax
#fake dynamic link
      push %eax
      movl $4, %eax
      push %ebp
      movl %esp, %ebp
      sysenter
return4:
#undo fake dynamic link
      pop %ebp
      addl $4, %esp
#check for errors
      cmpl $0, %eax
      jge fin4
      negl %eax
      incl %eax
      leal errno, %ebx
      movl %eax, (%ebx)
      movl $-1, %eax
fin4:
      pop %ebx
      pop %ebp
      ret

.globl gettime; .type gettime, @function; .align 0; gettime:
      push %ebp
      push %ebx
      movl %esp, %ebp
      leal return10, %eax
      push %eax
      movl $10, %eax
      push %ebp
      movl %esp, %ebp
      sysenter
return10:
      pop %ebp
      addl $4, %esp
      cmpl $0, %eax
      jge fin10
      negl %eax
      incl %eax
      leal errno, %ebx
      movl %eax, (%ebx)
      movl $-1, %eax
fin10:
      pop %ebx
      pop %ebp
      ret
