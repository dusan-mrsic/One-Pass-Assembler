.section data:

.global X
.equ X, 10 + 5-6
array:

                .word 10, 42, 8, 34, 22 , 2, 1, 87, 99, 53, 67, 10, 69
                .word 22, 80, 11, 75, 25, 0, 12

size:           .word X

.section text:

.extern print_hex
.extern println

.global START
START:

                push $array
                push size
                call bubblesort
                add %r6, 4
                mov %r1, 0
loop:           push array(%r1)
                call print_hex
                add 2, %r6
                call println

                add 2, %r1

                cmp size, %r1
                jgt loop

exit:           halt

bubblesort:                     

                push %r1
                push %r2
                push %r3
                push %r4
                mov %r3, 10(%r6)
                add %r3, 12(%r6)
                sub $2, %r3

next_iter:      cmp %r3, 10(%r6)
                jeq *return

                mov %r1, 10(%r6)
                mov %r2, %r1
inner_iter:     add $2, %r2
                cmp %r2, %r3
                jeq *inner_iter_end

                mov %r4, 0(%r2)
                cmp %r4, 0(%r1)
                jgt *skip_swap
                push %r1
                push %r2
                call *swap
                add $4, %r6

skip_swap:      mov %r1, %r2
                jmp *inner_iter


inner_iter_end: sub $2,%r3

                jmp *next_iter

return:         pop %r4

                pop %r3
                pop %r2
                pop %r1
                ret



swap:

                push %r1
                push %r2
                push %r3
                mov %r1, 8(%r6)
                mov %r2, 12(%r6)
                mov %r0, 0(%r1)
                mov %r3, 0(%r2)
                mov 0(%r1), %r3
                mov 0(%r2), %r0
                pop %r3
                pop %r2
                pop %r1
                ret



.end








