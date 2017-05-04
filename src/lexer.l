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

int yywrap() {
  return 1;
}

int main(void) {
  yylex();

  return 0;
}