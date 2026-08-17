#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include "CipherMode.h"
#include "CaesarCipher.h"
#include <string> 
#include <vector>

class VigenereCipher : public Cipher {
public: 
    explicit VigenereCipher( const std::string& formattedKey ); 

    virtual ~VigenereCipher() = default;

    virtual void setKey( const std::string& formattedKey ) override; 

    virtual std::string processString( const std::string& formatInputString, 
                               const CipherMode& processMode ) const override;

    std::string getKey() const { return key_; }

    virtual CipherType getType() const override { 
        return CipherType::Vigenere; 
    }

private:
    std::string key_; 
    std::vector< CaesarCipher > ciphers_;
};


#endif 