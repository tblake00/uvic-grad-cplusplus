#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include "CipherMode.h"
#include "Cipher.h"

#include <string> 
#include <map> 

class PlayfairCipher : public Cipher { 
public:
    using Coordinate = std::pair< size_t, size_t >; 

    explicit PlayfairCipher( const std::string& key );

    virtual ~PlayfairCipher() = default; 

    virtual void setKey( const std::string& key ) override;

    void printGrid() const; 

    virtual std::string processString( const std::string& formatInputString, 
        const CipherMode& cipherMode ) const override; 

    std::string getKey() const { return key_; }

    virtual CipherType getType() const override { return CipherType::Playfair; } 

private:

    std::string key_; 

    static constexpr size_t gridSize_{ 5 };

    std::map< char, Coordinate > characterToPositionMap_;
};

#endif 