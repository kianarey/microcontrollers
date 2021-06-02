.include "xc.inc"
.text                       ;BP (put the following data in ROM(program memory))
; This is a library, thus it can *not* contain a _main function: the C file will
; deine main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading
; underscore (_) and be included in a comment delimited list below.
.global _kv_wait_100us, _kv_wait_1ms
 
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
