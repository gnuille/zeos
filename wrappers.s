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
# 61 "wrappers.S"
.globl write; .type write, @function; .align 0; write:
      movl -8(%ebp), %ebx
      movl -12(%ebp), %ecx
      movl -16(%ebp), %edx
      movl $4, %eax
      int $0x80
      ret
