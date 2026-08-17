#ifndef PROCESSCOMMANDLINE_H
#define PROCESSCOMMANDLINE_H

#include <vector> 
#include <string> 

#include "CipherMode.h"

struct ProgramSettings { 
    std::string inputFileName{""}; 
    std::string outputFileName{""}; 
    std::string cipherKey{""};
    CipherMode programMode{ CipherMode::Unspecified }; 
    CipherType cipherType{ CipherType::Unspecified }; 
    bool verbosePrinting{ false }; 
};

bool processCommandLine( const std::vector< std::string >& cmdArgs, 
                         ProgramSettings& programSettings );

#endif 