/**
 * \file expression.h
 * \brief contains Expr "expression" class as well as Num, Var, Add, Mult, and Let subclasses
 */

#include <string>
#include <stdexcept>
#include <sstream>

//Pretty print utility enum for writing parentheses
//
typedef enum {
  prec_none,      // = 0
  prec_let,       // = 1
  prec_add,       // = 2
  prec_mult       // = 3
} precedence_t;

//To reference Val without full #include
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
class Expr{
public:
    virtual bool equals(Expr* e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(const std::string &name, Expr* substitution) = 0;
    virtual void printExpr(std::ostream& ot) = 0;
    virtual std::string to_string();
    virtual void pretty_print(std::ostream& ot);
    virtual void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
    virtual std::string to_pretty_string();
};

/**
 * \brief Num extends Expr, intended for integer values
 */
class NumExpr: public Expr{
public:
    int val;

    NumExpr(int val);

    bool equals(Expr* e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
};

class AddExpr: public Expr{
public:
    Expr *lhs;
    Expr *rhs;

    AddExpr(Expr *lhs, Expr *rhs);

    bool equals(Expr* e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
};

class MultExpr: public Expr{
public: 
    Expr *lhs;
    Expr *rhs;

    MultExpr(Expr *lhs, Expr *rhs);

    bool equals(Expr* e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
};

class VarExpr: public Expr{
public:
    std::string name;

    VarExpr(const std::string &name);

    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
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
    Expr *lhs;
    Expr *rhs; 

    LetExpr(const std::string &name, Expr* rhs, Expr* lhs);

    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
};
