#include "expr.h"
#include "catch.h"
#include <stdexcept>

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

int Num::interp()
{
    return this->val;
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

int Add::interp(){
    return this->lhs->interp() + this->rhs->interp();
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

int Mult::interp()
{
    return this->lhs->interp() * this->rhs->interp();
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

/**
 * interp is not defined (at this developmen stage) for variables,
 * so we return an error
 */
int VarExpr::interp()
{
    throw std::runtime_error("VarExpr does not support interp (at this stage in development)");
    return -1;
}

//TESTING
//
TEST_CASE( "Expression Equality") {
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

TEST_CASE("Expression interp"){
    SECTION("Num tests"){
        CHECK((new Num(10))->interp() == 10);
    }

    SECTION("Add tests"){
        CHECK((new Add(new Num(3), new Num(5)))->interp() == 8);
        CHECK((new Add(new Add(new Num(1),new Num(2)), new Num(3)))->interp() == 6);
    }

    SECTION("Mult tests")
    {
        CHECK((new Mult(new Num(3), new Num(5)))->interp() == 15);
        CHECK((new Mult(new Mult(new Num(2),new Num(3)), new Num(3)))->interp() == 18);
    }

    SECTION("VarExpr tests"){
        CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "VarExpr does not support interp (at this stage in development)" );
    }

    SECTION("Assignment tests"){
        CHECK( (new Mult(new Num(3), new Num(2)))->interp()==6 );
        CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp()==65);
    }
}