#include "parse.hpp"

Expr *parse_expr(std::istream &in)
{
    Expr* e = parse_addend(in);

    skip_whitespace(in);

    int c = in.peek();
    if(c == '+'){
        consume(in, '+');
        Expr* rhs = parse_expr(in);
        return new Add(e, rhs);
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
        return new Mult(e, rhs);
    } else {
        return e;
    }
}

Expr *parse_multicand(std::istream &in)
{
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
	//Simple Pseudocode for what we'll do for var and keyword...
	else if (isalpha(c))
	{
		//parse_var(c); 
        assert(false); //TODO: implement this. 
	}
	else if (c == '_')
	{
		//parse_keyword(c); (also parse_let but that's probably part of parse_keyword)
        assert(false); //TODO: implement this
	} 
	//...and back to what we already had
	else { 
		consume(in, c);
		throw std::runtime_error("invalid input");
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
        
    return new Num(n);
}

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
        throw std::runtime_error("consume mismatch");
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