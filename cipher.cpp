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
#include "CipherExceptions.h"


using namespace CharacterTransform; 

int main( int argc, char** argv ){ 

    // Convert argv to vector of strings
    const std::vector< std::string > cmdArgs{ argv, argv + argc }; 

    // Process command line arguments
    ProgramSettings programOpt; 
    try { 
        processCommandLine( cmdArgs, programOpt );
    }
    catch ( const MissingArgument& except ){  
        std::cerr << " [ERROR] Missing argument: " << except.what() << std::endl;
        return 1; 
    }
    catch ( const InvalidArgument& except ){ 
        std::cerr << " [ERROR] Invalid argument: " << except.what() << std::endl;
    }
    catch ( const UnkownArgument& except ){ 
        std::cerr << " [ERROR] Unkown argument: " << except.what() << std::endl; 
    }

    if ( CipherType::Unspecified == programOpt.cipherType ){ 
       std::cerr << " [ERROR] No cipher type specfied" << std::endl;
       return 1; 
    }

    if ( CipherMode::Unspecified == programOpt.programMode ){
        std::cerr << " [ERROR] No process specfied " << std::endl;
        return 1;
    }

    // Formatted cipher key
    std::string cipherKey = formatInputString( programOpt.cipherKey );
    if ( cipherKey.empty() ){
        std::cerr << " [ERROR] Invalid cipher key " << std::endl;
    }

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
            std::cerr << " [ERROR] Cannot open " << programOpt.inputFileName << std::endl;
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
        std::cerr << " [ERROR] Factory returned unknown Cipher type" << std::endl;
        return 1; 
    }

    textAfterEncoding = cipherImpl->processString( textAfterFormatting, 
                                                   programOpt.programMode );
     
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
            std::cerr << " [ERROR] Cannot open " 
                      << programOpt.outputFileName << std::endl;
        }
    }

    return 0; 
}