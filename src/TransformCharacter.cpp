#include "TransformCharacter.h"
#include <string> 



char AlphabetTransform::shiftPosition( const char inputChar, 
                                       const size_t offsetChar, 
                                       const int processMode ){ 
    const size_t posChar{ AlphabetTransform::alphabetLetters.find( inputChar ) };

    if ( posChar == std::string::npos ){ 
        return inputChar; 
    }

    size_t posTran{ 0 }; 

    if ( 0 == processMode ){ 
        posTran = ( offsetChar + posChar ); 
    } else { 
        posTran = ( AlphabetTransform::alphabetLength - offsetChar + posChar ); 
    }

    return AlphabetTransform::alphabetLetters[ posTran % AlphabetTransform::alphabetLength ];
}

char AlphabetTransform::shiftCharacter( const char inputChar, 
                                        const char offsetChar, 
                                        const int processMode ){ 
    const size_t posChar{ AlphabetTransform::alphabetLetters.find( offsetChar ) };

    if ( posChar == std::string::npos ){ 
        return inputChar; 
    }

    return AlphabetTransform::shiftPosition( inputChar, posChar, processMode ); 
}


char CharacterTransform::shiftPosition( const char inputChar, 
                                        const size_t offsetChar, 
                                        const int processMode ){ 

    size_t posTran{ 0 };

    if ( 0 == processMode ){ 
        posTran = ( inputChar - 'A' ) + offsetChar; 
    } else { 
        posTran = ( inputChar - 'A' ) + 26 - offsetChar; 
    }

    return 'A' +  ( posTran % 26 );
}

char CharacterTransform::shiftCharacter( const char inputChar, 
                                         const char offsetChar, 
                                         const int processMode ){ 
    const size_t offsetPos = static_cast< size_t >( offsetChar - 'A' );
    return CharacterTransform::shiftPosition( inputChar, offsetPos, processMode ); 
} 