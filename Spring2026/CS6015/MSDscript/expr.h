#include <string>

class Expr{
public:
    virtual bool Equals(Expr* e) = 0;
    virtual int interp() = 0;
};

class Num: public Expr{
public:
    int val;

    Num(int val);

    bool Equals(Expr* e);
    int interp();
};

class Add: public Expr{
public:
    Expr *lhs;
    Expr *rhs;

    Add(Expr *lhs, Expr *rhs);

    bool Equals(Expr* e);
    int interp();
};

class Mult: public Expr{
public: 
    Expr *lhs;
    Expr *rhs;

    Mult(Expr *lhs, Expr *rhs);

    bool Equals(Expr* e);
    int interp();
};

class VarExpr: public Expr{
public:
    std::string name;

    VarExpr(const std::string &name);

    bool Equals(Expr *e);
    int interp();
};