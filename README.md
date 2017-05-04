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
