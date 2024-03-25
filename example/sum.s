.intel_syntax noprefix

.global _start

.section .text

sum:
    lea eax, [rdi + rsi]
    ret

_start:
    mov edi, 0x2
    mov esi, 0x2
    call sum
    jmp _exit

_exit:
    mov rax, 0x3c
    xor rdi, rdi
    syscall
