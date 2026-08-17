#include "VigenereCipher.h"

VigenereCipher::VigenereCipher( const std::string& formattedKey ) { 
    setKey( formattedKey ); 
}

void VigenereCipher::setKey( const std::string& formattedKey ){
    
    for ( const auto inputChar: formattedKey ){ 
        ciphers_.emplace_back( inputChar );
    }
    
    return; 
}

std::string VigenereCipher::processString( const std::string& formatInputString,
                                           const CipherMode& processMode ) const { 

    std::string outputString{""};
    std::string inputString{""};
    
    const size_t numCiphers = ciphers_.size();

    for ( size_t i{0}; i < formatInputString.length(); i++ ){
        inputString   = formatInputString[i];
        outputString += ciphers_[ i % numCiphers ].processString( inputString,
                                                                  processMode );
    }
    return outputString; 
}