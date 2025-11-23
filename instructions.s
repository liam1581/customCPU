; Comments (only work at the start of a line, sorry)

; NUMBER TYPES
$ for HEX
% for BIN
# for DEC

; REGISTERS
A
B
C

; INSTRUCTIONS
LD VAL REG     VAL->REG       0b0001
ST ADDR REG    ADDR=REG       0b0010
NOP                           0b0011
HLT                           0b0100
ADD VAL REG    VAL+REG->REG   0b0101
SUB VAL REG    VAL-REG->REG   0b0110
MUL VAl REG    VAL*REG->REG   0b0111

; PSEUDO INSTRUCTIONS, BUT SADLY INSTRUCTIONS
.word ADDR REG ADRR=REG (rom) 0b0000

; 4 bits for instructions
; 8 bits in a reg
; 8 bits for addr (rom/ram)