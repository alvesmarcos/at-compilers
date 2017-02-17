#ifndef AT_COMPILERS_LEXER_H
#define AT_COMPILERS_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

// all types defined
enum Type {
  kLiteralNumber = 0,
  kOperator,
  kEof
};
// types operators
enum Operator {
  kAdd = 0,
  kSub,
  kMult,
  kDiv
};
// definition the Token
struct Token {
  Type type;
  int value;
  std::string lexeme;
};
// const map get values enum Type
extern const std::map<Type, const char*> kGetType;

// definition the Scanner
class Scanner {
  public:
    // constructor
    Scanner(FILE* file);
    // functions
    bool LexerError(int ch);
    void PrintToken();
  private:
    // data members
    FILE* stream;
    std::vector<Token> token;
    // functions
    bool ReadToken();
};
#endif //AT_COMPILERS_SRC_LEXER_H
