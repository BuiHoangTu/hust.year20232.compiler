//
// Created by tu on 16/05/2024.
//

#include "syntax_analyser.h"
#include "lexical_parser.h"

#include <stdio.h>
#include <stdlib.h>

Token token;

void error(const char msg[], LexicalStream *lexicalStream) {
    printf("Error : %s\n", msg);
    printf("Line : %d\n\n", lexicalStream->line);
    exit(1);
}

void factor(LexicalStream *lexicalStream) {
    if(token.type == LPARENT){
		token = nextToken(lexicalStream);
		expression(lexicalStream);
		if (token.type != RPARENT)
		{
			error("Missing )", lexicalStream);
		}
	}else{
		error("Missing (", lexicalStream);
	}
}

void term(LexicalStream *lexicalStream) {
    factor(lexicalStream);
	while (token.type == TIMES || token.type == SLASH)
	{
		token = nextToken(lexicalStream);
		factor(lexicalStream);
	}
}

void expression(LexicalStream *lexicalStream) {
    if (token.type == PLUS || token.type == MINUS ) token = nextToken(lexicalStream);
	term(lexicalStream);
	while (token.type == PLUS || token.type == MINUS )
    {
		token = nextToken(lexicalStream);
		term(lexicalStream);
	}
}

void condition(LexicalStream *lexicalStream) {
    expression(lexicalStream);
	if (token.type == EQU || token.type == NEQ || token.type == LSS ||   
       token.type == LEQ || token.type == GTR || token.type == GEQ)
    {
		token = nextToken(lexicalStream);
		expression(lexicalStream);
	} 
    else 
    {
		error("Condition: Syntax Error...", lexicalStream);
	}
}

void statement(LexicalStream *lexicalStream) {
    if (token.type == IDENT) // First statement
    {
		token = nextToken(lexicalStream);	//array variable ?

        if (token.type == LBRACK) 
        {
            token = nextToken(lexicalStream);
			expression(lexicalStream);

            token = nextToken(lexicalStream);
            if (token.type == RBRACK) {
                token = nextToken(lexicalStream);
            }
            else
            {
                error("Statement: Missing RBRACK operator in First statement...", lexicalStream);
            }
        }

		if(token.type == ASSIGN)
        {
			token = nextToken(lexicalStream);
			expression(lexicalStream);

            token = nextToken(lexicalStream);
		}
        else 
        {
            error("Statement: Missing ASSIGN operator in First statement...", lexicalStream);
        }
	} 
	else if (token.type == CALL) // Second statement
    {
        token = nextToken(lexicalStream); // assign current token

        if (token.type == IDENT) 
        {
            token = nextToken(lexicalStream); // find next token

            if (token.type == LPARENT) 
            {
                do 
                {
                    token = nextToken(lexicalStream);
                    expression(lexicalStream);

                    token = nextToken(lexicalStream);
                } while (token.type == COMMA);

                if (token.type == RPARENT)
                {
                    token = nextToken(lexicalStream);
                }
                else 
                {
                    error("Statement: Missing RPARENT operator in Second statement...", lexicalStream);
                }
            }
        }
        else
        {
            error("Statement: Missing IDENT operator in Second statement...", lexicalStream);
        }
    }
    else if (token.type == BEGIN) // Third statement
    {
        do
        {
            token = nextToken(lexicalStream);
            statement(lexicalStream);

            token = nextToken(lexicalStream);
        } while (token.type == SEMICOLON);
        
        if (token.type == END) 
        {
            token = nextToken(lexicalStream);
        }
        else
        {
            error("Statement: Missing END operator in Third statement...", lexicalStream);
        }
    }
    else if (token.type == IF) // Fourth statement
    {
        token = nextToken(lexicalStream);
        condition(lexicalStream);

        if (token.type == THEN) {
            token = nextToken(lexicalStream);
            statement(lexicalStream);

            token = nextToken(lexicalStream);

            if (token.type == ELSE) 
            {
                token = nextToken(lexicalStream);
                statement(lexicalStream);

                token = nextToken(lexicalStream);
            }
        } 
        else
        {
            error("Statement: Missing THEN operator in Fourth statement...", lexicalStream);
        }
    }
    else if (token.type == WHILE) // Fifth statement
    {
        token = nextToken(lexicalStream);
        condition(lexicalStream);

        if (token.type == DO) {
            token = nextToken(lexicalStream);
            statement(lexicalStream);

            token = nextToken(lexicalStream);
        } 
        else
        {
            error("Statement: Missing DO operator in Fifth statement...", lexicalStream);
        }
    }
    else if (token.type == FOR) // Sixth statement
    {
        token = nextToken(lexicalStream);

        if (token.type == IDENT) 
        {
            token = nextToken(lexicalStream);

            if (token.type == ASSIGN) 
            {
                token = nextToken(lexicalStream);
                expression(lexicalStream);

                token = nextToken(lexicalStream);

                if (token.type == TO)
                {
                    token = nextToken(lexicalStream);
                    expression(lexicalStream);

                    if (token.type == DO) {
                        token = nextToken(lexicalStream);
                        statement(lexicalStream);

                        token = nextToken(lexicalStream);
                    } 
                    else
                    {
                        error("Statement: Missing DO operator in Sixth statement...", lexicalStream);
                    }
                } 
                else 
                {
                    error("Statement: Missing TO operator in Sixth statement...", lexicalStream);
                }
            }
            else 
            {
                error("Statement: Missing ASSIGN operator in Sixth statement...", lexicalStream);
            }
        }
        else
        {
            error("Statement: Missing IDENT operator in Sixth statement...", lexicalStream);
        }
    }
}

void block(LexicalStream *lexicalStream) {

}

void program(LexicalStream *lexicalStream) {
    token = nextToken(lexicalStream);
    if(token.type=PROGRAM){
		token = nextToken(lexicalStream);

		if (token.type==IDENT){
			token = nextToken(lexicalStream);

			if(token.type==SEMICOLON){
				token = nextToken(lexicalStream);
				block(lexicalStream);

				if(token.type==PERIOD)
					printf("Success");

				else error("Missing .", lexicalStream);
                
			}else error("Missing ;", lexicalStream);

		}else error("Missing program name", lexicalStream);

	}else error("Missing keyword 'Program'", lexicalStream);

}
