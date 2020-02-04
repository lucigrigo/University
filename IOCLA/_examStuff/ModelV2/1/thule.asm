%include "io.inc"

section .data
   word_num1 dd 0xff543210
   word_num2 dd 0x00111111
   result_word resd 2
   big_num1 dd 0x11111111, 0x22222222, 0x33333333
   big_num2 dd 0xffffffff, 0x22222222, 0x33333333
   result_4word resd 4
   num_array1 dd 0x11111111, 0x22222222, 0x33333333, 0x12111211, 0x22232242, 0xff333333, 0xff123456, 0xff123456, 0xff123456
   num_array2 dd 0xffffffff, 0x22922252, 0x33033338, 0x12111211, 0x22232242, 0xff333333, 0xff123456, 0xff123456, 0xff123456
   result_array resd 12
   length dd 3

section .text
global main
main:
    push ebp
    mov ebp, esp

    ;TODO a, b, c: Implement the array sum starting with double word sum incrementally solving subsequent task b and c.

    leave
    ret
