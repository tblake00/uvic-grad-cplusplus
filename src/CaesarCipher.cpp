#include "CaesarCipher.h"
#include "Alphabet.h"
#include <string>
#include <iostream>
#include <cctype>

using namespace Alphabet;

CaesarCipher::CaesarCipher( const std::string& formattedKey ) {
    setKey( formattedKey ); 
} 

CaesarCipher::CaesarCipher( const char inputChar ){ 
    pos_ = static_cast< size_t >( inputChar - 'A' );
}

void CaesarCipher::setKey( const std::string& formattedKey ){ 
    if ( formattedKey.length() != 1 ){
        std::cout << "Invalid key, using first letter only" 
                  << std::endl;
    }
    pos_  = static_cast< size_t >( formattedKey[0] - 'A' );
    return; 
}

std::string CaesarCipher::getKey() const { 
    return std::string{ static_cast<char>('A' + pos_) };
}

void CaesarCipher::setPosition( const size_t keyPosition ){ 
    if ( keyPosition >= 0 && keyPosition < 26 ){ 
        pos_ = keyPosition;
    }
    return;
}

char CaesarCipher::shiftCharacter( const char inputChar, const size_t cipherShift ) const {
    const size_t posChar = static_cast< size_t >( inputChar - 'A' );
    return 'A' + ( ( posChar + cipherShift ) % 26 );
}

std::string CaesarCipher::processString( const std::string& formattedInputString, 
                                         const CipherMode& cipherMode ) const { 
    const size_t shift = ( cipherMode == CipherMode::Encrypt ? 
                           pos_ : 26 - pos_ ); 
                           
    std::string outputString{""};
    for ( size_t i{0}; i < formattedInputString.size(); i++ ){
        outputString += shiftCharacter( formattedInputString[i], shift );
    }
    return outputString;
}

AlphabetCaesarCipher::AlphabetCaesarCipher( const std::string& formattedKey ){ 
    setKey( formattedKey ); 
}

AlphabetCaesarCipher::AlphabetCaesarCipher( const char inputChar ){ 
    size_t keyPosition = Alphabet::letters.find( inputChar );
    
    if ( keyPosition >= 0 && keyPosition < Alphabet::length ){ 
        pos_ = keyPosition;
    }
    else { 
        std::cout << "Invalid key position, using zero" << std::endl;
    }
}

void AlphabetCaesarCipher::setKey( const std::string& formattedKey ){ 
    if ( formattedKey.length() != 1 ){
        std::cout << "Invalid key, using first letter only" 
                  << std::endl;
    }
    
    size_t keyPosition = Alphabet::letters.find( formattedKey[0] ); 

    if ( keyPosition >= 0 && keyPosition < Alphabet::length ){ 
        pos_ = keyPosition;
    }
    else { 
        std::cout << "Invalid key position, using zero" << std::endl;
    }
    
    return;
}

std::string AlphabetCaesarCipher::getKey() const { 
    return { Alphabet::letters[ pos_ ] };
}

void AlphabetCaesarCipher::setPosition( const size_t keyPosition ) {

    if ( keyPosition >= 0 && keyPosition < Alphabet::length ){ 
        pos_ = keyPosition;
    }

    return;
}

char AlphabetCaesarCipher::shiftCharacter( const char inputChar, const size_t cipherShift ) const { 
    const size_t posChar{ Alphabet::letters.find( inputChar ) };
    if ( posChar == std::string::npos ){ 
        return inputChar;
    }
    return Alphabet::letters[ ( posChar + cipherShift ) % Alphabet::length ];
}

std::string AlphabetCaesarCipher::processString( const std::string& formattedInputString, 
                                                 const CipherMode& cipherMode ) const { 

    const size_t shift = ( cipherMode == CipherMode::Encrypt ? 
                           pos_ : Alphabet::length - pos_ ); 
    
    std::string outputString{""};
    for ( size_t i{0}; i < formattedInputString.size(); i++ ){
        outputString += shiftCharacter( formattedInputString[i], shift );
    }

    return outputString; 
}