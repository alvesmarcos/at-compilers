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
	movl 	$3, x
	movl 	(x), %ecx

	cmpl 	(y), %ecx
	jne 	.L01
	movl 	$0, (z)

.L01:
	movl 	(y), %eax

	imull 	$5, %eax

	addl 	(x), %eax
	subl 	$2, %eax

	movl 	%eax, (z)

_exit:
	movl 	$1, %eax
	movl 	(z), %ebx
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
05: XOR 	x
06: JNZ 	LINHA 10
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

010 0 0000011
111 0 0000111

101 0 0000011
011 0 0000111
110 0 0001010

111 0 0000001

101 0 0000011
001 0 0000101
100 0 0000111
000 1 0000010

111 0 0000001
```

## Atividade 02 (02/02/2017)

1. Encontre expressões regulares considerando o alfabeto binário {0,1} que determine a seguinte linguagem: **L = {u| u não acabe com 01}**

```
(0 | 1) * (00 | 10 | 11)   
```
2. Considere as duas expressões regulares mostradas abaixo e resposta o que se pede:
	- r1 = a\* + b\*
	- r2 = ab\* + ba\* + b\*a + (a\*b)*

- Encontre um exemplo de string que corresponda a r1 mas não a r2;
```
aa
```
- Encontre um exemplo de string que corresponda a r1 e a r2.
```
a, b, bb, bbb ...
```

3. Construa um AFD para a linguagem com alfabeto {a,b,c} que não contenha palavras que possuam a sequência ac.

![DFA](https://github.com/alvesmarcos/at-compilers/blob/master/media/at023.png)

4. Dado o alfabeto Σ = {a,b,c} e as duas expressões α1 = a (a|b|c)\* e α2 = a|bc|b\*a:

* Especifique a gramática regular equivalente à expressão α1
```
S → aX  
X → aX | bX | cX | ε
```
* Especifique a gramática regular equivalente à expressão α2
```
S → a | bc | bZ  
Z → bZ | a
```
5. Construa os autômatos finitos determinísticos para as expressões α1 e α2 do exercício anterior.

- DFA α1

![DF1](https://github.com/alvesmarcos/at-compilers/blob/master/media/at026a.png)

- DFA α2

![DF2](https://github.com/alvesmarcos/at-compilers/blob/master/media/at026b.png)

## Atividade 03 (09/02/2017)
Adaptação de autômato finito dado em sala para que ele seja compatível com o Léxico do projeto final.

![DFA03](https://github.com/alvesmarcos/at-compilers/blob/master/media/at03.png)

## Atividade 04 (16/02/2017)
Implementação de um léxico para operações aritméticas utilizando as duas abordagens dadas em sala de aula.

Manulamente utilizando a linguagem C++
```cpp
if(std::isdigit(ch)){
	Type type = Type::kIntLiteral;
	std::string number(1, ch);
	ch = GetNextChar();
	
	while(std::isdigit(ch)){
		number += ch;
		ch = GetNextChar();
	}
	if(ch=='.') {
		number += ch;
		ch = GetNextChar();
    
		if(not isdigit(ch))
			LexerError("expected a digit after '.'");
		type = kRealLiteral;
    
		do {
			number += ch;
			ch = GetNextChar();
		} while(isdigit(ch));
	}
	this->queue_token.push(Token{number, line, type});
}
```
A resolução completa pode ser vista em ![lexer-pascal](https://github.com/alvesmarcos/lexer-pascal/blob/master/src/lex/scanner.cc)

Gerador léxico FLEX
```C
DIGIT[0-9]
OPERATOR[+ | - | \ | *]

%%
{DIGIT}+  { 
  printf("Integer number %s\n", yytext); 
}
{DIGIT}+"."{DIGIT}* {
  printf("Real number %s\n", yytext);
}
{OPERATOR} {
  printf("Operator %s\n", yytext);
}
%%

int main(void) {
  yylex();

  return 0;
}
```

## Atividade 05 (09/03/2017)

1. Encontre gramáticas livre de contexto que gerem as linguagens abaixo:

* L(G) = {a^**n** b^**m** c^**m** d^**2n** | n ≥ 0, m > 0} 
```
S → aSdd | bRc  
R → bRc | ε
```
* {w | w inicie e finalize com o mesmo símbolo}, considerando o alfabeto binário {0,1}
```
S → 0J0 | 1J1  
J → 0J | 1J | ε
```
* {w | |w| is ímpar}, considerando o alfabeto binário {0,1}
```
S → 0J | 1J  
J → 00J | 01J | 11J | 10J | ε
```
* {w | |w| é ímpar e o símbolo do meio é 0}, considerando o alfabeto binário {0,1}
```
J → 0J0 | 0J1 | 1J1 | 1J0 | 0
```

2. Explique porque a gramática abaixo é ambígua

>S → 0A | 1B
>
>A → 0AA | 1S | 1
>
>B → 1BB | 0S | 0

```
Gramática é ambígua se existe uma cadeia que pode ser gerada pela gramática em mais de um caminho.
```
>entrada: **11001100**

* Derivação ζ 
```
1B
11BB
1100S
11001B
110011BB
11001100
```
* Derivação ϕ
```
1B
11BB
110S1BB
1100A1BB
110011BB
11001100
```
3. Data a seguinte gramática livre de contexto ambígua, faça o que se pede:

>S → Ab | aaB
>
>A → a | Aa
>
>B → b

* Encontre uma string s gerada pela gramática que tem duas derivações mais a esquerda. Mostre estas derivações; 
```
aaB
aab
```
```
Ab
Aab
aab
```
* Desenhe as árvores sintáticas resultantes das duas derivações da string s.
```
   S
 / | \
a  a  B
      |
      b
```
```
    S
   / \
  A   b
 / \
A   a
|
a
```
## Atividade 06 (16/03/2017)

Retirar recursão a esquerda e não determinismo da gramática livre de contexto do projeto final.
```pascal
programa →
	program id ;
	declarações_variáveis
	declarações_de_subprogramas
	comando_composto
	.
```	
```pascal	
declarações_variáveis →
	var lista_declarações_variáveis
	| ε	
```
```
lista_declarações_variáveis →
	lista_de_identificadores : tipo ; lista_declarações_variáveis'
	
lista_declarações_variáveis' →	
	lista_de_identificadores : tipo ;  lista_declarações_variáveis'
	| ε
```
```
lista_de_identificadores →
	id lista_de_identificadores'

lista_de_identificadores' →
	, id lista_de_identificadores'
	| ε
```
```pascal	
tipo →
	integer
	| real
	| boolean
```
```
declarações_de_subprogramas → 
	declaração_de_subprograma; declarações_de_subprogramas 
	| ε
```
```pascal
declaração_de_subprograma →
	procedure id argumentos ;
	declarações_variáveis
	declarações_de_subprogramas
	comando_composto
```
```
argumentos →
	(lista_de_parametros)
	| ε
```
```
lista_de_parametros →
	lista_de_identificadores : tipo lista_de_parametros'
	
lista_de_parametros' → 
	; lista_de_identificadores : tipo lista_de_parametros'
	| ε
```
```pascal
comando_composto →
	begin
	comandos_opcionais
	end
```
```
comandos_opcionais →
	lista_de_comandos
	| ε
```
```
lista_de_comandos →
	comando lista_de_comandos'

lista_de_comandos' →
	; comando lista_de_comandos'
	| ε
```
```pascal
comando →
	variável := expressão
	| ativação_de_procedimento
	| comando_composto
	| if expressão then comando parte_else
	| while expressão do comando
```
```pascal
parte_else →
	else comando
	| ε
```
```pascal
variável →
	id
```
```
ativação_de_procedimento →
	id paramsϕ

paramsϕ → 
	ε 
	| (lista_de_expressões)
```
```
lista_de_expressões →
	expressão lista_de_expressões'

lista_de_expressões' →
	, expressão lista_de_expressões'
	| ε
```
```
expressão →
	expressão_simples paramsδ

paramsδ →
	op_relacional expressão_simples
	| ε
```
```
expressão_simples →
	termo expressão_simples'
	| sinal termo expressão_simples'

expressão_simples' →
	op_aditivo termo expressão_simples'
	| ε
```
```
termo →
	fator termo'
	
termo' → 
	op_multiplicativo fator termo'
	| ε
```
```pascal
fator →
	id paramsϕ
	| num_int
	| num_real
	| true
	| false
	| (expressão)
	| not fator
```
```pascal
sinal →
	+ | -
```
```pascal
op_relacional →
	= | <paramsκ | >paramsμ 
	
paramsκ →
	ε | = | > 

paramsμ →
	ε | =
```
```pascal
op_aditivo →
	+ | - | or
```
```pascal
op_multiplicativo →
	* | / | and
```	
## Atividade 09 (20/04/2017)

1. Responda:
* Quando se pode aplicar a otimização de eliminação de sub-expressão comum?
Suponha que a mesma expressão ocorre mais de uma vez em um trecho de programa:
```ruby
x = a + b
# ...
# ...
y = a + b
```
S a e b não são alterados, é possível guardar o valor da expressão a+b em uma variável temporária. No exemplo acima, se a variável *x* estiver disponível com mesmo valor, podemos usar o próprio *x*.
```ruby
x = a + b
# ...
# ...
y = x
```

* Qual o efeito que a quantidade de registradores tem no código gerado e por quê?

*"Os registradores estão no topo da hierarquia de memória, sendo assim, são o meio mais rápido de se armazenar um dado."*  

Seguindo a linha de pensamento da afirmação acima, podemos perceber que a quantidade de registradores está toltamente ligada ao código intermediário gerado, isto fica claro principalmente em expressões aritméticas onde temos várias variáveis auxíliares criadas, dependendo da quantidade, podemos passar todas as variáveis temporárias para dentro dos registradores tornando o processo mais rápido.

2. Mostre como o código intermediário a seguir pode ser otimizado. Justifique as otimizações.
* a.
```ASM
1 MOV a 0
2 JGT a 10 5
3 MOV x a
4 JMP 6
5 MOV x b
6 RTN
```
Como *a* é um valor constante, podemos substituir em todos os pontos que *a* aparece o seu valor constante. Como o desvio é formado somente por constantes, podemos retirar (false) ou substituir por um JUMP (true). Linha 5 não é utilizada, restou apenas o nosso código otimizado.
```ASM
1 MOV x 0
2 RTN
```
* b.
```ASM
1 MOV x 0
2 JGT x 10 7
3 MULT t1 y A
4 ADD t2 x t1
5 MOV x t2
6 JMP 2
7 RTN
```
Podemos retirar o comando *MULT t1 y A* do loop, já que o mesmo faz um cálculo constante.  
```ASM
1 MOV x 0
2 MULT t1 y A
3 JGT x 10 7
4 ADD t2 x t1
5 MOV x t2
6 JMP 3
7 RTN
```
* c.
```ASM
1 MOV a 0
2 MOV a p
3 JGT 0 a 17
4 DIV t1 a p
5 JGT t1 0.5 9
6 DIV t2 a p
7 ADD t3 f t2
8 MOV f t3
9 DIV t4 a p
10 JGT 0.5 t4 14
11 DIV t5 a p
12 SUB t6 f t5
13 MOV f t6
14 SUB t7 a 1
15 MOV a t7
16 JMP 3
17 MOV p f
```
Podemos retirar a linha 1 logo no começo, já que em seguida é atribuido um valor *p* para varriável. Substituir *t2*, *t4*, *t5* por apenas *t1* pois todos contém o mesmo valor (DIV t1 a p).
```ASM
1 MOV a p 
2 JGT 0 a 7 
3 DIV t1 a p  
4 SUB t2 f t1 
5 MOV f t2
6 SUB t2 a 1
7 JMP 2 
8 MOV p f
```
3. Indique qual o numero de registradores necessários para calcular as expressões a seguir. Lembrando que você precisa passar as instruções abaixo para a codificação de três endereços. (utilizem quantos registradores forem necessários)

* a. (a+b)\*(c-d)
```ASM
1 ADD t1 a b
2 SUB t2 c d
3 MULT t3 t1 t2
```

* b. (a+(b-c))\*((e-f)+(g-h))
```ASM
1 ADD t1 b c
2 SUB t2 a t1
3 SUB t3 e f
4 SUB t4 g h
5 ADD t5 t3 t4
4 MULT t6 t5 t2
```

* c. ((a-b)\*(c-d)+(e-f)\*(g-h))
```ASM
1 SUB t1 a b
2 SUB t2 c d
3 MULT t3 t1 t2
4 SUB t4 e f
5 SUB t5 g h
6 MULT t6 t4 t5
7 ADD t7 t3 t6
```
4. Refaça a questão anterior utilizando o menor número possível de registradores que você conseguir.

* a. (a+b)\*(c-d)
```ASM
1 ADD t1 a b
2 SUB t2 c d
3 MULT t3 t1 t2
```
* b. (a+(b-c))\*((e-f)+(g-h))
```ASM
1 ADD t1 b c
2 SUB t2 a t1
3 SUB t1 e f
4 SUB t3 g h
5 ADD t4 t1 t3
4 MULT t1 t4 t2
```
* c. ((a-b)\*(c-d)+(e-f)\*(g-h))
```ASM
1 SUB t1 a b
2 SUB t2 c d
3 MULT t3 t1 t2
4 SUB t1 e f
5 SUB t2 g h
6 MULT t4 t1 t2
7 ADD t1 t3 t4
```
