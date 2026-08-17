#ifndef CIPHEREXCEPTIONS_H
#define CIPHEREXCEPTIONS_H

#include <stdexcept>
#include <string> 

class MissingArgument : public std::invalid_argument {
public:
    MissingArgument( const std::string& msg ) :
        std::invalid_argument{msg}{}
};

class UnkownArgument : public std::invalid_argument { 
public:
    UnkownArgument( const std::string& msg ) :
        std::invalid_argument{msg}{}
}

class InvalidKey : public std::invalid_argument {
public:
    InvalidKey( const std::string& msg ) : 
        std::exception{ msg }{}
}

#endif