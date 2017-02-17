#include "lexer.h"

const std::map<Type, const char*> kGetType{
                                  {Type::kLiteralNumber, "Literal Number"},
                                  {Type::kOperator, "Operator"},
                                  {kEof, "Eof"}};
Scanner::Scanner(FILE* file){
  stream = file;
  ReadToken();
}

bool Scanner::LexerError(int ch){
  printf("ERROR: Caractere %c inesperado!!\n", ch);
  return false;
}

void Scanner::PrintToken(){
  int length = token.size();

  for(int i = 0 ; i < length; ++i)
    printf("Token: %s \t Lexeme: %s\n", kGetType.at(token[i].type), (token[i].lexeme).c_str());
}

bool Scanner::ReadToken(){
  bool done = true, is_buffer = false;
  int ch, buffer;
  Token t;

  while(done){
    if(is_buffer){
      ch = buffer;
      is_buffer = false;
    } else {
      ch = getc(stream);
    }
    while(ch==' ' or ch=='\n')
      ch = getc(stream);

    switch(ch){
      case '+': {
        t.type = Type::kOperator;
        t.value = Operator::kAdd;
        t.lexeme = "+";
        break;
      }
      case '-': {
        t.type = Type::kOperator;
        t.value = Operator::kSub;
        t.lexeme = "-";
        break;
      }
      case '*': {
        t.type = Type::kOperator;
        t.value = Operator::kMult;
        t.lexeme = "*";
        break;
      }
      case '/': {
        t.type = Type::kOperator;
        t.value = Operator::kDiv;
        t.lexeme = "/";
        break;
      }
      case EOF: {
        t.type = Type::kEof;
        t.value = 0;
        t.lexeme = "EOF";
        done = false;
        break;
      }
      default: {
        if(isdigit(ch)){
          bool flag = false;
          t.type = Type::kLiteralNumber;
          t.value = 0;
          t.lexeme = ch;
          ch = getc(stream);

          if(ch == '.')
            flag = true;

          while(isdigit(ch) or flag){
            t.lexeme += ch;
            ch = getc(stream);

            if(flag){
              if(not isdigit(ch))
                return LexerError(ch);
              flag = false;
            }
          }
          buffer = ch;
          is_buffer = true;

        } else {
          return LexerError(ch);
        }
      }
    }
    token.push_back(t);
  }
  return true;
}
