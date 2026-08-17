#include "ProcessCommandLine.h"
#include "Version.h"
#include <string>
#include <iostream>


bool processCommandLine( const std::vector< std::string >& cmdArgs, 
                         ProgramSettings& programOpt ) {

    for ( size_t i{1}; i < cmdArgs.size(); i++ ){ 
        if ( cmdArgs[i] == "-h" || 
             cmdArgs[i] == "--help" ){
            std::cout << "Usage:\n" 
                      << "\t" << cmdArgs[0] << " -i <input> -o <output> -h --encrypt" 
                      << "\n" << "or \n"
                      << "\t" << cmdArgs[0] << " -i <input> -o <output> -h --decrypt" 
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
            if ( i == cmdArgs.size() - 1 || cmdArgs[i+1][0] == '-' ){ 
                std::cout << "Expected value after -i (--input)" << std::endl;
                return false;
            }
            else {
                programOpt.inputFileName = cmdArgs[++i]; 
            }
        }
        else if ( cmdArgs[i] == "-o" || 
                  cmdArgs[i] == "--output" ){
            if ( i == cmdArgs.size() - 1 || cmdArgs[i+1][0] == '-' ){ 
                std::cout << "Expected value after -o (--output)" << std::endl;
                return false;
            }
            else {
                programOpt.outputFileName = cmdArgs[++i]; 
            }
        }
        else if ( cmdArgs[i] == "-k" || cmdArgs[i] == "--key" ){
            if ( i == cmdArgs.size() - 1 || cmdArgs[i+1][0] == '-' ){ 
                std::cout << "Exepcted value after -k (--key)" << std::endl;
                return false;
            } 
            else {
                programOpt.cipherKey = cmdArgs[++i];
            }
        }
        else if ( cmdArgs[i] == "-t" || cmdArgs[i] == "--type" ){ 
            if ( i == cmdArgs.size() - 1 || cmdArgs[i+1][0] == '-' ){ 
                std::cout << "Exepcted value after -t (--type)" << std::endl;
                return false;
            }
            if ( cmdArgs[i+1] == "caesar" ) { 
                programOpt.cipherType = CipherType::Caesar; 
                i++; 
            } 
            if ( cmdArgs[i+1] == "playfair" ){ 
               programOpt.cipherType = CipherType::Playfair; 
               i++;  
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
            std::cout << "Argument " << cmdArgs[i] 
                      << " is not recognised" << std::endl;
            return false;
        }
    }

    return true; 
}