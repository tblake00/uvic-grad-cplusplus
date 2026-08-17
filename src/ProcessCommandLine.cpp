#include "ProcessCommandLine.h"
#include "CipherExceptions.h"
#include "Version.h"
#include <string>
#include <iostream>


void processCommandLine( const std::vector< std::string >& cmdArgs, 
                         ProgramSettings& programOpt ) {
    
    const size_t nLastArg = cmdArgs.size()-1;

    for ( size_t i{1}; i < cmdArgs.size(); i++ ){ 
        if ( cmdArgs[i] == "-h" || 
             cmdArgs[i] == "--help" ){
            std::cout << "Usage:\n" 
                      << "\t" << cmdArgs[0] 
                      << " -i <input> -o <output> -h --encrypt -t <type> -k <key>" 
                      << "\n" << "or \n"
                      << "\t" << cmdArgs[0] 
                      << " -i <input> -o <output> -h --decrypt -t <type> -k <key>" 
                      << std::endl;
        }
        else if ( cmdArgs[i] == "-v" ||
                  cmdArgs[i] == "--version" ){ 
            std::cout << "Version " 
                      << Cipher_VERSION_MAJOR << "." << Cipher_VERSION_MINOR 
                      << std::endl;
        }
        else if ( cmdArgs[i] == "-i" || 
                  cmdArgs[i] == "--input" ){
            if ( i == nLastArg || cmdArgs[i+1][0] == '-' ){ 
                throw MissingArgument("--input [-i] expects an argument"); 
            }
            else {
                programOpt.inputFileName = cmdArgs[++i]; 
            }
        }
        else if ( cmdArgs[i] == "-o" || 
                  cmdArgs[i] == "--output" ){
            if ( i == nLastArg || cmdArgs[i+1][0] == '-' ){ 
                throw MissingArgument("--output [-o] expects an argument"); 
            }
            else {
                programOpt.outputFileName = cmdArgs[++i]; 
            }
        }
        else if ( cmdArgs[i] == "-k" || cmdArgs[i] == "--key" ){
            if ( i == nLastArg || cmdArgs[i+1][0] == '-' ){ 
                throw MissingArgument("--key [-k] expects an argument");
            } 
            else {
                programOpt.cipherKey = cmdArgs[++i];
            }
        }
        else if ( cmdArgs[i] == "-t" || cmdArgs[i] == "--type" ){ 
            if ( i == nLastArg || cmdArgs[i+1][0] == '-' ){ 
                throw MissingArgument("--type [-t] expects an argument");
            }
            
            if ( cmdArgs[i+1] == "caesar" || 
                 cmdArgs[i+1] == "CAESAR" ) { 
                programOpt.cipherType = CipherType::Caesar; 
                i++; 
            } 
            else if ( cmdArgs[i+1] == "playfair" || 
                      cmdArgs[i+1] == "PLAYFAIR" ){ 
               programOpt.cipherType = CipherType::Playfair; 
               i++;  
            }
            else if ( cmdArgs[i+1] == "vigenere" || 
                      cmdArgs[i+1] == "VIGENERE" ){
                programOpt.cipherType = CipherType::Vigenere;
                i++; 
            }
            else { 
                throw InvalidArgument("--type [-t] received " + cmdArgs[i+1]);
            }
        }
        else if ( cmdArgs[i] == "--encrypt" ){
            programOpt.programMode = CipherMode::Encrypt;
        }
        else if ( cmdArgs[i] == "--decrypt" ){
            programOpt.programMode = CipherMode::Decrypt; 
        } 
        else if ( cmdArgs[i] == "--verbose" ){ 
            programOpt.verbosePrinting = true; 
        } else { 
            throw UnkownArgument( cmdArgs[i] );
        }
    }

    return; 
}