;File Name: asm_test.s
;
;Description:
;The file contains a test assembly code which has several instructions and directives
;used in it. The code has few instructions for purpose of testing only.
;Instructions related to function calls and stack operations are also
;tested in the example.
;
;The semicolon is used to lead an inline documentation.
;Function calls also implemented, see description at end of file. References
;also present at the end of file.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Directives
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
      ;the current file preserves eight-byte alignment of the stack.
	  ;The linker checks that any code that requires eight-byte alignment of the
	  ;stack is only called, directly or indirectly, by code that preserves
	  ;eight-byte alignment of the stack.
	  PRESERVE8
      ;The THUMB directive instructs the assembler to interpret subsequent
	  ;instructions as T32 instructions.
      THUMB

; Vector Table Mapped to Address 0 at Reset
; Linker requires __Vectors to be exported
      AREA    RESET, DATA, READONLY
      EXPORT  __Vectors

__Vectors
	; stack pointer value when stack is empty, this assumes
	;that the stack is located at memory such that the initial MSP.
	;points to address 0x20000500. This memory location should be in SRAM,
	;configure these memory addresses using the linker scripts or
	;"options for Target1 in keil".
	;The processor uses a full descending stack.
	;This means the stack pointer holds the address of the last
	;stacked item in memory. When the processor pushes a new item
	;onto the stack, it decrements the stack pointer and then
	;writes the item to the new memory location.
	DCD  0x20000500

	; reset vector
	DCD  Reset_Handler

	;The ALIGN directive aligns the current location to a specified boundary by
	;padding with zeros or NOP instructions.
	ALIGN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; The program instructions.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    AREA    MYCODE, CODE, READONLY

	ENTRY

;;;;;;; Function definitions ;;;;;;;

	; Linker requires Reset_Handler
	EXPORT Reset_Handler

Reset_Handler
;;;;;;;;;;User Code Starts from the next line;;;;;;;;;;;;

	  MOV R0, #0x12

START
	  ADD R0, R0, #0x4
	  MOV R1, #0x16
	  MOV R2, #0x27
	  MOV R3, #0x56
	  PUSH {R1}
	  PUSH {R2}
	  ADD R0, R0, #0x5
	  BL fun3add12
	  POP {R4}
	  POP {R5}
   	  B  START


fun1add6	PROC
			MOV R6, #0x6
			BX LR
			ENDP


fun2add9	PROC
			PUSH {LR}
			MOV R6, #0x9
			BL fun1add6
			POP {PC}
			ENDP


fun3add12	PROC
			PUSH {LR}
			MOV R6, #0x12
			BL fun2add9
			POP {PC}
			ENDP

			END	;End of source

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	Refererences
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;(1). The code reference is taken from 
;	[University of Regina, CS-301 course ](https://www.labs.cs.uregina.ca/301/ARM-subroutine/lecture.php).
;	The main site for above is - https://www.labs.cs.uregina.ca/301/index.php
;
;(2). Tried implementing Function calls as per the below C snippet
;	Refrence -
;	[Assembly language PPT from book jonathon Volvano Book web, lec:4,5](https://users.ece.utexas.edu/~valvano/Volume1/)

;	;;; See Code Below ;;;;;;
	
;	void Fun1(void){
;	// body of Fun1
;	add value '6' to 'R0'
;	}
;	void Fun2(void){
;	// body of Fun2
;	  Fun1();
;	}
;	void Fun3(void){
;	// body of Fun3
;	  Fun2();
;	}
;	int main(void){
;	  while(1){
;	    Fun3();
;	  }
;	}


; End of File ;
