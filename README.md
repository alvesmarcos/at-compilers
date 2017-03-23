# Sobre
Repositório com todas as atividades do curso Construção de Compiladores I.

--------

## Atividade 01 (26/01/2017)
Implementação de um trecho de código nos três níveis de abstração.

**C++**
```cpp
int main(){
	int x = 3;
	int y = 1;
	int z = 0;

	if(x==y)
		z = 0;
	z = x + y * 5 - 2;
	return 0;
}
```

**Assembly GAS/AT&T**

 ```assembly

.SECTION .data
	z:
		.int 0
	y:
		.int 1

.SECTION .bss
	.lcomm	x, 4

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
 **Microcode**

Os comandos utilizados para o microcode estão especifícados abaixo.

|Comando|Código|Descrição|
|:--------:|:--------:|---------|
|[ADD]	 | 000 | Recebe um valor constante e adiciona ao acumulador|
|[IMUL]  | 001 | Recebe um valor constante e multiplica pelo acumulador|
|[LOAD]	 | 010 | Carrega um valor constante na memória|
|ADD		 | 100 | Recebe um endereço e adiciona o valor contido no endereço ao acumulador|
|JNZ		 | 110 | Pula para linha específica caso seja diferente de 0|
|LOAD	   | 101 | Carrega o valor contido no endereço na memória|
|STORE	 | 111 | Salva o que está no acumulador no parâmetro específicado|
|XOR	 	 | 011 | Operação é verdade (1) quando as variáveis assumirem valores diferentes entre si.|

 Tabela de endereços das variáveis utilizadas no programa.

|$|var|
|:--:|:--:|
|0000001| z|
|0000011| y|
|0000111| x|

Definição do microcode.

|comando|flag de sinal (+/-)|endereço/constantes|
|:--:|:--:|:--:|
|000|1|0000001|

```
01: [LOAD]	3
02: STORE	x
03:
04: LOAD 	y
05: XOR	 	x
06: JNZ	    LINHA 10
07:
08: STORE 	z
09:
10: LOAD 	y
11: [IMUL] 	5
12: ADD 	x
13: [ADD]	-2
14:
15: STORE 	z

=============================

010	0 0000011
111	0 0000111

101 0 0000011
011	0 0000111
110	0 0001010

111 0 0000001

101 0 0000011
001 0 0000101
100 0 0000111
000 1 0000010

111 0 0000001
```

## Atividade 02 (02/02/2017)

1. **RE** := (0 | 1) * (00 | 10 | 11)   
2.
   - aa
   - a, b, bb, bbb ...
3. DFA

  ![DFA](https://github.com/alvesmarcos/at-compilers/blob/master/media/at023.png)

4.
   - S → aX  
     X → aX | bX | cX | ε
   - S → a | bc | bZ  
     Z → bZ | a
5.
   - DFA α1

   ![DF1](https://github.com/alvesmarcos/at-compilers/blob/master/media/at026a.png)

   - DFA α2

   ![DF2](https://github.com/alvesmarcos/at-compilers/blob/master/media/at026b.png)

## Atividade 03 (09/02/2017)
Adaptação de autômato finito dado em sala para que ele seja compatível com o Léxico do projeto final.

![DFA03](https://github.com/alvesmarcos/at-compilers/blob/master/media/at03.png)

## Atividade 05 (09/03/2017) 

1. 
   - S → aSdd | bXc  
     X → bXc | ε
	 
