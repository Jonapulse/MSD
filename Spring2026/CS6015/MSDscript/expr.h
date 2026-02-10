/**
 * \file expression.h
 * \brief contains Expr "expression" class as well as Num, Var, Add, Mult, and Let subclasses
 */

#include <string>

//Pretty print utility enum for writing parentheses
//
typedef enum {
  prec_none,      // = 0
  prec_let,       // = 1
  prec_add,       // = 2
  prec_mult       // = 3
} precedence_t;

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
    virtual bool Equals(Expr* e) = 0;
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
class Num: public Expr{
public:
    int val;

    Num(int val);

    bool Equals(Expr* e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
};

class Add: public Expr{
public:
    Expr *lhs;
    Expr *rhs;

    Add(Expr *lhs, Expr *rhs);

    bool Equals(Expr* e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
};

class Mult: public Expr{
public: 
    Expr *lhs;
    Expr *rhs;

    Mult(Expr *lhs, Expr *rhs);

    bool Equals(Expr* e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
};

class Var: public Expr{
public:
    std::string name;

    Var(const std::string &name);

    bool Equals(Expr *e);
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
class Let: public Expr{
public:
    std::string name;
    Expr *lhs;
    Expr *rhs; 

    Let(const std::string &name, Expr* lhs, Expr* rhs);

    bool Equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
    void pretty_print(std::ostream& ot);
    void pretty_print_at(std::ostream& ot, precedence_t prec, int depth);
};
