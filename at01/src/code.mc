# ++
# Author: Marcos Alves
# --

LOAD	x
NEXT
STORE	3
NEXT
SET 	"A"
NEXT
STORE 	"M"
NEXT

LOAD 	y
XOR 	"M"
NEXT 			
JZ	    LINHA 23
LOAD 	z
NEXT
STORE 	0
NEXT

LOAD 	y
NEXT 	
SET 	"A"
NEXT 	
STORE 	"M"
NEXT
IMUL 	5
NEXT

SET 	"A"
NEXT
STORE   "R"
NEXT

LOAD 	x
NEXT
ADD		"M"
NEXT

SET 	"A"
NEXT
STORE   "R"
NEXT

ADD		-2
NEXT

LOAD 	z
NEXT	
STORE 	"R"


1. LOAD
2. STORE
3. NEXT
4. SET
5. XOR
6. ADD
7. MUL
8. JE
