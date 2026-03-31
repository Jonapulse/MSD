#include "parse.hpp"
#include "catch.h"

/**
 * \file parse.cpp
 * \brief parses input streams into expressions
 */

Expr *parse_expr(std::istream &in)
{
    Expr* e = parse_comparg(in);

    skip_whitespace(in);

    int c = in.peek();
    if(c == '='){
        consume(in, '=');
        if(in.peek() != '=')
            throw std::runtime_error("Error: '=' not followed by 2nd '='");
        consume(in, '=');
        Expr* rhs = parse_expr(in);
        return new EqExpr(e, rhs);
    } else {
        return e;
    }

}

Expr *parse_comparg(std::istream &in)
{
    Expr* e = parse_addend(in);

    skip_whitespace(in);

    int c = in.peek();
    if(c == '+'){
        consume(in, '+');
        Expr* rhs = parse_expr(in);
        return new AddExpr(e, rhs);
    } else {
        return e;
    }
}

Expr *parse_addend(std::istream &in)
{
    Expr* e = parse_multicand(in);

    skip_whitespace(in);

    int c = in.peek();
    if (c == '*'){
        consume(in, '*');
        Expr* rhs = parse_addend(in);
        return new MultExpr(e, rhs);
    } else {
        return e;
    }
}

Expr *parse_multicand(std::istream &in)
{
    Expr* expr = parse_inner(in);

    skip_whitespace(in);

    while(in.peek() == '('){
		consume(in, '(');
		Expr* actual_arg = parse_expr(in);
		consume(in, ')');
		expr = new CallExpr(expr, actual_arg);
	}
	return expr;
}

Expr* parse_inner(std::istream &in){
    skip_whitespace(in);
	
	int c = in.peek();
	if((c == '-') || isdigit(c))
		return parse_num(in);
	else if (c == '(') {
		consume(in, '(');
		Expr *e = parse_expr(in);
		skip_whitespace(in);
		c = in.get();
		if(c != ')')
			throw std::runtime_error("missing close parenthesis");
		return e;
	} 
	else if (isalpha(c))
	{
		return parse_var(in); 
	}
	else if (c == '_')
	{
        consume(in, '_');
		return parse_keyword(in);
	} 
	else { 
		throw std::runtime_error("non-parseable input for char: " + std::to_string(c));
	}
}

Expr *parse_num(std::istream &in) {
    int n = 0;
    bool negative = in.peek() == '-';
    if(negative)
        consume(in, '-');
    
    while (1) {
        int c = in.peek();
        if (isdigit(c))
        {
            consume(in, c);
            n = n*10 + (c - '0');
        }
        else
            break;
    }

    if(negative)
        n *= -1;

    return new NumExpr(n);
}

Expr* parse_var(std::istream &in)
{
    return new VarExpr(parse_word(in));
}

Expr* parse_keyword(std::istream &in){
    std::string keyword = parse_word(in);
    if(keyword == "let")
    {
        skip_whitespace(in);
        std::string name = parse_word(in);
        Expr* rhs;
        Expr* lhs;

        //Parse rhs after "="
        skip_whitespace(in);
        int c = in.peek();
        if(c == '=')
        {
            consume(in, c);
            rhs = parse_expr(in);
        }
        else 
            throw std::runtime_error("_let not followed \"=\"");

        //Parse lhs after "_in"
        skip_whitespace(in);
        c = in.peek();
        if(c == '_'){
            consume(in, c);
            std::string inKeyword = parse_word(in);
            if(inKeyword != "in")
                throw std::runtime_error("_let not followed by _in");
            lhs = parse_expr(in);
        }
        else
            throw std::runtime_error("_let not followed by _in");

        return new LetExpr(name, rhs, lhs);
    } 
    else if(keyword == "true" || keyword == "false"){
        return new BoolExpr(keyword == "true" ? true : false);
    }
    else if(keyword == "if")
    {
        skip_whitespace(in);
        Expr* condition_arg = parse_expr(in);
        Expr* then_arg;
        Expr* else_arg;

        skip_whitespace(in);
        int c = in.peek();
        if(c == '_'){
            consume(in, c);
            std::string thenKeyword = parse_word(in);
            if(thenKeyword != "then")
                throw std::runtime_error("_if not followed by _then");
            then_arg = parse_expr(in);
        }
        else
            throw std::runtime_error("_if not followed by _then");
        
        skip_whitespace(in);
        c = in.peek();
        if(c == '_'){
            consume(in, c);
            std::string elseKeyword = parse_word(in);
            if(elseKeyword != "else")
                throw std::runtime_error("_then not followed by _else");
            else_arg = parse_expr(in);
        }
        else
            throw std::runtime_error("_then not followed by _else");

        return new IfExpr(condition_arg, then_arg, else_arg);
    }
    else if(keyword == "fun")
    {
        //paren expression, //expression
        skip_whitespace(in);

        int c = in.peek();
        if(c == '('){
            consume(in, '(');
            std::string formal_arg = parse_word(in);
            skip_whitespace(in);
            consume(in, ')');
            return new FunExpr(formal_arg, parse_expr(in));
        }
        else 
            throw std::runtime_error("_fun not followed by '('");
    }
    else
    {
        throw std::runtime_error("Invalid keyword: " + keyword);
    }
}

std::string parse_word(std::istream &in){
    std::string word = "";
    while(1){
        int c = in.peek();
        if(isalpha(c))
        {
            consume(in, c);
            word += char(c);
        }
        else 
        break;
    }
    return word;
}

/**
 * This is a helper function for testing
 */
Expr* parse_str(std::string str)
{
    std::stringstream st(str);
    return(parse_expr(st));
}

static void consume(std::istream &in, char expected)
{
    int c = in.get();
    if(c != expected)
    {
        throw std::runtime_error("consume mismatch. Expected: " + std::to_string(expected) + ", received: " + std::to_string(c));
    }
}

static void skip_whitespace(std::istream &in)
{
    while(1){
        if(in.peek() == ' ')
            in.get();
        else
            break;
    }
}

//TESTING for parse.cpp
//
TEST_CASE( "Parse Input") {
    SECTION("Number parsing"){
        CHECK("123" == parse_str("123")->to_string());
        CHECK("-321" == parse_str("-321")->to_string());
    }
    SECTION("Add parsing"){
        //Test group A with adds
        CHECK("(123+456)" == parse_str("123+456")->to_string());
        CHECK("(1+(2+(3+(4+5))))" == parse_str("1+2+3+4+5")->to_string()); //Should right-associate
        CHECK("1 + 2 + 3 + 4 + 5" == parse_str("1+2+3+4+5")->to_pretty_string());
    }
    SECTION("Mult parsing"){
        //Test group A with mults
        CHECK("(123*456)" == parse_str("123*456")->to_string());
        CHECK("(1*(2*(3*(4*5))))" == parse_str("1*2*3*4*5")->to_string()); //Should right-associate
        CHECK("1 * 2 * 3 * 4 * 5" == parse_str("1*2*3*4*5")->to_pretty_string());
    }
    SECTION("Mixed Add/Mult parsing"){
        //Test group A alternating adds/mults
        CHECK("(123+456)" == parse_str("123+456")->to_string());
        CHECK("(1+((2*3)+(4*5)))" == parse_str("1+2*3+4*5")->to_string()); //Should right-associate
        CHECK("1 * 2 + 3 * 4 + 5" == parse_str("1*2+3*4+5")->to_pretty_string());
    }
    SECTION("Paren parsing")
    {
        CHECK("123 * (4 + 5)" == parse_str("((123 * (4 + (5))))")->to_pretty_string());
        CHECK("(123 + 4) * 5" == parse_str("((123 + 4) * 5)))")->to_pretty_string());
        CHECK_THROWS_WITH(parse_str("((5 + 3)"), "missing close parenthesis");
        //TODO: Check missing open paren?
    }
    SECTION("Var parsing"){
        CHECK("3 + x" == parse_str("3 + x")->to_pretty_string());
        CHECK_FALSE("3 + y" == parse_str("3 + x")->to_pretty_string());
    }
    SECTION("Keyword parsing"){
        //Let
        CHECK("(_let x=5 _in (x+1))" == parse_str("_let x = 5   _in   x +  1")->to_string());
        CHECK_THROWS_WITH(parse_str("_conquer)"), "Invalid keyword: conquer");
    }
}

//Mixed Parse and Expr testing
TEST_CASE("Mixed Parse and Expression testing")
{
    SECTION("Functions"){

        CHECK(parse_str("_let y = _fun(x) x + 1 _in y(3))")->interp()->to_string() == "4");

        CHECK(parse_str("_let f = _fun (x) _fun (g) g(x + 1) _in _let g = _fun (y) y + 2 _in (f(5))(g)")->interp()->to_string() == "8");
        //Fibonacci
        Expr* fibonacci = parse_str("_let factrl = _fun (factrl) _fun (x) _if x == 1  _then 1 _else x * factrl(factrl)(x + -1) _in factrl(factrl)(10)");
        CHECK(fibonacci->interp()->to_string() == "3628800");
    }
}