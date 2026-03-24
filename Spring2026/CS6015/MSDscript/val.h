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
 *          |〈boolean〉 
 */
class Val
{
public:
    virtual bool equals(Val* e) = 0;
    virtual Val* add_to(Val* rhs) = 0;
    virtual Val* mult_with(Val* rhs) = 0;
    virtual Expr* to_expr() = 0;
    virtual std::string to_string() = 0;
    virtual bool is_true() = 0;
};

/**
 * \brief NumVal, representing integer values
 */
class NumVal: public Val{
public:
    int rep;

    NumVal(int rep);

    bool equals(Val* e);
    Val* add_to(Val* rhs);
    Val* mult_with(Val* rhs);
    Expr* to_expr();
    std::string to_string();
    bool is_true(); //Will error when called on NumVal

    int to_int();
};

/**
 * \brief NumVal, representing boolean values
 */
class BoolVal: public Val{
public:
    bool rep;

    BoolVal(bool rep);

    bool equals(Val* e);
    Val* add_to(Val* rhs); //Will error when called on BoolVal
    Val* mult_with(Val* rhs); //Will error when called on BoolVal
    Expr* to_expr();
    std::string to_string();
    bool is_true();
};