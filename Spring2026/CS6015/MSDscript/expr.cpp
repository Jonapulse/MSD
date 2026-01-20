#include "expr.h"
#include "catch.h"

Num::Num(int val){
    this->val = val;
}

bool Num::Equals(Expr *e)
{
    //dynamic cast, check for null
    Num *c = dynamic_cast<Num*>(e);
    if(c == nullptr)
        return false;
    return this->val == c->val;
}

Add::Add(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::Equals(Expr *e)
{
    //dynamic cast, check for null
    Add *c = dynamic_cast<Add*>(e);
    if(c == nullptr)
        return false;
    return this->lhs->Equals(c->lhs) && this->rhs->Equals(c->rhs);
}

Mult::Mult(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::Equals(Expr *e)
{
    //dynamic cast, check for null
    Mult *c = dynamic_cast<Mult*>(e);
    if(c == nullptr)
        return false;
    return this->lhs->Equals(c->lhs) && this->rhs->Equals(c->rhs);
}

VarExpr::VarExpr(const std::string &name){
    this->name = name;
}

bool VarExpr::Equals(Expr *e)
{
    //dynamic cast, check for null
    VarExpr *c = dynamic_cast<VarExpr*>(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name;
}

//TESTING
//
TEST_CASE( "Basic Expression Equality") {
    SECTION("Num tests"){
        CHECK((new Num(10))->Equals(new Num(10)));
        CHECK_FALSE((new Num(10))->Equals(new Num(5)));
        CHECK_FALSE((new Num(10))->Equals(new VarExpr("a")));
    }
    
    SECTION("Add tests"){
        CHECK((new Add(new Num(2), new Num(3)))->Equals(new Add(new Num(2), new Num(3))));
        CHECK_FALSE((new Add(new Num(2), new Num(3)))->Equals(new Add(new Num(3), new Num(2))));
        CHECK_FALSE((new VarExpr("a"))->Equals(new Num(2)));
    }
    
    SECTION("Mult tests"){
        CHECK((new Mult(new Num(2), new Num(3)))->Equals(new Mult(new Num(2), new Num(3))));
        CHECK_FALSE((new Mult(new Num(2), new Num(3)))->Equals(new Mult(new Num(3), new Num(2))));
        CHECK_FALSE((new VarExpr("a"))->Equals(new Num(2)));
    }

    SECTION("VarExpr tests"){
        CHECK((new VarExpr("a"))->Equals((new VarExpr("a"))));
        CHECK_FALSE((new VarExpr("a"))->Equals((new VarExpr("b"))));
        CHECK_FALSE((new VarExpr("a"))->Equals(new Num(2)));
    }
}