#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"

//Keeping track of position of current lexeme
//For consumption of token
static int currentPosition = 0;

//All function headers
void consume(struct lexics *allLexs, struct lexics *currentLex);
_Bool compare(int expectedToken, struct lexics *allLexs, struct lexics *curentLex);
_Bool parseFunction(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseHeader(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseArgDecl(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseBody(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseStatementList(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseStatement(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseWhileLoop(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseReturn(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseAssignment(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseExpression(struct lexics *allLexs, struct lexics *currentLex);
_Bool parseTerm(struct lexics *allLexs, struct lexics *currentLex);
_Bool parser(struct lexics *someLexics, int numberOfLexics);

#endif
