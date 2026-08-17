#include "PlayfairCipher.h"
#include "Alphabet.h"

#include <algorithm>
#include <string>
#include <iostream>

PlayfairCipher::PlayfairCipher( const std::string& formattedKey ) : key_{""} { 
    setKey( formattedKey );
}

void PlayfairCipher::setKey( const std::string& formattedKey ){ 
    // Reset key to be an empty string
    key_ = formattedKey; 
    
    // Append the alphabet to the end
    key_ += Alphabet::letters;

    // Transform J -> I 
    std::transform( key_.begin(), key_.end(), key_.begin(), 
                    [](const char c){ 
                        return ( c == 'J' ? 'I' : c ); 
                    } );

    // Remove duplicate letters
    std::string foundLetters{""};

    // Find duplicate lambda function 
    auto findDuplicate = [&foundLetters](const char c){ 
        if ( foundLetters.find( c ) == std::string::npos ){
            foundLetters += c; 
            return false;
        } 
        return true;
    };

    // Remove duplicates (placed at end by remove_if)
    key_.erase( std::remove_if( key_.begin(), key_.end(), findDuplicate ), 
                key_.end() ); 

    // Reset maps between grid position and character
    characterToPositionMap_.clear();

    for ( size_t i{0}; i < key_.size(); i++ ){
        std::pair< size_t, size_t > coord{ 
            i / gridSize_, 
            i % gridSize_ 
        };
        characterToPositionMap_[ key_[i] ] = coord; 
    }

    return;
}

void PlayfairCipher::printGrid() const {
    for ( size_t i{0}; i < gridSize_; i++ ){ 
        for ( size_t j{0}; j < gridSize_; j++ ){
            std::cout << " " << key_[ i*gridSize_ + j ];
        }
        std::cout << "\n"; 
    }
    return;
}


std::string PlayfairCipher::processString( const std::string& formatInputString, 
                                           const CipherMode& cipherMode ) const { 
    std::string outputString{ formatInputString };

    // Replace J -> I 
    std::transform( outputString.begin(), outputString.end(), outputString.begin(), 
                    [](const char c){ 
                        return ( c == 'J' ? 'I' : c ); 
                    } );
    
    

    // Check bigraphs for repeated letters 
    std::string tmpString{""};
    for ( size_t i{0}; i < outputString.size(); i+=2 ){ 
        tmpString += outputString[i];
        if ( outputString[i] != outputString[i+1] ){
            tmpString += outputString[i+1];
        }
        else {
            tmpString += ('X' == outputString[i] ? 'Q' : 'X' );
            --i; 
        }
    }

    // Append a Z if the string has an odd length
    if ( 1 == outputString.length() % 2 ) outputString += "Z";

    // Replace outputString by tmpString 
    outputString.swap( tmpString );

    // Row/Column shift based on CipherMode::Encrypt or CipherMode::Decrypt
    const size_t shift = ( cipherMode == CipherMode::Encrypt ? 1 : gridSize_ - 1 ); 

    // Process bigrams
    for ( size_t i{0}; i < outputString.size(); i+=2 ){ 
        auto [rowOne,colOne] { characterToPositionMap_.at( outputString[i]   ) }; 
        auto [rowTwo,colTwo] { characterToPositionMap_.at( outputString[i+1] ) }; 

        if ( rowOne == rowTwo ){ 
            // If same row shift up/down in column
            colOne  = ( colOne + shift ) % gridSize_; 
            colTwo  = ( colTwo + shift ) % gridSize_; 
        }
        else if ( colOne == colTwo ){ 
            // If same column shift forward/backward in row
            rowOne = ( rowOne + shift ) % gridSize_; 
            rowTwo = ( rowTwo + shift ) % gridSize_; 
        }
        else { 
            // Else swap colums for square
            std::swap( colOne, colTwo );
        }

        outputString[i]   = key_.at( rowOne*gridSize_ + colOne );
        outputString[i+1] = key_.at( rowTwo*gridSize_ + colTwo );
    }

    return outputString;
}