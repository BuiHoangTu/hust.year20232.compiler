#ifndef LEXICAL_PARSER
#define LEXICAL_PARSER

#include <stdio.h>

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

LexicalStream *createLexicalStream(const char *filePath);

/// @brief free the lexical stream
/// @param ls lexical stream
/// @return 0 if success, else return error code of fclose(ls->source)
int freeLexicalStream(LexicalStream *ls);


Token nextToken(LexicalStream *lexicalStream);


/// @brief Convert token to a readable format, overflow data are truncated
/// @param token
/// @return string of readable format that need freeing after use
char *tokenToString(Token token);

/// @brief Convert token to a readable format, overflow data are truncated. Result is written to des
/// @param token
/// @param des destination string, which must be already initialized
/// @param desLength max length of destination
/// @return length of returned string
int tokenToString_static(Token token, char *des, int desLength);

#endif // LEXICAL_PARSER