#include <p18f4620.inc>

	org 0x800

; --- Initialize Ports ---

	movlw 0xFF
	movwf TRISB
	movwf TRISC
	clrf TRISD	

; --- Program ---
L1: 
	btfss PORTB, 0
	goto L1
L2:
	btfsc PORTB, 1
	goto L3
	btfsc PORTB, 2
	goto L4
L5:
	movff PORTC, PORTD
	goto L6
L3:
	movlw 17
	movff PORTC, PORTD
	addwf PORTD, F
	goto L6
L4:
	movlw 17
	movff PORTC, PORTD
	subwf PORTD, F
L6:
	btfss PORTB, 0
	goto L1
	goto L6
end
		