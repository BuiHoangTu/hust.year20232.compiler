//
// Created by tu on 16/05/2024.
//

#ifndef INYEAR4_2_COMPILER_SYNTAX_ANALYSER_H
#define INYEAR4_2_COMPILER_SYNTAX_ANALYSER_H

#include "lexical_parser.h"


void factor(LexicalStream *lexicalStream);
void term(LexicalStream *lexicalStream);
void expression(LexicalStream *lexicalStream);
void condition(LexicalStream *lexicalStream);
void statement(LexicalStream *lexicalStream);
void block(LexicalStream *lexicalStream);
void program(LexicalStream *lexicalStream);

#endif //INYEAR4_2_COMPILER_SYNTAX_ANALYSER_H
