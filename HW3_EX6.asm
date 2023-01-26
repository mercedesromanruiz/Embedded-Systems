; --- HW3_EX6 ---
; This program toggles RC0 at 146.83 Hz (note D3)

#include <p18f4620.inc>

; --- Variables ---
CNT0 EQU 1
CNT1 EQU 2

; --- Program --
	org 0x800
	call Init
Loop:
	incf PORTC, F
	call Wait	; Play note D3 on RC0
	goto Loop
	
; --- Initialize ports ---
Init:
	clrf TRISA
	clrf TRISB
	clrf TRISC
	clrf TRISD
	clrf TRISE
	movlw 15	; 0x0F in hexadecimal
	movwf ADCON1	; Set all to binary
	return

; --- Wait 34,053 clocks ---
Wait:
	movlw 34
	movwf CNT1
Loop1:
	movlw 100
	movwf CNT0
Loop0:	
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz CNT0, F
	goto Loop0
	decfsz CNT1, F
	goto Loop1
	return
	end

	

