/**
* \file environment.h
* \brief describes variable environments for resolving variable evaluation
*/

#ifndef env_h
#define env_h

#include <string>
#include "pointer.h"

//Referencing Val without full #include
//
class Val;

CLASS(Env){
public:
    virtual PTR(Val) lookup(std::string find_name) = 0;
    static PTR(Env) empty;
};

class EmptyEnv : public Env{
public:
    PTR(Val) lookup(std::string find_name);
};

class ExtendedEnv : public Env{
public:
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;
    
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
    PTR(Val) lookup(std::string find_name);
};

#endif
