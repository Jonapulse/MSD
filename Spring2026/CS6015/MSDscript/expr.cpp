/**
 * \file expression.cpp
 * \brief contains Expr "expression" implementation as well as Num, Var, Add, Mult, and Let subclass implementations.
 */

#include "expr.h"
#include "val.h"
#include "catch.h"

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
    this->val = new NumVal(val);
}

NumExpr::NumExpr(Val* val){
    NumVal *c = dynamic_cast<NumVal*>(val);
    if(c == nullptr)
        throw std::runtime_error("Error: NumExpr initialized with non-NumVal Val");
    this->val = c;
}

bool NumExpr::equals(Expr *e)
{
    //dynamic cast, check for null
    NumExpr *c = dynamic_cast<NumExpr*>(e);
    if(c == nullptr)
        return false;
    return this->val->equals(c->val);
}

Val* NumExpr::interp()
{
    return this->val;
}

bool NumExpr::has_variable()
{
    return false;
}

/**
 * \brief Returns itself, as number values do not change in substitution
 */
Expr* NumExpr::subst(const std::string &name, Expr* substitution){
    return this;
}

void NumExpr::printExpr(std::ostream& ot){
    ot << val->to_string();
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

bool AddExpr::has_variable()
{
    return lhs->has_variable() || rhs->has_variable();
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

bool MultExpr::has_variable()
{
    return lhs->has_variable() || rhs->has_variable();
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
    throw std::runtime_error("Error: VarExpr does not support interp (at this stage in development)");
}

bool VarExpr::has_variable(){
    return true;
}

Expr* VarExpr::subst(const std::string &name, Expr* substitution){
    if(this->name == name)
        return substitution;
    else
        return this;
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
    return lhs->subst(name, new NumExpr(rhs->interp()))->interp();
}

/**
 * \brief
 */
bool LetExpr::has_variable(){
    return rhs->has_variable();
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
    return lhs->subst(name, substitution);
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


//TESTING for expr.cpp
//
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

    SECTION("VarExpr tests"){
        CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "Error: VarExpr does not support interp (at this stage in development)" );
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
}

TEST_CASE("has_var"){
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(1)))->has_variable());
    CHECK_FALSE( (new MultExpr(new NumExpr(2), new NumExpr(1)))->has_variable());
    CHECK((new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(5)), new AddExpr(new VarExpr("x"), new NumExpr(1))))->has_variable());
    CHECK_FALSE((new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->has_variable());
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
