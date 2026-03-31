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
void Expr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth){
    return this->printExpr(ot);
}

std::string Expr::to_pretty_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}

NumExpr::NumExpr(int val){
    this->rep = new NumVal(val);
}

bool NumExpr::equals(Expr *e)
{
    //dynamic cast, check for null
    NumExpr *c = dynamic_cast<NumExpr*>(e);
    if(c == nullptr)
        return false;
    return this->rep->equals(c->rep);
}

Val* NumExpr::interp()
{
    return this->rep;
}

/**
 * \brief Returns itself, as number values do not change in substitution
 */
Expr* NumExpr::subst(const std::string &name, Expr* substitution){
    return this;
}

void NumExpr::printExpr(std::ostream& ot){
    ot << rep->to_string();
}

AddExpr::AddExpr(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(Expr *e)
{
    //dynamic cast, check for null
    AddExpr *c = dynamic_cast<AddExpr*>(e);
    if(c == nullptr)
        return false;
    return lhs->equals(c->lhs) && rhs->equals(c->rhs);
}

Val* AddExpr::interp(){
    return lhs->interp()->add_to(rhs->interp());
}

Expr* AddExpr::subst(const std::string &name, Expr* substitution){
    return new AddExpr(lhs->subst(name, substitution), rhs->subst(name, substitution));
}

void AddExpr::printExpr(std::ostream& ot){
    ot << "(" << lhs->to_string() << "+" << rhs->to_string() << ")";
}

/**
 * explain how this precedence works.
 */
void AddExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, 0);
}

/**
 * \brief Adds parentheses if prec is high enough, which for Add means it was called by an add or mult.
 */
void AddExpr::pretty_print_at(std::ostream &ot, precedence_t prec, int depth){
    bool doParen = prec >= prec_add;
    if(doParen)
        ot << "(";
    lhs->pretty_print_at(ot, prec_add, depth);
    ot << " + ";
    rhs->pretty_print_at(ot, prec_none, depth);
    if(doParen)
        ot << ")";
}

MultExpr::MultExpr(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(Expr *e)
{
    //dynamic cast, check for null
    MultExpr *c = dynamic_cast<MultExpr*>(e);
    if(c == nullptr)
        return false;
    return this->lhs->equals(c->lhs) && this->rhs->equals(c->rhs);
}

Val* MultExpr::interp()
{
    return lhs->interp()->mult_with(rhs->interp());
}

Expr* MultExpr::subst(const std::string &name, Expr* substitution){
    return new MultExpr(lhs->subst(name, substitution), rhs->subst(name, substitution));
}

void MultExpr::printExpr(std::ostream& ot){
    ot << "(" << lhs->to_string() << "*" << rhs->to_string() << ")";
}

/**
 * explain how this precedence works.
 */
void MultExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, 0);
}

/**
 * \brief Adds parentheses if precedence is high enough, which for mult means it was called by a mult.
 */
void MultExpr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth){
    bool doParen = prec >= prec_mult;
    if(doParen)
        ot << "(";
    lhs->pretty_print_at(ot, prec_mult, depth);
    ot << " * ";
    rhs->pretty_print_at(ot, prec_add, depth);
    if(doParen)
        ot << ")";
}

VarExpr::VarExpr(const std::string &name){
    this->name = name;
}

bool VarExpr::equals(Expr *e)
{
    //dynamic cast, check for null
    VarExpr *c = dynamic_cast<VarExpr*>(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name;
}

/**
 * \brief interp is not defined (at this developmen stage) for variables, so we return an error
 */
Val* VarExpr::interp()
{
    throw std::runtime_error("Error: VarExpr(\"" + name + "\") does not support interp (at this stage in development)");
}

Expr* VarExpr::subst(const std::string &name, Expr* substitution){
    if(this->name == name)
        return substitution;
    else
        return new VarExpr(this->name);
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
LetExpr::LetExpr(const std::string &name, Expr* rhs, Expr* lhs)
{
    this->name = name;
    this->rhs = rhs;
    this->lhs = lhs;
}

bool LetExpr::equals(Expr *e)
{
    //dynamic cast, check for null
    LetExpr *c = dynamic_cast<LetExpr*>(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name && this->lhs->equals(c->lhs) && this->rhs->equals(c->rhs);
}

Val* LetExpr::interp(){
    return lhs->subst(name, rhs->interp()->to_expr())->interp();
}

/**
 * \brief for Let we only substitue the 'lhs', the expression following '_in'
 * if substituting name that would overwrite rhs, we stop.
 * Nested Let expressions sharing variable names will substitue deeper nested names first.
 */
Expr* LetExpr::subst(const std::string &name, Expr* substitution){
    //End substitution if the substituting name matches Let's name
    if(this->name == name)
        return this;
    return new LetExpr(this->name, rhs, lhs->subst(name, substitution));
}

void LetExpr::printExpr(std::ostream& ot){
    ot << "(_let " << this->name << "=" << rhs->to_string() << " _in "<< lhs->to_string() << ")";
}

void LetExpr::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none, 0);
}

/**
 * \brief Adds parentheses if precedence is high enough, which for mult means it was called by a mult.
 * \param depth -> '_in' is preceded by an in-line, then depth * 6 spaces to align with its _let if nested.
 */
void LetExpr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth = 0){
    bool doParen = prec >= prec_let;
    
    std::string spacing = "";
    for(int i = 0; i < depth; i++)
        spacing += "      ";

    if(doParen)
        ot << "(";
    ot << "_let " << name << " = ";
    rhs->pretty_print_at(ot, prec_let, depth);
    ot << '\n' << spacing << "_in  ";
    lhs->pretty_print_at(ot, prec_let, depth + 1);
    if(doParen)
        ot << ")";
}

BoolExpr::BoolExpr(bool value){
    rep = new BoolVal(value);
}

bool BoolExpr::equals(Expr* e){
    //dynamic cast, check for null
    BoolExpr *c = dynamic_cast<BoolExpr*>(e);
    if(c == nullptr)
        return false;
    return rep->equals(c->rep);
}

Val* BoolExpr::interp(){
    return rep;
}

Expr* BoolExpr::subst(const std::string &name, Expr* substitution){
    return this;
}

void BoolExpr::printExpr(std::ostream& ot){
    ot << rep->to_string();
}

IfExpr::IfExpr(Expr* condition_arg, Expr* if_arg, Expr* else_arg){
    this->condition_arg = condition_arg;
    this->then_arg = if_arg;
    this->else_arg = else_arg;
}

bool IfExpr::equals(Expr* e){
    //dynamic cast, check for null
    IfExpr *c = dynamic_cast<IfExpr*>(e);
    if(c == nullptr)
        return false;
    return condition_arg->equals(c->condition_arg) && then_arg->equals(c->then_arg) && else_arg->equals(c->else_arg);
}

Val* IfExpr::interp(){
    if(condition_arg->interp()->is_true())
        return then_arg->interp();
    else
        return else_arg->interp();
}

Expr* IfExpr::subst(const std::string &name, Expr* substitution){
    return new IfExpr(condition_arg->subst(name, substitution),
        then_arg->subst(name, substitution),
        else_arg->subst(name, substitution));
}

void IfExpr::printExpr(std::ostream& ot){}

void IfExpr::pretty_print(std::ostream& ot){}

void IfExpr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth){}

EqExpr::EqExpr(Expr* lhs, Expr* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(Expr* e){
    //dynamic cast, check for null
    EqExpr *c = dynamic_cast<EqExpr*>(e);
    if(c == nullptr)
        return false;
    return lhs->equals(c->lhs) && rhs->equals(c->rhs);
}

Val* EqExpr::interp(){
    return new BoolVal(lhs->interp()->equals(rhs->interp()));
}

Expr* EqExpr::subst(const std::string &name, Expr* substitution){
    return new EqExpr(lhs->subst(name, substitution), rhs->subst(name, substitution));
}

void EqExpr::printExpr(std::ostream& ot){}

void EqExpr::pretty_print(std::ostream& ot){}

void EqExpr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth){}

FunExpr::FunExpr(std::string formal_arg, Expr* body){
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(Expr* e){
    //dynamic cast, check for null
    FunExpr *c = dynamic_cast<FunExpr*>(e);
    if(c == nullptr)
        return false;
    return formal_arg == c->formal_arg && body->equals(c->body);
}

Val* FunExpr::interp(){
    return new FunVal(formal_arg, body);
}

Expr* FunExpr::subst(const std::string &name, Expr* substitution){
    //End substitution if the substituting name matches Let's name
    if(this->formal_arg == name)
        return this;
    return new FunExpr(this->formal_arg, body->subst(name, substitution));
}

void FunExpr::printExpr(std::ostream& ot){}
void FunExpr::pretty_print(std::ostream& ot){}
void FunExpr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth){}

CallExpr::CallExpr(Expr* to_be_called, Expr* actual_arg){
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(Expr* e){
    //dynamic cast, check for null
    CallExpr *c = dynamic_cast<CallExpr*>(e);
    if(c == nullptr)
        return false;
    return to_be_called->equals(c->to_be_called) && actual_arg->equals(c->actual_arg);
}

Val* CallExpr::interp(){
    return to_be_called->interp()->call(actual_arg->interp());
}

Expr* CallExpr::subst(const std::string &name, Expr* substitution){
    return new CallExpr(to_be_called->subst(name, substitution), actual_arg->subst(name, substitution));
}

void CallExpr::printExpr(std::ostream& ot){}
void CallExpr::pretty_print(std::ostream& ot){}
void CallExpr::pretty_print_at(std::ostream& ot, precedence_t prec, int depth){}

////////////////////////////////////////
// TESTING for expr.cpp
////////////////////////////////////////
TEST_CASE( "Expression Equality") {
    SECTION("Num tests"){
        CHECK((new NumExpr(10))->equals(new NumExpr(10)));
        CHECK_FALSE((new NumExpr(10))->equals(new NumExpr(5)));
        CHECK_FALSE((new NumExpr(10))->equals(new VarExpr("a")));
    }
    
    SECTION("Add tests"){
        CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(2), new NumExpr(3))));
        CHECK_FALSE((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(3), new NumExpr(2))));
        CHECK_FALSE((new VarExpr("a"))->equals(new NumExpr(2)));
    }
    
    SECTION("Mult tests"){
        CHECK((new MultExpr(new NumExpr(2), new NumExpr(3)))->equals(new MultExpr(new NumExpr(2), new NumExpr(3))));
        CHECK_FALSE((new MultExpr(new NumExpr(2), new NumExpr(3)))->equals(new MultExpr(new NumExpr(3), new NumExpr(2))));
        CHECK_FALSE((new VarExpr("a"))->equals(new NumExpr(2)));
    }

    SECTION("VarExpr tests"){
        CHECK((new VarExpr("a"))->equals((new VarExpr("a"))));
        CHECK_FALSE((new VarExpr("a"))->equals((new VarExpr("b"))));
        CHECK_FALSE((new VarExpr("a"))->equals(new NumExpr(2)));
    }

    SECTION("Let tests"){
        CHECK((new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1)), new NumExpr(5)))->
        equals(new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1)), new NumExpr(5))));
        CHECK_FALSE((new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1)), new NumExpr(5)))->
        equals(new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1)), new NumExpr(6))));
        CHECK_FALSE((new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1)), new NumExpr(5)))->
        equals(new LetExpr("y", new AddExpr(new VarExpr("y"), new NumExpr(1)), new NumExpr(5))));
    }
}

TEST_CASE("Expression interp"){
    SECTION("Num tests"){
        CHECK((new NumExpr(10))->interp()->equals(new NumVal(10)));
    }

    SECTION("Add tests"){
        CHECK((new AddExpr(new NumExpr(3), new NumExpr(5)))->interp()->equals(new NumVal(8)));
        CHECK((new AddExpr(new AddExpr(new NumExpr(1),new NumExpr(2)), new NumExpr(3)))->interp()->equals(new NumVal(6)));
    }

    SECTION("Mult tests")
    {
        CHECK((new MultExpr(new NumExpr(3), new NumExpr(5)))->interp()->equals(new NumVal(15)));
        CHECK((new MultExpr(new MultExpr(new NumExpr(2),new NumExpr(3)), new NumExpr(3)))->interp()->equals(new NumVal(18)));
    }

    SECTION("Assignment tests"){
        CHECK( (new MultExpr(new NumExpr(3), new NumExpr(2)))->interp()->equals(new NumVal(6)));
        CHECK( (new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),new AddExpr(new NumExpr(20),new NumExpr(20))))->interp()->equals(new NumVal(65)));
    }

    SECTION("Let tests"){
        CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp()->equals(new NumVal(6)));

        //nested Let
        CHECK((new LetExpr("x", new NumExpr(10), new AddExpr(new VarExpr("x"), new LetExpr("x", new NumExpr(13), new AddExpr(new VarExpr("x"), new NumExpr(5))))))->interp()->equals(new NumVal(28)));
    }

    SECTION("Bool tests"){
        CHECK((new BoolExpr(true))->interp()->is_true());
        CHECK_FALSE((new BoolExpr(false))->interp()->is_true());
    }

    SECTION("If tests"){
        CHECK((new IfExpr(new BoolExpr(true), new NumExpr(3), new NumExpr(4)))->interp()->equals(new NumVal(3)));
        CHECK((new IfExpr(new BoolExpr(false), new NumExpr(3), new NumExpr(4)))->interp()->equals(new NumVal(4)));
    }

    SECTION("Equality tests"){
        CHECK((new EqExpr(new NumExpr(3), new NumExpr(3)))->interp()->equals(new BoolVal(true)));
        CHECK((new EqExpr(new NumExpr(3), new NumExpr(4)))->interp()->equals(new BoolVal(false)));
    }

    SECTION("Function tests"){
        CHECK((new FunExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp()->equals(new FunVal("x", new AddExpr(new VarExpr("x"), new NumExpr(1)))));
    
        //Factorial
        //          _let factrl = _fun (factrl)  
//                 _fun (x)  
//                   _if x == 1  
//                   _then 1  
//                   _else x * factrl(factrl)(x + -1)  
//         _in  factrl(factrl)(10)
        Expr* factorial = new LetExpr("factrl", new FunExpr("factrl", 
            new FunExpr("x", 
                new IfExpr(new EqExpr(new VarExpr("x"), new NumExpr(1)), 
                new NumExpr(1), 
                new MultExpr(new VarExpr("x"), new CallExpr(new CallExpr(new VarExpr("factrl"), new VarExpr("factrl")), new AddExpr(new VarExpr("x"), new NumExpr(-1))))))), 
            new CallExpr(new CallExpr(new VarExpr("factrl"), new VarExpr("factrl")), new NumExpr(10)));
        std::cout << "\nIt's:" + factorial->interp()->to_string() << "\n";
        CHECK(factorial->interp()->to_string() == "3628800");
    }

    SECTION("Call tests"){
        CHECK((new CallExpr((new FunExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1)))), new NumExpr(1)))->interp()->equals(new NumVal(2)));
    }
}

TEST_CASE("substitution")
{
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
       ->subst("x", new VarExpr("y"))
       ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );
    CHECK( (new VarExpr("x"))
       ->subst("x", new AddExpr(new VarExpr("y"),new NumExpr(7)))
       ->equals(new AddExpr(new VarExpr("y"),new NumExpr(7))) );
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(5)))
        ->subst("x", new NumExpr(3))
        ->interp()->equals(new NumVal(8)));
    CHECK( (new MultExpr(new VarExpr("x"), new VarExpr("y")))
        ->subst("x", new NumExpr(3))
        ->subst("y", new NumExpr(4))
        ->interp()->equals(new NumVal(12)));
}

TEST_CASE("to_string")
{
    CHECK((new NumExpr(3))->to_string() == "3");
    CHECK((new VarExpr("x"))->to_string() == "x");
    CHECK((new AddExpr(new NumExpr(3), new NumExpr(4)))->to_string() == "(3+4)");
    CHECK((new MultExpr(new NumExpr(3), new NumExpr(4)))->to_string() == "(3*4)");

    CHECK((new AddExpr(new NumExpr(3), new MultExpr(new VarExpr("x"), new NumExpr(4))))->to_string() == "(3+(x*4))");
    CHECK((new MultExpr(new NumExpr(3), new AddExpr(new VarExpr("x"), new NumExpr(4))))->to_string() == "(3*(x+4))");
    
    CHECK((new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(5)), new AddExpr(new VarExpr("x"), new NumExpr(1))))->to_string() == "(_let x=(x+5) _in (x+1))");
    CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->to_string() == "(_let x=5 _in (x+1))");
}

TEST_CASE("pretty_print")
{
    CHECK ( (new MultExpr(new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
    CHECK ( (new MultExpr(new MultExpr(new NumExpr(8), new NumExpr(1)), new VarExpr("y")))->to_pretty_string() ==  "(8 * 1) * y" );
    CHECK ( (new MultExpr(new AddExpr(new NumExpr(3), new NumExpr(5)), new MultExpr(new NumExpr(6), new NumExpr(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
    CHECK ( (new MultExpr(new MultExpr(new NumExpr(7), new NumExpr(7)), new AddExpr(new NumExpr(9), new NumExpr(2))))->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );

    CHECK ( (new MultExpr(new MultExpr(new NumExpr(5), new NumExpr(2)), new NumExpr(8)))->to_pretty_string() == "(5 * 2) * 8");

    CHECK ( (new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->to_pretty_string()
        == "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
}
