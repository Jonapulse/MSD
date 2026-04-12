/**
 * \file expression.cpp
 * \brief contains Expr "expression" implementation as well as Num, Var, Add, Mult, and Let subclass implementations.
 */

#include "expr.h"
#include "val.h"
#include "catch.h"
#include <iostream>

std::string Expr::to_string() {
    std::stringstream st("");
    this->printExpr(st);
    return st.str();
}

/**
 * \brief For Num and Add (default), printExpr prints them without considering parentheses or precence
 */
void Expr::pretty_print(std::ostream& ot){
    this->printExpr(ot);
}

/**
 * \brief For num and Add (default), printExpr prints them without considering parentheses or precence
 */
void Expr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth){
    return this->printExpr(ot);
}

std::string Expr::to_pretty_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}

NumExpr::NumExpr(int val){
    rep = NEW(NumVal)(val);
}

NumExpr::NumExpr(PTR(Val) rep){
    this->rep = rep;
}

bool NumExpr::equals(PTR(Expr) e)
{
    //dynamic cast, check for null
    PTR(NumExpr) c = CAST(NumExpr)(e);
    if(c == nullptr)
        return false;
    return rep->equals(c->rep);
}

PTR(Val) NumExpr::interp(PTR(Env) env)
{
    return rep;
}

void NumExpr::printExpr(std::ostream& ot){
    ot << rep->to_string();
}

AddExpr::AddExpr(PTR(Expr) _lhs, PTR(Expr) _rhs){
    lhs = _lhs;
    rhs = _rhs;
}

bool AddExpr::equals(PTR(Expr) e)
{
    //dynamic cast, check for null
    PTR(AddExpr) c = CAST(AddExpr)(e);
    if(c == nullptr)
        return false;
    return lhs->equals(c->lhs) && rhs->equals(c->rhs);
}

PTR(Val)  AddExpr::interp(PTR(Env) env){
    return lhs->interp(env)->add_to(rhs->interp(env));
}

void AddExpr::printExpr(std::ostream& ot){
    ot << "(" << lhs->to_string() << "+" << rhs->to_string() << ")";
}

/**
 * explain how this precedence works.
 */
void AddExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, false, 0);
}

/**
 * \brief Adds parentheses if prec is high enough, which for Add means it was called by an add or mult.
 */
void AddExpr::pretty_print_at(std::ostream &ot, precedence_t prec, bool keywordFormsNeedParen, int depth){
    bool doParen = prec >= prec_add;
    if(doParen)
        ot << "(";
    lhs->pretty_print_at(ot, prec_add, false, depth);
    ot << " + ";
    rhs->pretty_print_at(ot, prec_none, false, depth);
    if(doParen)
        ot << ")";
}

MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(PTR(Expr) e)
{
    //dynamic cast, check for null
    PTR(MultExpr) c = CAST(MultExpr)(e);
    if(c == nullptr)
        return false;
    return this->lhs->equals(c->lhs) && this->rhs->equals(c->rhs);
}

PTR(Val)  MultExpr::interp(PTR(Env) env)
{
    return lhs->interp(env)->mult_with(rhs->interp(env));
}

void MultExpr::printExpr(std::ostream& ot){
    ot << "(" << lhs->to_string() << "*" << rhs->to_string() << ")";
}

/**
 * explain how this precedence works.
 */
void MultExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, false, 0);
}

/**
 * \brief Adds parentheses if precedence is high enough, which for mult means it was called by a mult.
 */
void MultExpr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth){
    bool doParen = prec >= prec_mult;
    if(doParen)
        ot << "(";
    lhs->pretty_print_at(ot, prec_mult, false, depth);
    ot << " * ";
    rhs->pretty_print_at(ot, prec_add, false, depth);
    if(doParen)
        ot << ")";
}

VarExpr::VarExpr(const std::string &name){
    this->name = name;
}

bool VarExpr::equals(PTR(Expr) e)
{
    //dynamic cast, check for null
    PTR(VarExpr) c = CAST(VarExpr)(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name;
}

/**
 * \brief interp is not defined (at this developmen stage) for variables, so we return an error
 */
PTR(Val) VarExpr::interp(PTR(Env) env)
{
    return env->lookup(this->name);
}

void VarExpr::printExpr(std::ostream& ot){
    ot << name;
}

/**
 * \brief Let allows users to set values for variable names
 * \param name - variable name
 * \param rhs - the expression var 'name' will be replaced with
 * \param lhs - the expression, which should contain var 'name', into which rhs will be inserted
 */
LetExpr::LetExpr(const std::string &name, PTR(Expr)  rhs, PTR(Expr)  lhs)
{
    this->name = name;
    this->rhs = rhs;
    this->lhs = lhs;
}

bool LetExpr::equals(PTR(Expr) e)
{
    //dynamic cast, check for null
    PTR(LetExpr) c = CAST(LetExpr)(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name && this->lhs->equals(c->lhs) && this->rhs->equals(c->rhs);
}

PTR(Val)  LetExpr::interp(PTR(Env) env){
    PTR(Val) rhs_val = rhs->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv)(name, rhs_val, env);
    return lhs->interp(new_env);
}

void LetExpr::printExpr(std::ostream& ot){
    ot << "(_let " << this->name << "=" << rhs->to_string() << " _in "<< lhs->to_string() << ")";
}

void LetExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, false, 0);
}

/**
 * \brief Adds parentheses if precedence is high enough, which for mult means it was called by a mult.
 * \param depth -> '_in' is preceded by an in-line, then depth * 6 spaces to align with its _let if nested.
 */
void LetExpr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth = 0){
    bool doParen = prec >= prec_let || keywordFormsNeedParen;
    
    std::string spacing = "";
    for(int i = 0; i < depth; i++)
        spacing += "      ";

    if(doParen)
        ot << "(";
    ot << "_let " << name << " = ";
    rhs->pretty_print_at(ot, prec_let, true, depth);
    ot << '\n' << spacing << "_in  ";
    lhs->pretty_print_at(ot, prec_let, doParen ? keywordFormsNeedParen : false, depth + 1);
    if(doParen)
        ot << ")";
}

BoolExpr::BoolExpr(bool value){
    rep = NEW(BoolVal)(value);
}

bool BoolExpr::equals(PTR(Expr)  e){
    //dynamic cast, check for null
    PTR(BoolExpr) c = CAST(BoolExpr)(e);
    if(c == nullptr)
        return false;
    return rep->equals(c->rep);
}

PTR(Val)  BoolExpr::interp(PTR(Env) env){
    return rep;
}

void BoolExpr::printExpr(std::ostream& ot){
    ot << rep->to_string();
}

IfExpr::IfExpr(PTR(Expr) condition_arg, PTR(Expr) if_arg, PTR(Expr) else_arg){
    this->condition_arg = condition_arg;
    this->then_arg = if_arg;
    this->else_arg = else_arg;
}

bool IfExpr::equals(PTR(Expr) e){
    //dynamic cast, check for null
    PTR(IfExpr) c = CAST(IfExpr)(e);
    if(c == nullptr)
        return false;
    return condition_arg->equals(c->condition_arg) && then_arg->equals(c->then_arg) && else_arg->equals(c->else_arg);
}

PTR(Val)  IfExpr::interp(PTR(Env) env){
    if(condition_arg->interp(env)->is_true())
        return then_arg->interp(env);
    else
        return else_arg->interp(env);
}

void IfExpr::printExpr(std::ostream& ot){
    ot << "(_if " << this->condition_arg << " == " << then_arg->to_string() << " _in "<< else_arg->to_string() << ")";
}

void IfExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, false, 0);
}

void IfExpr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth){
    // bool doParen = prec >= prec_let || keywordFormsNeedParen;
    
    // std::string spacing = "";
    // for(int i = 0; i < depth; i++)
    //     spacing += "      ";

    // if(doParen)
    //     ot << "(";
    // ot << spacing << "_if ";
    // condition_arg->pretty_print_at(ot, prec_let, keywordFormsNeedParen, depth);
    // ot << "\n" << spacing << "_then ";
    // then_arg->pretty_print_at(ot, prec_let, keywordFormsNeedParen, depth);
    // ot << "\n" << spacing << "_else ";
    // else_arg->pretty_print_at(ot, prec_let, keywordFormsNeedParen, depth);
    // if(doParen)
    //     ot << ")";
}

EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(PTR(Expr) e){
    //dynamic cast, check for null
    PTR(EqExpr) c = CAST(EqExpr)(e);
    if(c == nullptr)
        return false;
    return lhs->equals(c->lhs) && rhs->equals(c->rhs);
}

PTR(Val)  EqExpr::interp(PTR(Env) env){
    return NEW(BoolVal)(lhs->interp(env)->equals(rhs->interp(env)));
}

void EqExpr::printExpr(std::ostream& ot){
    
}

void EqExpr::pretty_print(std::ostream& ot){

}

void EqExpr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth){

}

FunExpr::FunExpr(std::string formal_arg, PTR(Expr) body){
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(PTR(Expr) e){
    //dynamic cast, check for null
    PTR(FunExpr) c = CAST(FunExpr)(e);
    if(c == nullptr)
        return false;
    return formal_arg == c->formal_arg && body->equals(c->body);
}

PTR(Val) FunExpr::interp(PTR(Env) env){
    return NEW(FunVal)(formal_arg, body, env);
}

void FunExpr::printExpr(std::ostream& ot){}
void FunExpr::pretty_print(std::ostream& ot){}
void FunExpr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth){}

CallExpr::CallExpr(PTR(Expr)  to_be_called, PTR(Expr)  actual_arg){
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(PTR(Expr)  e){
    //dynamic cast, check for null
    PTR(CallExpr) c = CAST(CallExpr)(e);
    if(c == nullptr)
        return false;
    return to_be_called->equals(c->to_be_called) && actual_arg->equals(c->actual_arg);
}

PTR(Val)  CallExpr::interp(PTR(Env) env){
    return to_be_called->interp(env)->call(actual_arg->interp(env));
}

void CallExpr::printExpr(std::ostream& ot){}
void CallExpr::pretty_print(std::ostream& ot){}
void CallExpr::pretty_print_at(std::ostream& ot, precedence_t prec, bool keywordFormsNeedParen, int depth){}

////////////////////////////////////////
// TESTING for expr.cpp
////////////////////////////////////////
#ifndef NTEST
TEST_CASE( "Expression Equality") {
    SECTION("Num tests"){
        CHECK((NEW(NumExpr)(10))->equals(NEW(NumExpr)(10)));
        CHECK_FALSE((NEW(NumExpr)(10))->equals(NEW(NumExpr)(5)));
        CHECK_FALSE((NEW(NumExpr)(10))->equals(NEW(VarExpr)("a")));
    }
    
    SECTION("Add tests"){
        CHECK((NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))->equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))));
        CHECK_FALSE((NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))->equals(NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2))));
        CHECK_FALSE((NEW(VarExpr)("a"))->equals(NEW(NumExpr)(2)));
    }
    
    SECTION("Mult tests"){
        CHECK((NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))->equals(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))));
        CHECK_FALSE((NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))->equals(NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2))));
        CHECK_FALSE((NEW(VarExpr)("a"))->equals(NEW(NumExpr)(2)));
    }

    SECTION("VarExpr tests"){
        CHECK((NEW(VarExpr)("a"))->equals((NEW(VarExpr)("a"))));
        CHECK_FALSE((NEW(VarExpr)("a"))->equals((NEW(VarExpr)("b"))));
        CHECK_FALSE((NEW(VarExpr)("a"))->equals(NEW(NumExpr)(2)));
    }

    SECTION("Let tests"){
        CHECK((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), NEW(NumExpr)(5)))->
        equals(NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), NEW(NumExpr)(5))));
        CHECK_FALSE((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), NEW(NumExpr)(5)))->
        equals(NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), NEW(NumExpr)(6))));
        CHECK_FALSE((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), NEW(NumExpr)(5)))->
        equals(NEW(LetExpr)("y", NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(1)), NEW(NumExpr)(5))));
    }
}

TEST_CASE("Expression interp"){
    SECTION("Num tests"){
        CHECK((NEW(NumExpr)(10))->interp(Env::empty)->equals(NEW(NumVal)(10)));
    }

    SECTION("Add tests"){
        CHECK((NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(5)))->interp(Env::empty)->equals(NEW(NumVal)(8)));
        CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(1),NEW(NumExpr)(2)), NEW(NumExpr)(3)))->interp(Env::empty)->equals(NEW(NumVal)(6)));
    }

    SECTION("Mult tests")
    {
        CHECK((NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(5)))->interp(Env::empty)->equals(NEW(NumVal)(15)));
        CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(2),NEW(NumExpr)(3)), NEW(NumExpr)(3)))->interp(Env::empty)->equals(NEW(NumVal)(18)));
    }

    SECTION("Assignment tests"){
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2)))->interp(Env::empty)->equals(NEW(NumVal)(6)));
        CHECK( (NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(15)),NEW(AddExpr)(NEW(NumExpr)(20),NEW(NumExpr)(20))))->interp(Env::empty)->equals(NEW(NumVal)(65)));
    }

    SECTION("Let tests"){
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->interp(Env::empty)->equals(NEW(NumVal)(6)));

        //nested Let
        CHECK((NEW(LetExpr)("x", NEW(NumExpr)(10), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(LetExpr)("x", NEW(NumExpr)(13), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(5))))))->interp(Env::empty)->equals(NEW(NumVal)(28)));
    }

    SECTION("Bool tests"){
        CHECK((NEW(BoolExpr)(true))->interp(Env::empty)->is_true());
        CHECK_FALSE((NEW(BoolExpr)(false))->interp(Env::empty)->is_true());
    }

    SECTION("If tests"){
        CHECK((NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(3), NEW(NumExpr)(4)))->interp(Env::empty)->equals(NEW(NumVal)(3)));
        CHECK((NEW(IfExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(3), NEW(NumExpr)(4)))->interp(Env::empty)->equals(NEW(NumVal)(4)));
    }

    SECTION("Equality tests"){
        CHECK((NEW(EqExpr)(NEW(NumExpr)(3), NEW(NumExpr)(3)))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
        CHECK((NEW(EqExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4)))->interp(Env::empty)->equals(NEW(BoolVal)(false)));
    }

    SECTION("Function tests"){
        CHECK((NEW(FunExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->interp(Env::empty)->equals(NEW(FunVal)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), Env::empty)));
    
        //Factorial
        //          _let factrl = _fun (factrl)  
//                 _fun (x)  
//                   _if x == 1  
//                   _then 1  
//                   _else x * factrl(factrl)(x + -1)  
//         _in  factrl(factrl)(10)
        PTR(Expr) factorial = NEW(LetExpr)("factrl", NEW(FunExpr)("factrl", 
            NEW(FunExpr)("x", 
                NEW(IfExpr)(NEW(EqExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), 
                NEW(NumExpr)(1), 
                NEW(MultExpr)(NEW(VarExpr)("x"), NEW(CallExpr)(NEW(CallExpr)(NEW(VarExpr)("factrl"), NEW(VarExpr)("factrl")), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(-1))))))), 
            NEW(CallExpr)(NEW(CallExpr)(NEW(VarExpr)("factrl"), NEW(VarExpr)("factrl")), NEW(NumExpr)(10)));
        CHECK(factorial->interp(Env::empty)->to_string() == "3628800");
    }

    SECTION("Call tests"){
        CHECK((NEW(CallExpr)((NEW(FunExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))), NEW(NumExpr)(1)))->interp(Env::empty)->equals(NEW(NumVal)(2)));
    }
}

TEST_CASE("to_string")
{
    CHECK((NEW(NumExpr)(3))->to_string() == "3");
    CHECK((NEW(VarExpr)("x"))->to_string() == "x");
    CHECK((NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4)))->to_string() == "(3+4)");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4)))->to_string() == "(3*4)");

    CHECK((NEW(AddExpr)(NEW(NumExpr)(3), NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(4))))->to_string() == "(3+(x*4))");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(4))))->to_string() == "(3*(x+4))");
    
    CHECK((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(5)), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->to_string() == "(_let x=(x+5) _in (x+1))");
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->to_string() == "(_let x=5 _in (x+1))");
}

TEST_CASE("pretty_print")
{
    CHECK ( (NEW(MultExpr)(NEW(NumExpr)(1), NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
    CHECK ( (NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(8), NEW(NumExpr)(1)), NEW(VarExpr)("y")))->to_pretty_string() ==  "(8 * 1) * y" );
    CHECK ( (NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(5)), NEW(MultExpr)(NEW(NumExpr)(6), NEW(NumExpr)(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
    CHECK ( (NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(7), NEW(NumExpr)(7)), NEW(AddExpr)(NEW(NumExpr)(9), NEW(NumExpr)(2))))->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );

    CHECK ( (NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(2)), NEW(NumExpr)(8)))->to_pretty_string() == "(5 * 2) * 8");

    CHECK ( (NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))), NEW(VarExpr)("x"))))->to_pretty_string()
        == "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");


    // PTR(Expr) factorial = NEW(LetExpr)("factrl", NEW(FunExpr)("factrl", 
    //         NEW(FunExpr)("x", 
    //             NEW(IfExpr)(NEW(EqExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)), 
    //             NEW(NumExpr)(1), 
    //             NEW(MultExpr)(NEW(VarExpr)("x"), NEW(CallExpr)(NEW(CallExpr)(NEW(VarExpr)("factrl"), NEW(VarExpr)("factrl")), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(-1))))))), 
    //         NEW(CallExpr)(NEW(CallExpr)(NEW(VarExpr)("factrl"), NEW(VarExpr)("factrl")), NEW(NumExpr)(10)));
    // CHECK(factorial->to_pretty_string() == "_let factrl = _fun (factrl)\n      _fun (x)\n            _if x == 1\n            _then 1\n            _else x * factrl(factrl)(x + -1)\n_in  factrl(factrl)(10)");
}
#endif