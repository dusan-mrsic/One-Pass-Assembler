
.global A, C
.extern B
.section text:
jmp *A(%pc)
jmp *E(%pc)
jmp *B(%pc)
jmp *D(%pc)
D: .word D
mov %r1, B
mov C, %r1
mov %r1, E
.section data:
.skip 8
E: .equ X, A-E+D
.word C
.word B
A: .word B
.section bss:
C: .skip 8
.end


