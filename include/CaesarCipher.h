#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "Cipher.h"
#include "CipherMode.h"
#include <string> 

class CaesarCipher : public Cipher  { 
public:
    explicit CaesarCipher( const std::string& formattedKey );

    explicit CaesarCipher( const char inputChar );

    virtual ~CaesarCipher() = default;

    virtual std::string processString( const std::string& inputString, 
                                       const CipherMode& cipherMode ) const override; 

    std::string getKey() const;

    virtual void setKey( const std::string& formattedKey ) override; 

    virtual CipherType getType() const override { return CipherType::Caesar; }

    void setPosition( const size_t keyPosition );

private:
    char shiftCharacter( const char inputChar, size_t cipherShift ) const;

    size_t pos_{ 0 };
};


class AlphabetCaesarCipher : public Cipher { 
public:
    explicit AlphabetCaesarCipher( const std::string& formattedKey );

    explicit AlphabetCaesarCipher( const char inputChar );

    virtual ~AlphabetCaesarCipher() = default;

    virtual std::string processString( const std::string& inputString, 
                               const CipherMode& cipherMode ) const override;  

    std::string getKey() const;

    virtual void setKey( const std::string& formattedKey ) override; 

    virtual CipherType getType() const override { return CipherType::AlphabetCaesar; }

    void setPosition( const size_t keyPosition );

private:
    char shiftCharacter( const char inputChar, const size_t cipherShift ) const;

    size_t pos_{ 0 };
};

#endif 