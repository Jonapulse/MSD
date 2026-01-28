#include <string>

class Expr{
public:
    virtual bool Equals(Expr* e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(const std::string &name, Expr* substitution) = 0;
    virtual void printExpr(std::ostream& ot) = 0;
    virtual std::string to_string();
};

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
};

class VarExpr: public Expr{
public:
    std::string name;

    VarExpr(const std::string &name);

    bool Equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string &name, Expr* substitution);
    void printExpr(std::ostream& ot);
};