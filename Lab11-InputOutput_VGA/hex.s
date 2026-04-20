.global _start

_start:
    LDR R0, =0xFF200020     // Address of HEX3-HEX0
    MOV R1, #0x6D           // Encoding for digit '5'
    STR R1, [R0]            // Write to display

stop:
    B stop