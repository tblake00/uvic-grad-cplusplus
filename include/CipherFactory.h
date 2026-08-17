#ifndef CIPHERFACTORY_H
#define CIPHERFACTORY_H

#include "CipherMode.h"
#include "Cipher.h"
#include <memory>
#include <string>

namespace CipherFactory { 
    std::unique_ptr<Cipher> makeCipher( const CipherType cipherType, 
                                        const std::string& formattedKey );
}

#endif 