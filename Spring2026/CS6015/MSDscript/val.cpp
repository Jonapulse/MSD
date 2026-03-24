/**
 * \file val.cpp
 * \brief contains implementations for Val "Value" class as well as Number,... subclasses
 */
#include "val.h"
#include "expr.h"
#include "catch.h"
 
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
        CHECK(((new NumVal(3))->mult_with(new NumVal(5)))->equals(new NumVal(15)));
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