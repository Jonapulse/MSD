
#ifndef parse_hpp
#include "expr.h"
#include <iostream>
#include <sstream>
#include <assert.h>
#define parse_hpp

#include <stdio.h>

#endif

Expr *parse_num(std::istream &in);
Expr *parse_expr(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr *parse_multicand(std::istream &in);

Expr *parse_str(std::string str); //For testing

static void consume(std::istream &in, char expected);
static void skip_whitespace(std::istream &in);