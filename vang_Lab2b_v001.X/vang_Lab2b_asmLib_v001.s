.include "xc.inc"
.text                       ;BP (put the following data in ROM(program memory))
; This is a library, thus it can *not* contain a _main function: the C file will
; deine main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _kv_wait_100us, _kv_wait_1ms
   
_write_0:
	    ; create a 0.35 microseconds pulse in a 1.25 microseconds period
	    ; 2 cycles for function call
    bset    LATA, #0	; 1 cycle
    repeat #3		; 1 cycle to load and prep
    nop			; 3 + 1 cycles
	    ; 6 total cycles HIGH (T0H)    
    clr	    LATA	; 1 cycle
    repeat  #6		; 1 cycle to load and prep
    nop			; 6 + 1 cycles
    return		; 3 cycles
	    ; 14 cycles LOW (T0W)
	    ; 20 total cycles for write_0
	    
_write_1:
	    ; create a 0.70 microseconds pulse in a 1.25 microseconds period
	    ; 2 cycles for function call
    bset    LATA, #0	; 1 cycle
    repeat  #8		; 1 cycle to load and prep
    nop			; 8 + 1 cycles
	    ; 11 total cycles HIGH (T0H) 
	    
    clr	    LATA	; 1 cycle   
    repeat  #1		; 1 cycle to load and prep
    nop			; 1 + 1 cycles
    return		; 3 cycles
	    ; 9 cycles LOW (T0L)
	    ; 20 total cycles for write_1
	    
_kv_wait_100us:
	    ; approx. 1592.36 cycles
	    ; 2 cycles for function call
    repeat #1586
    nop	    ; 1586 + 1 cycles
    return  ; 3 cycles
    
_kv_wait_1ms:
	    ; approx. 16,000 cycles
	    ; 2 cycles for function call
    repeat #15994
    nop	    ; 15994 + 1 cycles
    return  ; 3 cycles
