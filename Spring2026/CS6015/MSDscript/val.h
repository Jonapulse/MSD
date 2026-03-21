/**
 * \file val.h
 * \brief contains Val "value" class as well as Num... subclasses
 */

#include <string>

//Referencing Expr without full #include
//
class Expr;

/**
 * \brief Value class, supporting interpreter grammar
 * 〈val〉 = 〈number〉
 *  | 〈boolean〉 
 */
class Val
{
public:
    virtual bool equals(Val* e) = 0;
    virtual Val* add_to(Val* rhs) = 0;
    virtual Val* mult_with(Val* rhs) = 0;
    virtual Expr* to_expr() = 0;
    virtual std::string to_string() = 0;
};

/**
 * \brief NumVal, representing integer values
 * 
 */
class NumVal: public Val{
public:
    int val;

    NumVal(int val);

    bool equals(Val* e);
    Val* add_to(Val* rhs);
    Val* mult_with(Val* rhs);
    Expr* to_expr();
    std::string to_string();

    int to_int();
};