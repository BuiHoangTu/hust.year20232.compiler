#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define IDENT_MAX_LEN 20
#define MAX_NUM_LENGTH 6
#define MAX_STR_LENGTH 20

typedef enum
{
    NONE = 0,
    IDENT,
    NUMBER,
    BEGIN,
    CALL,
    CONST,
    DO,
    ELSE,
    END,
    FOR,
    IF,
    ODD,
    PROCEDURE,
    PROGRAM,
    THEN,
    TO,
    VAR,
    WHILE,
    PLUS,
    MINUS,
    TIMES,
    SLASH,
    EQU,
    NEQ,
    LSS,
    LEQ,
    GTR,
    GEQ,
    LPARENT,
    RPARENT,
    LBRACK,
    RBRACK,
    PERIOD,
    COMMA,
    SEMICOLON,
    ASSIGN,
    PERCENT

} TokenType;

static const char *TOKEN_TYPE_NAME[] = {
    "NONE",
    "IDENT",
    "NUMBER",
    "BEGIN",
    "CALL",
    "CONST",
    "DO",
    "ELSE",
    "END",
    "FOR",
    "IF",
    "ODD",
    "PROCEDURE",
    "PROGRAM",
    "THEN",
    "TO",
    "VAR",
    "WHILE",
    "PLUS",
    "MINUS",
    "TIMES",
    "SLASH",
    "EQU",
    "NEQ",
    "LSS",
    "LEQ",
    "GTR",
    "GEQ",
    "LPARENT",
    "RPARENT",
    "LBRACK",
    "RBRACK",
    "PERIOD",
    "COMMA",
    "SEMICOLON",
    "ASSIGN",
    "PERCENT",
    "COMMENT"};

typedef struct token
{
    TokenType type;
    int number;
    char id[IDENT_MAX_LEN + 1];
} Token;

typedef struct lexical_stream
{
    FILE *source;
    char lastChar;
} LexicalStream;

LexicalStream *createLexicalStream(char *filePath)
{
    LexicalStream *out = malloc(sizeof(LexicalStream));

    out->lastChar = ' ';
    out->source = fopen(filePath, "r");

    return out;
}

/// @brief free the lexical stream
/// @param ls lexical stream
/// @return 0 if success, else return error code of fclose(ls->source)
int freeLexicalStream(LexicalStream *ls)
{
    int res = fclose(ls->source);
    if (res != 0)
    {
        return res;
    }
    free(ls);
    return 0;
}

Token nextToken(LexicalStream *lexicalStream)
{
    Token token;
    char c = lexicalStream->lastChar;

    // Skip whitespace
    while (isspace(c))
    {
        c = fgetc(lexicalStream->source);
    }

    // End of file
    if (c == EOF)
    {
        token.type = NONE;
        return token;
    }

    // Check for single-character tokens
    switch (c)
    {
    case '+':
        token.type = PLUS;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '-':
        token.type = MINUS;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '*':
        token.type = TIMES;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '/':
        token.type = SLASH;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '=':
        token.type = EQU;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case ':':
        if ((c = fgetc(lexicalStream->source)) == '=')
        {
            token.type = ASSIGN;
            lexicalStream->lastChar = getc(lexicalStream->source);
            break;
        }
        else
        {
            token.type = NONE;
            break;
        }
    case '<':
        if ((c = fgetc(lexicalStream->source)) == '>')
        {
            token.type = NEQ;
            lexicalStream->lastChar = getc(lexicalStream->source);
        }
        else if (c == '=')
        {
            token.type = LEQ;
            lexicalStream->lastChar = getc(lexicalStream->source);
        }
        else
        {
            lexicalStream->lastChar = c;
            token.type = LSS;
        }
        break;
    case '>':
        if ((c = fgetc(lexicalStream->source)) == '=')
        {
            token.type = GEQ;
            lexicalStream->lastChar = getc(lexicalStream->source);
        }
        else
        {
            lexicalStream->lastChar = c;
            token.type = GTR;
        }
        break;
    case '(':
        token.type = LPARENT;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case ')':
        token.type = RPARENT;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '[':
        token.type = LBRACK;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case ']':
        token.type = RBRACK;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '.':
        token.type = PERIOD;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case ',':
        token.type = COMMA;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case ';':
        token.type = SEMICOLON;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    case '%':
        token.type = PERCENT;
        lexicalStream->lastChar = getc(lexicalStream->source);
        break;
    default:
        // Check for identifiers or numbers
        if (isdigit(c))
        {
            int numLength = 1;

            token.type = NUMBER;
            token.number = c - '0';
            while (isdigit(c = fgetc(lexicalStream->source)))
            {
                token.number = token.number * 10 + (c - '0');
                numLength++;
                if (numLength >= MAX_NUM_LENGTH)
                {
                    token.type = NONE;
                    break;
                }
            }
            lexicalStream->lastChar = c;
        }
        else if (isalpha(c))
        {
            token.type = IDENT;
            token.id[0] = c;
            int i = 1;
            while (isalnum(c = fgetc(lexicalStream->source)))
            {
                if (i >= IDENT_MAX_LEN)
                {
                    token.type = NONE;
                    break;
                }
                token.id[i++] = c;
            }
            token.id[i] = '\0';
            lexicalStream->lastChar = c;

            //// check other keywords
            if (strcmp("begin", token.id) == 0)
            {
                token.type = BEGIN;
            }
            else if (strcmp("end", token.id) == 0)
            {
                token.type = END;
            }
            else if (strcmp("if", token.id) == 0)
            {
                token.type = IF;
            }
            else if (strcmp("then", token.id) == 0)
            {
                token.type = END;
            }
            else if (strcmp("while", token.id) == 0)
            {
                token.type = WHILE;
            }
            else if (strcmp("do", token.id) == 0)
            {
                token.type = DO;
            }
            else if (strcmp("call", token.id) == 0)
            {
                token.type = CALL;
            }
            else if (strcmp("odd", token.id) == 0)
            {
                token.type = ODD;
            }
            else if (strcmp("to", token.id) == 0)
            {
                token.type = TO;
            }
            else if (strcmp("const", token.id) == 0)
            {
                token.type = CONST;
            }
            else if (strcmp("var", token.id) == 0)
            {
                token.type = VAR;
            }
            else if (strcmp("procedure", token.id) == 0)
            {
                token.type = PROCEDURE;
            }
            else if (strcmp("program", token.id) == 0)
            {
                token.type = PROGRAM;
            }
            else if (strcmp("else", token.id) == 0)
            {
                token.type = ELSE;
            }
            else if (strcmp("for", token.id) == 0)
            {
                token.type = FOR;
            }
        }
        else
        {
            // TODO: Handle unrecognized characters
            token.type = NONE;
        }
        break;
    }

    return token;
}

/// @brief Convert token to a readable format, overflow data are truncated
/// @param token
/// @return string of readable format that need freeing after use
char *tokenToString(Token token)
{
    int resLength = (MAX_NUM_LENGTH > MAX_STR_LENGTH ? MAX_NUM_LENGTH : MAX_STR_LENGTH) + 10;
    char *result = malloc(resLength + 1);

    tokenToString_static(token, result, resLength);

    return result;
}

/// @brief Convert token to a readable format, overflow data are truncated. Result is written to des
/// @param token
/// @param des destination string, which must be already initialized
/// @param desLength max length of destination
/// @return length of returned string
int tokenToString_static(Token token, char *des, int desLength)
{
    int res = 0;

    switch (token.type)
    {
    case NUMBER:
        res = snprintf(des, desLength, "NUMBER(%d)", token.number);
        break;
    case IDENT:
        res = snprintf(des, desLength, "IDENT(%s)", token.id);
        break;
    default: // keywords
        res = snprintf(des, desLength, "%s", TOKEN_TYPE_NAME[token.type]);
        break;
    }

    return res;
}