/**
 * \file val.cpp
 * \brief contains implementations for Val "Value" class as well as Number,... subclasses
 */
#include "val.h"
#include "expr.h"
#include "catch.h"
#include <iostream>
 
NumVal::NumVal(int rep){
    this->rep = rep;
}

bool NumVal::equals(Val* e){
    NumVal *c = dynamic_cast<NumVal*>(e);
    if(c == nullptr)
        return false;
    return this->rep == c->rep;
}

Val* NumVal::add_to(Val* rhs){
    NumVal *c = dynamic_cast<NumVal*>(rhs);
    if(c == nullptr)
        throw std::runtime_error("Error: NumVal cannot add_to non-NumVals.");
    return new NumVal(this->rep + c->rep);
}

Val* NumVal::mult_with(Val* rhs){
    NumVal *c = dynamic_cast<NumVal*>(rhs);
    if(c == nullptr)
        throw std::runtime_error("Error: NumVal cannot mult_with non-NumVals.");
    return new NumVal(this->rep * c->rep);
}

Expr* NumVal::to_expr(){
    return new NumExpr(this->rep);
}

bool NumVal::is_true(){
    throw std::runtime_error("Error: NumVal cannot call is_true()");
}

std::string NumVal::to_string(){
    return std::to_string(this->rep);
}

Val* NumVal::call(Val* actual_arg){
    throw std::runtime_error("Error: NumVall calling 'call' invalid");
}

BoolVal::BoolVal(bool rep){
    this->rep = rep;
}

bool BoolVal::equals(Val* e){
    BoolVal *c = dynamic_cast<BoolVal*>(e);
    if(c == nullptr)
        return false;
    return this->rep == c->rep;
}

Val* BoolVal::add_to(Val* e){
    throw std::runtime_error("Error: BoolVal add_to invalid");
}

Val* BoolVal::mult_with(Val* e){
    throw std::runtime_error("Error: BoolVal mult_with invalid");
}

Expr* BoolVal::to_expr(){
    return new BoolExpr(this->rep);
}

std::string BoolVal::to_string(){
    return rep ? "true" : "false";
}

bool BoolVal::is_true(){
    return rep;
}

Val* BoolVal::call(Val* actual_arg){
    throw std::runtime_error("Error: BoolVal calling 'call' invalid");
}

FunVal::FunVal(std::string name, Expr* expression){
    this->name = name;
    this->expression = expression;
}

bool FunVal::equals(Val* e){
    FunVal *c = dynamic_cast<FunVal*>(e);
    if(c == nullptr)
        return false;
    return this->name == c->name && this->expression->equals(c->expression);
}

Val* FunVal::add_to(Val* rhs){
    throw std::runtime_error("Error: FunVal add_to invalid");
}

Val* FunVal::mult_with(Val* rhs){
    throw std::runtime_error("Error: FunVal mult_with invalid");
}

Expr* FunVal::to_expr(){
    return new FunExpr(name, expression);
}

std::string FunVal::to_string(){
    return to_expr()->to_string();
}

bool FunVal::is_true(){
    throw std::runtime_error("Error: FunVal cannot call is_true()");
}

Val* FunVal::call(Val *actual_arg){
    return expression->subst(name, actual_arg->to_expr())->interp();
}

TEST_CASE("NumVal"){
    SECTION("Equals"){
        CHECK((new NumVal(3))->equals(new NumVal(3)));
        CHECK_FALSE((new NumVal(-302))->equals(new NumVal(9999999)));
    }

    SECTION("Add_to"){
        CHECK(((new NumVal(3))->add_to(new NumVal(5)))->equals(new NumVal(8)));
    }

    SECTION("Mult_With")
    {
        CHECK(((new NumVal(3))->mult_with(new NumVal(5)))->equals(new NumVal(15)));
    }

    SECTION("to_expr")
    {
        CHECK((new NumVal(3))->to_expr()->equals(new NumExpr(3)));
    }

    SECTION("to_string")
    {
        CHECK((new NumVal(37))->to_string() == "37");
    }
}

TEST_CASE("BoolVal"){
    SECTION("Equals"){
        CHECK((new BoolVal(true))->equals(new BoolVal(true)));
        CHECK_FALSE((new BoolVal(true))->equals(new BoolVal(false)));
    }

    SECTION("Add_to"){
        CHECK_THROWS(((new BoolVal(true))->add_to(new NumVal(5)))->equals(new NumVal(8)));
    }

    SECTION("Mult_With")
    {
        CHECK_THROWS(((new BoolVal(3))->mult_with(new NumVal(5)))->equals(new NumVal(15)));
    }

    SECTION("to_expr")
    {
        CHECK((new BoolVal(true))->to_expr()->equals(new BoolExpr(true)));
    }

    SECTION("to_string")
    {
        CHECK((new BoolVal(true))->to_string() == "true");
    }
}

TEST_CASE("FunVal"){
    SECTION("Equals"){
        CHECK((new FunVal("x", new NumExpr(1)))->equals(new FunVal("x", new NumExpr(1))));
        CHECK_FALSE((new FunVal("x", new NumExpr(2)))->equals(new FunVal("x", new NumExpr(1))));
    }

    SECTION("Add_to"){
        CHECK_THROWS(((new FunVal("x", new NumExpr(1)))->add_to(new NumVal(5)))->equals(new NumVal(8)));
    }

    SECTION("Mult_With")
    {
        CHECK_THROWS(((new FunVal("x", new NumExpr(1)))->mult_with(new NumVal(5)))->equals(new NumVal(15)));
    }

    SECTION("to_expr")
    {
        CHECK((new FunVal("x", new NumExpr(1)))->to_expr()->equals(new FunExpr("x", new NumExpr(1))));
    }

    SECTION("to_string")
    {
       // CHECK((new FunVal(true))->to_string() == "true");
    }
}