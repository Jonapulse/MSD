
#ifndef parse_hpp
#define parse_hpp
#include "expr.h"
#include "val.h"
#include <iostream>
#include <sstream>
#include <assert.h>
#include <stdio.h>

/**
 * \file parse.hpp
 * \brief parses input streams into expressions
 */

#endif

Expr *parse_expr(std::istream &in);
Expr *parse_comparg(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr *parse_multicand(std::istream &in);
Expr *parse_inner(std::istream &in);
Expr *parse_num(std::istream &in);
Expr* parse_var(std::istream &in);
Expr* parse_keyword(std::istream &in);
std::string parse_word(std::istream &in);

Expr *parse_str(std::string str); //For testing

static void consume(std::istream &in, char expected);
static void skip_whitespace(std::istream &in);