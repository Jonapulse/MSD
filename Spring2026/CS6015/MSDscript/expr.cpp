/**
 * \file expression.h
 * \brief contains Expr "expression" implementation as well as Num, Var, Add, Mult, and Let subclass implementations.
 */

#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <sstream>

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
void Expr::pretty_print_at(std::ostream& ot, precedence_t prec){
    return this->printExpr(ot);
}

std::string Expr::to_pretty_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}

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

bool Num::has_variable()
{
    return false;
}

/**
 * \brief Returns itself, as number values do not change in substitution
 */
Expr* Num::subst(const std::string &name, Expr* substitution){
    return this;
}

void Num::printExpr(std::ostream& ot){
    ot << std::to_string(val);
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
    return lhs->Equals(c->lhs) && rhs->Equals(c->rhs);
}

int Add::interp(){
    return lhs->interp() + rhs->interp();
}

bool Add::has_variable()
{
    return lhs->has_variable() || rhs->has_variable();
}

Expr* Add::subst(const std::string &name, Expr* substitution){
    return new Add(lhs->subst(name, substitution), rhs->subst(name, substitution));
}

void Add::printExpr(std::ostream& ot){
    ot << "(" << lhs->to_string() << "+" << rhs->to_string() << ")";
}

/**
 * explain how this precedence works.
 */
void Add::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none);
}

/**
 * \brief Adds parentheses if prec is high enough, which for Add means it was called by an add or mult.
 */
void Add::pretty_print_at(std::ostream &ot, precedence_t prec){
    bool doParen = prec >= prec_add;
    if(doParen)
        ot << "(";
    lhs->pretty_print_at(ot, prec_add);
    ot << " + ";
    rhs->pretty_print_at(ot, prec_none);
    if(doParen)
        ot << ")";
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
    return lhs->interp() * rhs->interp();
}

bool Mult::has_variable()
{
    return lhs->has_variable() || rhs->has_variable();
}

Expr* Mult::subst(const std::string &name, Expr* substitution){
    return new Mult(lhs->subst(name, substitution), rhs->subst(name, substitution));
}

void Mult::printExpr(std::ostream& ot){
    ot << "(" << lhs->to_string() << "*" << rhs->to_string() << ")";
}

/**
 * explain how this precedence works.
 */
void Mult::pretty_print(std::ostream& ot){
    pretty_print_at(ot, prec_none);
}

/**
 * \brief Adds parentheses if precedence is high enough, which for mult means it was called by a mult.
 */
void Mult::pretty_print_at(std::ostream& ot, precedence_t prec){
    bool doParen = prec >= prec_mult;
    if(doParen)
        ot << "(";
    lhs->pretty_print_at(ot, prec_mult);
    ot << " * ";
    rhs->pretty_print_at(ot, prec_add);
    if(doParen)
        ot << ")";
}

Var::Var(const std::string &name){
    this->name = name;
}

bool Var::Equals(Expr *e)
{
    //dynamic cast, check for null
    Var *c = dynamic_cast<Var*>(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name;
}

/**
 * \brief interp is not defined (at this developmen stage) for variables, so we return an error
 */
int Var::interp()
{
    throw std::runtime_error("VarExpr does not support interp (at this stage in development)");
}

bool Var::has_variable(){
    return true;
}

Expr* Var::subst(const std::string &name, Expr* substitution){
    if(this->name == name)
        return substitution;
    else
        return this;
}

void Var::printExpr(std::ostream& ot){
    ot << name;
}

Let::Let(const std::string &name, Expr* lhs, Expr* rhs)
{
    this->name = name;
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Let::Equals(Expr *e)
{
    //dynamic cast, check for null
    Let *c = dynamic_cast<Let*>(e);
    if(c == nullptr)
        return false;
    
    return this->name == c->name && this->lhs->Equals(c->lhs) && this->rhs->Equals(c->rhs);
}

int Let::interp(){
    rhs->subst(name, lhs)->interp();
}

bool Let::has_variable(){
    return rhs->has_variable();
}

//TESTING
//
TEST_CASE( "Expression Equality") {
    SECTION("Num tests"){
        CHECK((new Num(10))->Equals(new Num(10)));
        CHECK_FALSE((new Num(10))->Equals(new Num(5)));
        CHECK_FALSE((new Num(10))->Equals(new Var("a")));
    }
    
    SECTION("Add tests"){
        CHECK((new Add(new Num(2), new Num(3)))->Equals(new Add(new Num(2), new Num(3))));
        CHECK_FALSE((new Add(new Num(2), new Num(3)))->Equals(new Add(new Num(3), new Num(2))));
        CHECK_FALSE((new Var("a"))->Equals(new Num(2)));
    }
    
    SECTION("Mult tests"){
        CHECK((new Mult(new Num(2), new Num(3)))->Equals(new Mult(new Num(2), new Num(3))));
        CHECK_FALSE((new Mult(new Num(2), new Num(3)))->Equals(new Mult(new Num(3), new Num(2))));
        CHECK_FALSE((new Var("a"))->Equals(new Num(2)));
    }

    SECTION("VarExpr tests"){
        CHECK((new Var("a"))->Equals((new Var("a"))));
        CHECK_FALSE((new Var("a"))->Equals((new Var("b"))));
        CHECK_FALSE((new Var("a"))->Equals(new Num(2)));
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
        CHECK_THROWS_WITH( (new Var("x"))->interp(), "VarExpr does not support interp (at this stage in development)" );
    }

    SECTION("Assignment tests"){
        CHECK( (new Mult(new Num(3), new Num(2)))->interp()==6 );
        CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp()==65);
    }
}

TEST_CASE("has_var"){
    CHECK( (new Add(new Var("x"), new Num(1)))->has_variable() == true );
    CHECK( (new Mult(new Num(2), new Num(1)))->has_variable() == false );
}

TEST_CASE("substitution")
{
    CHECK( (new Add(new Var("x"), new Num(7)))
       ->subst("x", new Var("y"))
       ->Equals(new Add(new Var("y"), new Num(7))) );
    CHECK( (new Var("x"))
       ->subst("x", new Add(new Var("y"),new Num(7)))
       ->Equals(new Add(new Var("y"),new Num(7))) );
    CHECK( (new Add(new Var("x"), new Num(5)))
        ->subst("x", new Num(3))
        ->interp() == 8);
    CHECK( (new Mult(new Var("x"), new Var("y")))
        ->subst("x", new Num(3))
        ->subst("y", new Num(4))
        ->interp() == 12);
}

TEST_CASE("to_string")
{
    CHECK((new Num(3))->to_string() == "3");
    CHECK((new Var("x"))->to_string() == "x");
    CHECK((new Add(new Num(3), new Num(4)))->to_string() == "(3+4)");
    CHECK((new Mult(new Num(3), new Num(4)))->to_string() == "(3*4)");

    CHECK((new Add(new Num(3), new Mult(new Var("x"), new Num(4))))->to_string() == "(3+(x*4))");
    CHECK((new Mult(new Num(3), new Add(new Var("x"), new Num(4))))->to_string() == "(3*(x+4))");
}

TEST_CASE("pretty_print")
{
    CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
    CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() ==  "(8 * 1) * y" );
    CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
    CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );
}
