DMACOPY:
LD  DE,$FF80
RST $28
DB $00,$0D

DB $F5, $3E, $C1, $EA. $46, $FF, $3E, $28, $3D, $20, $FD, $F1, $D9

RET
