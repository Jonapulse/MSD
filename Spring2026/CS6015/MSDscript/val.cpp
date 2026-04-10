/**
 * \file val.cpp
 * \brief contains implementations for Val "Value" class as well as Number,... subclasses
 */
#include "val.h"
#include "env.h"
#include "expr.h"
#include "catch.h"
#include <iostream>
 
NumVal::NumVal(int rep){
    this->rep = rep;
}

bool NumVal::equals(PTR(Val) e){
    PTR(NumVal)c = CAST(NumVal)(e);
    if(c == nullptr)
        return false;
    return this->rep == c->rep;
}

PTR(Val) NumVal::add_to(PTR(Val) rhs){
    PTR(NumVal)c = CAST(NumVal)(rhs);
    if(c == nullptr)
        throw std::runtime_error("Error: NumVal cannot add_to non-NumVals.");
    return NEW(NumVal)(this->rep + c->rep);
}

PTR(Val) NumVal::mult_with(PTR(Val) rhs){
    PTR(NumVal)c = CAST(NumVal)(rhs);
    if(c == nullptr)
        throw std::runtime_error("Error: NumVal cannot mult_with non-NumVals.");
    return NEW(NumVal)(this->rep * c->rep);
}

PTR(Expr) NumVal::to_expr(){
    return NEW(NumExpr)(this->rep);
}

bool NumVal::is_true(){
    throw std::runtime_error("Error: NumVal cannot call is_true()");
}

std::string NumVal::to_string(){
    return std::to_string(this->rep);
}

PTR(Val) NumVal::call(PTR(Val) actual_arg){
    throw std::runtime_error("Error: NumVall calling 'call' invalid");
}

BoolVal::BoolVal(bool rep){
    this->rep = rep;
}

bool BoolVal::equals(PTR(Val) e){
    PTR(BoolVal)c = CAST(BoolVal)(e);
    if(c == nullptr)
        return false;
    return this->rep == c->rep;
}

PTR(Val) BoolVal::add_to(PTR(Val) e){
    throw std::runtime_error("Error: BoolVal add_to invalid");
}

PTR(Val) BoolVal::mult_with(PTR(Val) e){
    throw std::runtime_error("Error: BoolVal mult_with invalid");
}

PTR(Expr) BoolVal::to_expr(){
    return NEW(BoolExpr)(this->rep);
}

std::string BoolVal::to_string(){
    return rep ? "true" : "false";
}

bool BoolVal::is_true(){
    return rep;
}

PTR(Val) BoolVal::call(PTR(Val) actual_arg){
    throw std::runtime_error("Error: BoolVal calling 'call' invalid");
}

FunVal::FunVal(std::string name, PTR(Expr) expression, PTR(Env) captured_env){
    this->name = name;
    this->expression = expression;
    this->captured_env = captured_env;
}

bool FunVal::equals(PTR(Val) e){
    PTR(FunVal)c = CAST(FunVal)(e);
    if(c == nullptr)
        return false;
    return this->name == c->name && this->expression->equals(c->expression);
}

PTR(Val) FunVal::add_to(PTR(Val) rhs){
    throw std::runtime_error("Error: FunVal add_to invalid");
}

PTR(Val) FunVal::mult_with(PTR(Val) rhs){
    throw std::runtime_error("Error: FunVal mult_with invalid");
}

PTR(Expr) FunVal::to_expr(){
    return NEW(FunExpr)(name, expression);
}

std::string FunVal::to_string(){
    return to_expr()->to_string();
}

bool FunVal::is_true(){
    throw std::runtime_error("Error: FunVal cannot call is_true()");
}

PTR(Val) FunVal::call(PTR(Val)actual_arg){
    PTR(Env) new_env = NEW(ExtendedEnv)(name, actual_arg, captured_env);
    return expression->interp(new_env);
}

TEST_CASE("NumVal"){
    SECTION("Equals"){
        CHECK((NEW(NumVal)(3))->equals(NEW(NumVal)(3)));
        CHECK_FALSE((NEW(NumVal)(-302))->equals(NEW(NumVal)(9999999)));
    }

    SECTION("Add_to"){
        CHECK(((NEW(NumVal)(3))->add_to(NEW(NumVal)(5)))->equals(NEW(NumVal)(8)));
    }

    SECTION("Mult_With")
    {
        CHECK(((NEW(NumVal)(3))->mult_with(NEW(NumVal)(5)))->equals(NEW(NumVal)(15)));
    }

    SECTION("to_expr")
    {
        CHECK((NEW(NumVal)(3))->to_expr()->equals(NEW(NumExpr)(3)));
    }

    SECTION("to_string")
    {
        CHECK((NEW(NumVal)(37))->to_string() == "37");
    }
}

TEST_CASE("BoolVal"){
    SECTION("Equals"){
        CHECK((NEW(BoolVal)(true))->equals(NEW(BoolVal)(true)));
        CHECK_FALSE((NEW(BoolVal)(true))->equals(NEW(BoolVal)(false)));
    }

    SECTION("Add_to"){
        CHECK_THROWS(((NEW(BoolVal)(true))->add_to(NEW(NumVal)(5)))->equals(NEW(NumVal)(8)));
    }

    SECTION("Mult_With")
    {
        CHECK_THROWS(((NEW(BoolVal)(3))->mult_with(NEW(NumVal)(5)))->equals(NEW(NumVal)(15)));
    }

    SECTION("to_expr")
    {
        CHECK((NEW(BoolVal)(true))->to_expr()->equals(NEW(BoolExpr)(true)));
    }

    SECTION("to_string")
    {
        CHECK((NEW(BoolVal)(true))->to_string() == "true");
    }
}

TEST_CASE("FunVal"){
    SECTION("Equals"){
        CHECK((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->equals(NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty)));
        CHECK_FALSE((NEW(FunVal)("x", NEW(NumExpr)(2), Env::empty))->equals(NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty)));
    }

    SECTION("Add_to"){
        CHECK_THROWS(((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->add_to(NEW(NumVal)(5)))->equals(NEW(NumVal)(8)));
    }

    SECTION("Mult_With")
    {
        CHECK_THROWS(((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->mult_with(NEW(NumVal)(5)))->equals(NEW(NumVal)(15)));
    }

    SECTION("to_expr")
    {
        CHECK((NEW(FunVal)("x", NEW(NumExpr)(1), Env::empty))->to_expr()->equals(NEW(FunExpr)("x", NEW(NumExpr)(1))));
    }

    SECTION("to_string")
    {
       // CHECK((NEW(FunVal)(true))->to_string() == "true");
    }
}