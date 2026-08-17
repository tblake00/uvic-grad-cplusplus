#ifndef CIPHER_H
#define CIPHER_H

#include "CipherMode.h"
#include <string>

class Cipher { 
public:
    Cipher() = default;

    Cipher( const Cipher& other ) = default;

    Cipher( Cipher&& other ) = default;

    Cipher& operator=( const Cipher& other ) = default;

    Cipher& operator=( Cipher&& other ) = default;

    virtual ~Cipher() = default;

    virtual void setKey( const std::string& formattedKey ) = 0; 

    virtual std::string processString( const std::string& formattedInputString, 
                                       const CipherMode& cipherMode ) const = 0; 

    virtual CipherType getType() const = 0;                                   
};

#endif 
