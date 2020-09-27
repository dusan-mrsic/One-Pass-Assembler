.section text:
.global main

.extern readln, writeln

main:
    halt
    xchgb %r0h, %r0l
    xchg %r0, %r1
    xchgw %r1, 0(%r2)
    xchgw %r2, 5(%r3)
    xchg %r3, offset(%r4)
    xchgw $782, %r4
    xchg %r5, offset
    xchg %r5, offset
    xchg  %r5, -597(%r6)
    int 3
    mov %r0, offset
    addb %r0h, %r1l
    sub %r2, offset

    mul offset(%r5), %r3
    div %r0, offset
    cmp offset(%r7), %r0
    not 0(%r5), %r1
    andb %r0h, %r1l

    orw %r0, offset(%pc)
    xorb %r0h, %r0h

test:
    test %r0, offset
    shl $0x682, %r3
    shr offset, %r2
    push -892(%r3)
    pop %r3
    jmp *test
    jeq *test(%r7)
    jne *73
 jgt offset(%r4)

 call *func
 iret
movw 0(%r2), 0x1234
    jmp *offset
func:
    push 5(%r3)
    ret
.section data:
.word 2
offset: .word 576
.section rodata


hellostr:       .byte 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0x0


.end
