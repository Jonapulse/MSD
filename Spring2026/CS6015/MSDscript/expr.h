/**
 * \file expression.h
 * \brief contains Expr "expression" class as well as Num, Var, Add, Mult, and Let subclasses
 */

#include <string>
#include <stdexcept>
#include <sstream>
#include "pointer.h"

//Pretty print utility enum for writing parentheses
//
typedef enum {
  prec_none,      // = 0
  prec_let,       // = 1
  prec_add,       // = 2
  prec_mult       // = 3
} precedence_t;

//Referencing Val without full #include
//
class Val;

/**
 * \brief Expression class, supporting interpret grammar
 * 〈expr〉 = 〈number〉
 * |(〈expr〉)
 * | 〈expr〉 + 〈expr〉
 * | 〈expr〉 * 〈expr〉
 * | 〈variable〉
 * | _let 〈variable〉 = 〈expr〉 _in 〈expr
 */
CLASS(Expr){
public:
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) interp() = 0;
    virtual PTR(Expr) subst(const std::string &name, PTR(Expr) substitution) = 0;
    virtual void printExpr(std::ostream& ot) = 0;
    virtual std::string to_string();
    virtual void pretty_print(std::ostream& ot);
    virtual void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
    virtual std::string to_pretty_string();
};

/**
 * \brief Num extends Expr, intended for integer values
 */
class NumExpr: public Expr{
public:
    PTR(Val) rep;

    NumExpr(int rep);
    NumExpr(PTR(Val) rep);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
};

/**
 * \brief Add represents two expressions being added
 */
class AddExpr: public Expr{
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};

/**
 * \brief Mult represents two expressions being multiplied
 */
class MultExpr: public Expr{
public: 
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    MultExpr(PTR(Expr) lhs, PTR(Expr) rhs);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};

class VarExpr: public Expr{
public:
    std::string name;

    VarExpr(const std::string &name);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
};

/**
 * \brief An expression defining a var and the value it refers to.
 * example: _let x = 5 in x + 1
 * \property name - 'x' from example. The variable name which, in use, will match with 'name' in Var expressions.
 * \property rhs - '5' from example. The 'value' expression. When substituting, x will be swapped with this expression.
 * \property lhs - 'x + 1' from example. The expression that rhs will be substituted into.
 */
class LetExpr: public Expr{
public:
    std::string name;
    PTR(Expr) rhs; 
    PTR(Expr) lhs;

    LetExpr(const std::string &name, PTR(Expr) rhs, PTR(Expr) lhs);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};

class BoolExpr: public Expr{
public:
    PTR(Val) rep;

    BoolExpr(bool value);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
};

class IfExpr: public Expr{
public:
    PTR(Expr) condition_arg;
    PTR(Expr) then_arg;
    PTR(Expr) else_arg;

    IfExpr(PTR(Expr) condition_arg, PTR(Expr) then_arg, PTR(Expr) else_arg);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};

class EqExpr: public Expr{
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    EqExpr(PTR(Expr) lhs, PTR(Expr) rhs);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};

class FunExpr: public Expr{
public:
    std::string formal_arg;
    PTR(Expr) body;

    FunExpr(std::string formal_arg, PTR(Expr) body);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};

class CallExpr: public Expr{
public:
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;

    CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);

    bool equals(PTR(Expr) e);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string &name, PTR(Expr) substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth);
};