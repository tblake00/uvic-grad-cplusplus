#ifndef CIPHERMODE_H
#define CIPHERMODE_H


enum class CipherMode { 
    Unspecified,
    Encrypt, 
    Decrypt
};

enum class CipherType { 
    Unspecified, 
    Caesar, 
    AlphabetCaesar,
    Playfair, 
    Vignere 
};

#endif 