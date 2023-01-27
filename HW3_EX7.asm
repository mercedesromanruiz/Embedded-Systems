; ----- HW3_EX7 -----
; This program drives a LED flashlight

#include <p18f4620.inc>

CNT0 equ 1
CNT1 equ 2
CNT2 equ 3
LED equ 4

; --- Program ---
	org 0x800
	movlw 15
	movwf ADCON1

	call Init
	goto Button

Init:
	movlw 255
	movwf TRISB
	clrf TRISC
	clrf TRISD
	return

Button:
	btfsc PORTB, 0
	call Off
	btfsc PORTB, 1
	call Half
	btfsc PORTB, 2
	call All
	goto Button

Off:
	movlw 0
	movwf PORTC
	movwf PORTD
	return

Half:
	movlw 0
	movwf PORTC
	movlw 255
	movwf PORTD
	bcf PORTD, 7
	return

All:
	movlw 255
	movwf PORTC
	movwf PORTD
	call OffC
	return

Wait:	; --- Wait 500 ms (2,500,000 clocks)
	movlw 25
	movwf CNT2
Loop2:
	movlw 100
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
	decfsz	CNT1, F
	goto Loop1
	decfsz CNT2, F
	goto Loop2
	return

OffC:
	call Wait
	bcf PORTC, 7
	call Wait
	bcf PORTC, 6
	call Wait
	bcf PORTC, 5
	call Wait
	bcf PORTC, 4
	call Wait
	bcf PORTC, 3
	call Wait
	bcf PORTC, 2
	call Wait
	bcf PORTC, 1
	call Wait
	bcf PORTC, 0
	return


end


	
	




