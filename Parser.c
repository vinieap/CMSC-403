#include "Parser.h"

/***
 * Consume current token for comparison
 ***/
void consume(struct lexics *allLexs, struct lexics *currentLex) {
    *currentLex = allLexs[currentPosition++];
}

/***
 * Checks if the expected token is equal to the actual token parsed
 ***/
_Bool compare(int expectedToken, struct lexics *allLexs, struct lexics *currentLex) {
    if(currentLex->token == expectedToken) {
        consume(allLexs, currentLex);
        return TRUE;
    }
    return FALSE;
}

/***
 * Function -> Header Body
 ***/
_Bool parseFunction(struct lexics *allLexs, struct lexics *currentLex) {
    return parseHeader(allLexs, currentLex) && parseBody(allLexs, currentLex);
}

/***
 * Header -> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
 ***/
_Bool parseHeader(struct lexics *allLexs, struct lexics *currentLex) {
    return compare(VARTYPE, allLexs, currentLex) && compare(IDENTIFIER, allLexs, currentLex) && compare(LEFT_PARENTHESIS, allLexs, currentLex) && (currentLex->token==VARTYPE ? parseArgDecl(allLexs, currentLex) : TRUE) && compare(RIGHT_PARENTHESIS, allLexs, currentLex);
}

/***
 * ArgDecl -> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
 ***/
_Bool parseArgDecl(struct lexics *allLexs, struct lexics *currentLex) {
    _Bool var = compare(VARTYPE, allLexs, currentLex);
    _Bool iden = compare(IDENTIFIER, allLexs, currentLex);
    _Bool multipleArgs = TRUE;
    //Optional
    while(currentLex->token == COMMA) {
       consume(allLexs, currentLex);
       multipleArgs = compare(VARTYPE, allLexs, currentLex) && compare(IDENTIFIER, allLexs, currentLex); 
    }

    return var && iden && multipleArgs;
}

/***
 * Body -> LEFT_BRACKET [statement-list] RIGHT_BRACKET
 ***/
_Bool parseBody(struct lexics *allLexs, struct lexics *currentLex) {
    return compare(LEFT_BRACKET, allLexs, currentLex) && (currentLex->token==RIGHT_BRACKET ? TRUE : parseStatementList(allLexs, currentLex)) && compare(RIGHT_BRACKET, allLexs, currentLex);
}

/***
 * Statement-List -> Statement {Statement}
 ***/
_Bool parseStatementList(struct lexics *allLexs, struct lexics *currentLex) {
    _Bool firstStatement = parseStatement(allLexs, currentLex);
    _Bool accurateStatement = TRUE;
    //Make sure there is at least 1 statement
    if(firstStatement) {
        while(currentLex->token == WHILE_KEYWORD || currentLex->token == RETURN_KEYWORD || currentLex->token == IDENTIFIER || currentLex->token == LEFT_BRACKET) {
            accurateStatement = accurateStatement && parseStatement(allLexs, currentLex);
        }
        return accurateStatement;
    }
    return firstStatement;
}

/***
 * Statement -> While-Loop | Return | Assignment | Body
 ***/
_Bool parseStatement(struct lexics *allLexs, struct lexics *currentLex) {
    _Bool options = FALSE;

    //Check which one is the correct path to parse
    switch(currentLex->token) {
        case WHILE_KEYWORD:
            options = parseWhileLoop(allLexs, currentLex);
            break;
        case RETURN_KEYWORD:
            options = parseReturn(allLexs, currentLex);
            break;
        case IDENTIFIER:
            options = parseAssignment(allLexs, currentLex);
            break;
        case LEFT_BRACKET:
            options = parseBody(allLexs, currentLex);
            break;
    }

    return options;
}

/***
 * While-Loop -> WHILE_KEYWORD LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS Statement
 ***/
_Bool parseWhileLoop(struct lexics *allLexs, struct lexics *currentLex) {
    return compare(WHILE_KEYWORD, allLexs, currentLex) && compare(LEFT_PARENTHESIS, allLexs, currentLex) && parseExpression(allLexs, currentLex) && compare(RIGHT_PARENTHESIS, allLexs, currentLex) && parseStatement(allLexs, currentLex);
}

/***
 * Return -> RETURN_KEYWORD Expression EOL
 ***/
_Bool parseReturn(struct lexics *allLexs, struct lexics *currentLex) {
    return compare(RETURN_KEYWORD, allLexs, currentLex) && parseExpression(allLexs, currentLex) && compare(EOL, allLexs, currentLex);
}

/***
 * Assignment -> IDENTIFIER EQUAL Expression EOL
 ***/
_Bool parseAssignment(struct lexics *allLexs, struct lexics *currentLex) {
    return compare(IDENTIFIER, allLexs, currentLex) && compare(EQUAL, allLexs, currentLex) && parseExpression(allLexs, currentLex) && compare(EOL, allLexs, currentLex);
}

/***
 * Expression -> Term {BINOP Term} | LEFT_PARENTHESIS Expression RIGHT_PARENTHESIS
 ***/
_Bool parseExpression(struct lexics *allLexs, struct lexics *currentLex) {
    _Bool termOrexpression = TRUE;
    //Check for term first
    if(parseTerm(allLexs, currentLex)) {
        while(currentLex->token == BINOP) {
            consume(allLexs, currentLex);
            termOrexpression = termOrexpression && parseTerm(allLexs, currentLex);
        }
    }
    //If no term then check for LEFT_PARENTHESIS
    else if(currentLex->token == LEFT_PARENTHESIS){
        consume(allLexs, currentLex);
        termOrexpression = termOrexpression && parseExpression(allLexs, currentLex);
        if(currentLex->token == RIGHT_PARENTHESIS) {
            consume(allLexs, currentLex);
        }
        else {
            return FALSE;
        }
    }
    //Neither option is valid
    else {
        return FALSE;
    }
    return termOrexpression;
}

/***
 * Term -> IDENTIFIER | NUMBER
 ***/
_Bool parseTerm(struct lexics *allLexs, struct lexics *currentLex) {
    if(currentLex->token == IDENTIFIER || currentLex->token == NUMBER) {
        consume(allLexs, currentLex);
        return TRUE;
    }
    return FALSE;
}

/***
 * Required parser function to start parsing
 ***/
_Bool parser(struct lexics *someLexics, int numberOfLexics) {
    struct lexics currentLex;

    consume(someLexics, &currentLex);

    _Bool finalResult = parseFunction(someLexics, &currentLex);

    //Check for extra tokens leftover
    if(currentLex.token != 0) {
        finalResult = FALSE;
    }

    return finalResult;
}