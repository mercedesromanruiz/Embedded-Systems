; ----- HW3_EX7 -----
; This program drives a LED flashlight

#include <p18f4620.inc>

LIGHT equ 0
CNT0 equ 1

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
	return

All:
	movlw 255
	movwf PORTC
	movwf PORTD
	return

end


	
	




