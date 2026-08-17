#include "CipherFactory.h"
#include "CipherMode.h"
#include "CaesarCipher.h"
#include "PlayfairCipher.h"
#include "VigenereCipher.h"

std::unique_ptr<Cipher> CipherFactory::makeCipher( const CipherType cipherType, 
                                                   const std::string& formattedKey  ){
    switch ( cipherType ){ 
        case CipherType::Caesar: 
            return std::make_unique< CaesarCipher >( formattedKey );
        case CipherType::Playfair:
            return std::make_unique< PlayfairCipher >( formattedKey );
        case CipherType::Vignere: 
            return std::make_unique< VigenereCipher >( formattedKey );
        case CipherType::AlphabetCaesar: 
            return std::make_unique< AlphabetCaesarCipher >( formattedKey );
        case CipherType::Unspecified:
            return std::unique_ptr<Cipher>( nullptr );
    }
    return std::unique_ptr<Cipher>( nullptr ); 
}