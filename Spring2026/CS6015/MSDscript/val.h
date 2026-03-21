/**
 * \file val.h
 * \brief contains Val "value" class as well as Num... subclasses
 */

#include <string>

/**
 * \brief Value class, supporting interpreter grammar
 * 〈val〉 = 〈number〉
 *  | 〈boolean〉
 */
class Val
{
public:
    virtual bool equals(Val* e) = 0;
    virtual Val* add_to(Val* rhs) = 0;
    virtual Val* mult_with(Val* rhs) = 0;
    virtual std::string to_string() = 0;
};

class NumVal: public Val{
public:
    int val;

    NumVal(int val);

    bool equals(Val* e);
    Val* add_to(Val* rhs);
    Val* mult_with(Val* rhs);
    std::string to_string();
};