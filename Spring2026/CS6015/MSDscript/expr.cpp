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
 * For Num and Add, printExpr prints them without considering
 * parentheses or precence
 */
void Expr::pretty_print(std::ostream& ot){
    this->printExpr(ot);
}

/**
 * Default return of lowest precedence: "none".
 */
precedence_t Expr::pretty_print_at(){
    return prec_none;
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
 * Returns itself, as number values do not change in substitution
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
    // bool parenLeft = lhs->pretty_print_at() < this->pretty_print_at();
    // bool parenRight = rhs->pretty_print_at() < this->pretty_print_at();
    // if(parenLeft)
    //     ot << "( ";
    lhs->pretty_print(ot);
    // if(parenLeft)
    //     ot << " )";
    ot << " + ";
    // if(parenRight)
    //     ot << "( ";
    rhs->pretty_print(ot);
    // if(parenRight)
    //     ot << " )";
}

/**
 * Returns precedence higher than 'none', but lower than 'mult'
 */
precedence_t Add::pretty_print_at(){
    return prec_add;
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
    bool parenLHS = lhs->pretty_print_at() == 1;
    bool parenRHS = rhs->pretty_print_at() == 1;
    if(parenLHS)
        ot << "(";
    lhs->pretty_print(ot);
    if(parenLHS)
        ot << ")";
    ot << " * ";
    if(parenRHS)
        ot << "(";
    rhs->pretty_print(ot);
    if(parenRHS)
        ot << ")";
}

/**
 * Returns precedence higher than 'none', but lower than 'mult'
 */
precedence_t Mult::pretty_print_at(){
    return prec_mult;
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

TEST_CASE("has_var"){
    CHECK( (new Add(new VarExpr("x"), new Num(1)))->has_variable() == true );
    CHECK( (new Mult(new Num(2), new Num(1)))->has_variable() == false );
}

TEST_CASE("substitution")
{
    CHECK( (new Add(new VarExpr("x"), new Num(7)))
       ->subst("x", new VarExpr("y"))
       ->Equals(new Add(new VarExpr("y"), new Num(7))) );
    CHECK( (new VarExpr("x"))
       ->subst("x", new Add(new VarExpr("y"),new Num(7)))
       ->Equals(new Add(new VarExpr("y"),new Num(7))) );
    CHECK( (new Add(new VarExpr("x"), new Num(5)))
        ->subst("x", new Num(3))
        ->interp() == 8);
    CHECK( (new Mult(new VarExpr("x"), new VarExpr("y")))
        ->subst("x", new Num(3))
        ->subst("y", new Num(4))
        ->interp() == 12);
}

TEST_CASE("to_string")
{
    CHECK((new Num(3))->to_string() == "3");
    CHECK((new VarExpr("x"))->to_string() == "x");
    CHECK((new Add(new Num(3), new Num(4)))->to_string() == "(3+4)");
    CHECK((new Mult(new Num(3), new Num(4)))->to_string() == "(3*4)");

    CHECK((new Add(new Num(3), new Mult(new VarExpr("x"), new Num(4))))->to_string() == "(3+(x*4))");
    CHECK((new Mult(new Num(3), new Add(new VarExpr("x"), new Num(4))))->to_string() == "(3*(x+4))");
}

TEST_CASE("pretty_print")
{
    CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
    CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new VarExpr("y")))->to_pretty_string() ==  "(8 * 1) * y" );
    CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
    CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );
}