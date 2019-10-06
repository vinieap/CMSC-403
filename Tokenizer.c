#include "Tokenizer.h"

/***
 * Peak ahead at next character and put stream back to original position
 ***/
int peekAhead(FILE *inf)
{
    int ch;
    fpos_t currentPos; 

    fgetpos(inf, &currentPos); //Store original position of stream
    ch = fgetc(inf); //Read next character
    fsetpos(inf, &currentPos); //Restore to original position

    return ch;
}

/***
 * Check if VARTYPE | WHILE | RETURN | IDENTIFIER | Incorrect File
 * Uses 1 character look ahead
 * Returns -1 if not matching a lexeme
 ***/
int readLetters(char* buffer, FILE *inf)
{
    int numOfLetters = 1;
    int currChar;

    //Loop until not a letter or number and put character into buffer
    while (isLetter(peekAhead(inf)) || isDigit(peekAhead(inf)))
    {
        currChar = fgetc(inf);
        buffer[numOfLetters++] = currChar;
    }

    buffer[numOfLetters] = '\0';

    //Check which lexeme the buffer matches
    if((strcmp(buffer, "void")) == FALSE || (strcmp(buffer, "int")) == FALSE) {
        return VARTYPE;
    }
    else if ((strcmp(buffer, "while")) == FALSE)
    {
        return WHILE_KEYWORD;
    }
    else if ((strcmp(buffer, "return")) == FALSE)
    {
        return RETURN_KEYWORD;
    }
    else if (validIdentifier(buffer))
    {
        return IDENTIFIER;
    }

    return -1;
}

/***
 * Read full number and make sure it is a number
 ***/
_Bool readDigits(char *buffer, FILE *inf)
{
    int numOfDigits = 1;
    int currChar;

    //Loop until next character is not a digit
    //Add to buffer
    while (isDigit(peekAhead(inf)))
    {
        currChar = fgetc(inf);
        buffer[numOfDigits++] = currChar;
    }

    buffer[numOfDigits] = '\0';

    return validNumber(buffer);
}

/***
 * Creates new lexic
 ***/
struct lexics *nextLexic(FILE *inf)
{
    int currChar;
    struct lexics *currLexic = (struct lexics *) malloc(sizeof(struct lexics));

    currChar = fgetc(inf); //Get next character

    //Checks if end of file
    if(feof(inf)) {
            currLexic->token = 0;
            currLexic->lexeme[0] = '\0';
            return currLexic;
        }

    //Ignores whitespace
    while (currChar == ' ' || currChar == '\r' || currChar == '\n' || currChar == '\t')
    {
        currChar = fgetc(inf);
    }

    //Check which path needed to tokenize character
    switch (currChar)
    {
        case '(':
            currLexic->token = LEFT_PARENTHESIS;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        case ')':
            currLexic->token = RIGHT_PARENTHESIS;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        case '{':
            currLexic->token = LEFT_BRACKET;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        case '}':
            currLexic->token = RIGHT_BRACKET;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        case ',':
            currLexic->token = COMMA;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        case ';':
            currLexic->token = EOL;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        //All 3 tokenize identically
        case '+':
        case '*':
        case '%':
            currLexic->token = BINOP;
            currLexic->lexeme[0] = currChar;
            currLexic->lexeme[1] = '\0';
            break;
        //Check if just 1 equals or 2
        case '=':
            if (peekAhead(inf) == '=')
            {
                currChar = fgetc(inf);
                currLexic->token = BINOP;
                currLexic->lexeme[0] = '=';
                currLexic->lexeme[1] = '=';
                currLexic->lexeme[2] = '\0';
            }
            else
            {
                currLexic->token = EQUAL;
                currLexic->lexeme[0] = '=';
                currLexic->lexeme[1] = '\0';
            }
            break;
        //Make sure there is an equals after !
        case '!':
            if (peekAhead(inf) == '=')
            {
                currChar = fgetc(inf);
                currLexic->token = BINOP;
                currLexic->lexeme[0] = '!';
                currLexic->lexeme[1] = '=';
                currLexic->lexeme[2] = '\0';
            }
            else
            {
                return NULL;
            }
            break;
        //Something not easy to tokenize
        default:
        {
            char *buff = (char *)malloc(sizeof(char) * LEXEME_MAX); //Buffer for storing full number or name

            if(buff == NULL) {
                return NULL;
            }

            //Check if digit
            if (isDigit(currChar))
            {
                buff[0] = currChar;
                if (readDigits(buff, inf))
                {
                    currLexic->token = NUMBER;
                    strcpy(currLexic->lexeme, buff);
                }
                else
                {
                    return NULL;
                }
            }
            //Check if letter
            else if (isLetter(currChar))
            {
                buff[0] = currChar;
                int tokenValue = readLetters(buff, inf);
                if (!(tokenValue == -1)) //Invalid collection of letters and numbers
                {
                    currLexic->token = tokenValue;
                }
                else
                {
                    return NULL;
                }
                strcpy(currLexic->lexeme, buff);
            }
            //Some other symbol that is not valid
            else
            {
                return NULL;
            }
        }
    }
    
    return currLexic;
}

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf)
{
    struct lexics *next;
    *numLex = 0;

    //Loops until something is wrong or file is tokenized
    while ((next = nextLexic(inf)) != NULL)
    {
        
        if(next->lexeme[0] == '\0') {
            return TRUE;
        }

        aLex[(*numLex)] = *next;
        (*numLex)++;
    }

    //Returns False cause something was wrong
    if(next == NULL) {
        return FALSE;
    }

    return TRUE;
}
