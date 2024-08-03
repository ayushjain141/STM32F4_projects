;The semicolon is used to lead an inline documentation.
;This is the first ARM Assembly language program you see in the lab.
;This program skeleton was from Dave Duguid and Trevor Douglas in summer 2013.
;When you write your program, you could have your info at the top document block.
;For Example:  Your Name, Student Number, what the program is for, and what it does etc.

;;; Directives
          PRESERVE8
          THUMB

; Vector Table Mapped to Address 0 at Reset
; Linker requires __Vectors to be exported
 
          AREA    RESET, DATA, READONLY
          EXPORT  __Vectors

__Vectors
		  DCD  0x20000500 ; stack pointer value when stack is empty, this assumes
			;that the stack is located at memory such that the initial MSP.
			;points to address 0x20000500. This memory location should be in SRAM,
			;configure these memory addresses using the linker scripts or
			;"options for Target1 in keil".
			;The processor uses a full descending stack. 
			;This means the stack pointer holds the address of the last 
			;stacked item in memory. When the processor pushes a new item 
			;onto the stack, it decrements the stack pointer and then 
			;writes the item to the new memory location.

          DCD  Reset_Handler  ; reset vector

          ALIGN

; The program
; Linker requires Reset_Handler

          AREA    MYCODE, CODE, READONLY

   	  ENTRY
   	  EXPORT Reset_Handler

Reset_Handler
;;;;;;;;;;User Code Starts from the next line;;;;;;;;;;;;

	  MOV R0, #12

STOP
	  ADD R0, R0, #4
	  MOV R1, #16
	  MOV R2, #27
	  MOV R3, #56
	  PUSH {R1}
	  PUSH {R2}
	  PUSH {R3}
	  ADD R0, R0, #5
	  POP {R4}
	  POP {R5}
	  POP {R6}
   	  B  STOP

      END	;End of t
