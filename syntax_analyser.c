//
// Created by tu on 16/05/2024.
//

#include "syntax_analyser.h"
#include "lexical_parser.h"

Token token;

void error(const char msg[]) {
    printf("Error : %s\n", msg);
    exit(1);
}

void factor() {

}

void term() {
    factor();
	while (token.type == TIMES || token.type == SLASH)
	{
		token = nextToken();
		factor();
	}
}

void expression() {
    if (token.type == PLUS || token.type == MINUS ) token.type = nextToken();
	term();
	while (token.type == PLUS || token.type == MINUS )
    {
		token = nextToken();
		term();
	}
}

void condition() {
    expression();
	if (token.type == EQU || token.type == NEQ || token.type == LSS ||   
       token.type == LEQ || token.type == GTR || token.type == GEQ)
    {
		token = nextToken();
		expression();
	} 
    else 
    {
		error("Condition: Syntax Error...");
	}
}

void statement() {
    if (token.type == IDENT) // First statement
    {
		token = nextToken();	//array variable ?

        if (token.type == LBRACK) 
        {
            token = nextToken();
			expresion();

            token = nextToken();
            if (token.type == RBRACK) {
                token = nextToken();
            }
            else
            {
                error("Statement: Missing RBRACK operator in First statement...");
            }
        }

		if(token == ASSIGN)
        {
			token = nextToken();
			expresion();

            token = nextToken();
		}
        else 
        {
            error("Statement: Missing ASSIGN operator in First statement...");
        }
	} 
	else if (token.type == CALL) // Second statement
    {
        token = nextToken(); // assign current token

        if (token.type == IDENT) 
        {
            token = nextToken(); // find next token

            if (token.type == LPARENT) 
            {
                do 
                {
                    token = nextToken();
                    expression();

                    token = nextToken();
                } while (token.type == COMMA)

                if (token.type == RPARENT)
                {
                    token = nextToken();
                }
                else 
                {
                    error("Statement: Missing RPARENT operator in Second statement...");
                }
            }
        }
        else
        {
            error("Statement: Missing IDENT operator in Second statement...");
        }
    }
    else if (token.type == BEGIN) // Third statement
    {
        do
        {
            token = nextToken();
            statement();

            token = nextToken();
        } while (token.type == SEMICOLON)
        
        if (token.type == END) 
        {
            token = nextToken();
        }
        else
        {
            error("Statement: Missing END operator in Third statement...");
        }
    }
    else if (token.type == IF) // Fourth statement
    {
        token = nextToken();
        condition();

        if (token.type == THEN) {
            token = nextToken();
            statement();

            token = nextToken();

            if (token.type == ELSE) 
            {
                token = nextToken();
                statement();

                token = nextToken();
            }
        } 
        else
        {
            error("Statement: Missing THEN operator in Fourth statement...");
        }
    }
    else if (token.type == WHILE) // Fifth statement
    {
        token = nextToken();
        condition();

        if (token.type == DO) {
            token = nextToken();
            statement();

            token = nextToken();
        } 
        else
        {
            error("Statement: Missing DO operator in Fifth statement...");
        }
    }
    else if (token.type == FOR) // Sixth statement
    {
        token = nextToken();

        if (token.type == IDENT) 
        {
            token = nextToken();

            if (token.type == ASSIGN) 
            {
                token = nextToken();
                expression();

                token = nextToken();

                if (token.type == TO)
                {
                    token = nextToken();
                    expression();

                    if (token.type == DO) {
                        token = nextToken();
                        statement();

                        token = nextToken();
                    } 
                    else
                    {
                        error("Statement: Missing DO operator in Sixth statement...");
                    }
                } 
                else 
                {
                    error("Statement: Missing TO operator in Sixth statement...");
                }
            }
            else 
            {
                error("Statement: Missing ASSIGN operator in Sixth statement...");
            }
        }
        else
        {
            error("Statement: Missing IDENT operator in Sixth statement...");
        }
    }
}

void block() {

}

void program() {

}
