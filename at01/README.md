AT01
===================

Implementação de um trecho de código nos **três níveis** de abstração.

```python
y = 1 # valor não específicado na descrição
x = 3
if(x==y):
	z = 0
z = x + y * 5 - 2
```

```gas
# >>>> segmento de dados inicializados <<<<
.SECTION .data
	z:
		.int 0	
	y:
		.int 1

# >>>> segmento de dados NÃO inicializados <<<<	
.SECTION .bss
	.lcomm	x, 4 # lcomm varname, size

# >>>> labels do programa <<<<
.SECTION .text
	.globl _start

_start:
	movl	$3, x
	movl	(x), %ecx

	cmpl    (y), %ecx
	jne     .L01 
	movl    $0, (z)

.L01:
	movl	(y), %eax
 
 	imull  	$5, %eax

 	addl   	(x), %eax
 	subl   	$2, %eax

 	movl   	%eax, (z)

_exit:
	movl  	$1, %eax
	movl  	(z), %ebx
	int 	$0x80
```