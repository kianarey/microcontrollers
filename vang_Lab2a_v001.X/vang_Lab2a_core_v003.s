.include "xc.inc"          ; required "boiler-plate" (BP)

;the next two lines set up the actual chip for operation - required
config __CONFIG2, POSCMOD_EC & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSECME & FNOSC_FRCPLL & SOSCSEL_LPSOSC & WUTSEL_FST & IESO_OFF
config __CONFIG1, WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & BKBUG_ON & GWRP_ON & GCP_ON & JTAGEN_OFF

    .bss        ; put the following labels in RAM
counter:
    .space 2    ; a variable that takes two bytes (we won?t use
		; it for now, but put here to make this a generic
		; template to be used later).
stack:
    .space  32  ; this will be our stack area, needed for func calls

.text       ; BP (put the following data in ROM(program memory))

;because we are using the C compiler to assemble our code, we need a "_main" label
;somewhere. (There's a link step that looks for it.)
.global _main               ;BP
;your functions go here

wait_21cycles:
	    ; 2 cycles for function call
    repeat #16 	; 1 to load and prep
    nop	    ; 16 + 1 cycles to execute
    return  ; 3 cycles

wait_100us: ; approx. 1592.36 cycles
	    ; 2 cycles for function call
    repeat #800
    nop	    ; 1586 + 1 cycles
    return  ; 3 cycles
    
wait_1ms:   ; approx. 16,000 cycles
	    ; 2 cycles for function call
    repeat #15994
    nop	    ; 15994 + 1 cycles
    return  ; 3 cycles
    
write_0:
	    ; create a 0.35 microseconds pulse in a 1.25 microseconds period
	    ; 2 cycles for function call
    bset    LATA, #0	; 1 cycle; set bit-0 to 1 in LATA
    repeat #3		; 1 cycle to load and prep
    nop			; 3 + 1 cycles
	    ; 6 total cycles HIGH (T0H)    
    clr	    LATA	; 1 cycle
    repeat  #6		; 1 cycle to load and prep
    nop			; 6 + 1 cycles
    return		; 3 cycles
	    ; 14 cycles LOW (T0W)
	    ; 20 total cycles for write_0
    
write_1:
	    ; create a 0.70 microseconds pulse in a 1.25 microseconds period
	    ; 2 cycles for function call
    bset    LATA, #0	; 1 cycle; set bit-0 to 1 in LATA
    repeat  #8		; 1 cycle to load and prep
    nop			; 8 + 1 cycles
	    ; 11 total cycles HIGH (T0H) 
	    
    clr	    LATA	; 1 cycle   
    repeat  #1		; 1 cycle to load and prep
    nop			; 1 + 1 cycles
    return		; 3 cycles
	    ; 9 cycles LOW (T0L)
	    ; 20 total cycles for write_1
_main:
    bclr    CLKDIV,#8	    ;BP
    nop
    ;; --- Begin your program below here ---
    mov     #0x9fff, w0
    mov     w0, AD1PCFG            ; Set all pins to digital mode
    mov     #0b1111111111111110, w0
    mov     w0, TRISA              ; set pin RA0 to output
    mov     #0x0001, w0
    mov     w0, LATA               ; set pin RA0 high, LED off

    /*foreverLoop:
	nop
	nop
	clr	LATA ; set pin RA0 low
	nop
	nop
	inc	LATA ; set pin RA0 high
	bra	foreverLoop
	.end	; this doesn't actually end anything. Does not translate to assembly
		; code. Just a way to tell the compiler we are done with this file.
    */
    
    /*foreverLoop1:
	call	wait_21cycles	; 21 cycles
	clr	LATA		; set pin RA0 low = 1 cycle
    
	nop			; 2 cycles to match BRA delay
	nop
	repeat #27		; 1 cycle to load and prep
	nop			; 27 + 1 cycles to execute NOP
	inc	LATA		; set pin RA0 high = 1 cycle
				; Total = 24 cycles high, 32 cycles low
	bra	foreverLoop1
    */
    ; add serial transmission of RGB colors before the forever loop here:
    
    foreverLoop2:	
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	call	write_0
	
	call	write_1
	call	write_1
	call	write_1
	call	write_1
	call	write_1
	call	write_1
	call	write_1
	call	write_1
	
		    ; 24 total calls
	call	wait_100us  ; wait approx. 100us
	bra	foreverLoop2
	.end	; this doesn't actually end anything. Does not translate to assembly
		; code. Just a way to tell the compiler we are done with this file.