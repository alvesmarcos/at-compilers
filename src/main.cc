#include <iostream>
#include "lexer.h"

int main(){
  FILE* f;
  f = fopen("../media/file.txt", "r");

  Scanner* s = new Scanner(f);

  s->PrintToken();
  fclose(f);

  return 0;
}
