/**
 * \file val.h
 * \brief contains Val "value" class as well as Num... subclasses
 */

#include <string>
#include "pointer.h" 


//Referencing Expr/Env without full #include
//
class Expr;
class Env;

/**
 * \brief Value class, supporting interpreter grammar
 * 〈val〉 = 〈number〉
 *          |〈boolean〉 
 */
CLASS(Val)
{
public:
    virtual bool equals(PTR(Val) e) = 0;
    virtual PTR(Val) add_to(PTR(Val) rhs) = 0;
    virtual PTR(Val) mult_with(PTR(Val) rhs) = 0;
    virtual PTR(Expr) to_expr() = 0;
    virtual std::string to_string() = 0;
    virtual bool is_true() = 0;
    virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
};

/**
 * \brief NumVal, representing integer values
 */
class NumVal: public Val{
public:
    int rep;

    NumVal(int rep);

    bool equals(PTR(Val) e);
    PTR(Val) add_to(PTR(Val) rhs);
    PTR(Val) mult_with(PTR(Val) rhs);
    PTR(Expr) to_expr();
    std::string to_string();
    bool is_true(); //Will error when called on NumVal
    PTR(Val) call(PTR(Val) actual_arg); //Will error when called on NumVal

    int to_int();
};

/**
 * \brief NumVal, representing boolean values
 */
class BoolVal: public Val{
public:
    bool rep;

    BoolVal(bool rep);

    bool equals(PTR(Val) e);
    PTR(Val) add_to(PTR(Val) rhs); //Will error when called on BoolVal
    PTR(Val) mult_with(PTR(Val) rhs); //Will error when called on BoolVal
    PTR(Expr) to_expr();
    std::string to_string();
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg); //Will error when called on BoolVal
};

/**
 * \brief Fun, representing functions
 */
class FunVal: public Val{
public:
    std::string name;
    PTR(Expr) expression;
    PTR(Env) captured_env;

    FunVal(std::string name, PTR(Expr) expression, PTR(Env) captured_env);

    bool equals(PTR(Val) e);
    PTR(Val) add_to(PTR(Val) rhs); //Will error when called on FunVal
    PTR(Val) mult_with(PTR(Val) rhs); //Will error when called on FunVal
    PTR(Expr) to_expr();
    std::string to_string();
    bool is_true(); //Will error when called on FunVal
    PTR(Val) call(PTR(Val) actual_arg); 
};