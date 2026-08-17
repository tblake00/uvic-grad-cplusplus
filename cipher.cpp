#include <iostream> 
#include <fstream>
#include <vector>  
#include <string>
#include <cctype>
#include <memory> 

#include "Cipher.h"
#include "ProcessCommandLine.h"
#include "TransformCharacter.h"
#include "TextFormatting.h"
#include "CipherMode.h"
#include "CipherFactory.h"


using namespace CharacterTransform; 

int main( int argc, char** argv ){ 

    // Convert argv to vector of strings
    const std::vector< std::string > cmdArgs{ argv, argv + argc }; 

    // Process command line arguments
    ProgramSettings programOpt; 
    bool checkArgs = processCommandLine( cmdArgs, programOpt );

    if ( !checkArgs ){
        std::cout << "Invalid arguments specified, exiting" << std::endl;
        return 1;
    }

    if ( CipherType::Unspecified == programOpt.cipherType ){ 
       std::cout << "No cipher type specfied, exiting" << std::endl;
       return 1; 
    }

    if ( CipherMode::Unspecified == programOpt.programMode ){
        std::cout << "No process specfied, exiting" << std::endl;
        return 1;
    }

    // Formatted cipher key
    std::string cipherKey = formatInputString( programOpt.cipherKey );

    // Print input/output file names
    if( programOpt.verbosePrinting ){ 
        std::cout << "Input  file = " 
                  << ( programOpt.inputFileName.empty() ? 
                        "None" : programOpt.inputFileName ) 
                  << std::endl;
        std::cout << "Output file = " 
                  << ( programOpt.outputFileName.empty() ? 
                        "None" : programOpt.outputFileName ) 
                  << std::endl;
    }


    std::string textToProcess{""};

    // If input file specified, read from file otherwise read from
    // keyboard
    if ( programOpt.inputFileName.empty() ){ 
        std::getline( std::cin, textToProcess );
    }
    else { 
        std::ifstream inputFile{ programOpt.inputFileName };
        if ( inputFile.good() ){ 
            std::getline( inputFile, textToProcess );
            inputFile.close();
        }
        else { 
            std::cout << "Cannot open " << programOpt.inputFileName << std::endl;
            return 1; 
        }
    }

    // Reformat input string
    std::string textAfterFormatting = formatInputString( textToProcess );

    if ( programOpt.verbosePrinting ){ 
        std::cout << "Plain input text is " 
                  << textToProcess << std::endl;
        std::cout << "Processed input text is " 
                  << textAfterFormatting << std::endl;
    }

   

    // Encrypt/decrypt input string
    std::string textAfterEncoding{""};
   
   

    std::unique_ptr< Cipher > cipherImpl = 
        CipherFactory::makeCipher( programOpt.cipherType, cipherKey );

    if ( cipherImpl == nullptr ){ 
        std::cout << "Unknown Cipher type" << std::endl;
        return 1; 
    }

    // if ( programOpt.cipherType == CipherType::Caesar ){
    //     CaesarCipher cipherImpl( cipherKey );
        textAfterEncoding = cipherImpl->processString( textAfterFormatting, 
                                                       programOpt.programMode );
    //}

    // if ( programOpt.cipherType == CipherType::Playfair ){
    //     PlayfairCipher playfairImpl( cipherKey ); 
    //     if ( programOpt.verbosePrinting ){ 
    //         playfairImpl.printGrid();
    //     }
    //     textAfterEncoding = playfairImpl.processString( textAfterFormatting, 
    //                                                     programOpt.programMode );
    // }

    // If output file name specified output to file otherwise 
    // output to the screen (also output if verbose printing
    // is enabled). 
    if ( programOpt.outputFileName.empty() || programOpt.verbosePrinting  ){ 
        if ( CipherMode::Encrypt == programOpt.programMode ){
            std::cout << "Encrypted text is " << textAfterEncoding 
                      << std::endl; 
        }
        else if ( CipherMode::Decrypt == programOpt.programMode ){ 
            std::cout << "Decrypted text is " << textAfterEncoding 
                      << std::endl; 
        }
    }
    else {
        std::ofstream outputFile{ programOpt.outputFileName };
        if ( outputFile.good() ){ 
            outputFile << textAfterEncoding; 
            outputFile.close();
        }
        else {
            std::cout << "Cannot open " 
                      << programOpt.outputFileName << std::endl;
        }
    }

    return 0; 
}