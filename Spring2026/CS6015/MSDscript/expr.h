/**
 * \file expression.h
 * \brief contains Expr "expression" class as well as Num, Var, Add, Mult, and Let subclasses
 */

#include <string>

//Pretty print utility enum for writing parentheses
//
typedef enum {
  prec_none,      // = 0
  prec_add,       // = 1
  prec_mult       // = 2
} precedence_t;

/**
 * \brief Expression class, supporting interpret grammar
 * 〈expr〉 = 〈number〉
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
    virtual precedence_t pretty_print_at();
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
    precedence_t pretty_print_at();
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
    precedence_t pretty_print_at();
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