; unsigned char A, B, C;

A equ 0
B equ 1
C equ 2

; A = 4*B + 5*C + 6;

movlw 6

addwf B, W
addwf B, W
addwf B, W
addwf B, W

addwf C, W
addwf C, W
addwf C, W
addwf C, W
addwf C, W

movwf A


