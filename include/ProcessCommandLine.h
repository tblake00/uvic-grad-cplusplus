#ifndef PROCESSCOMMANDLINE_H
#define PROCESSCOMMANDLINE_H

#include <vector> 
#include <string> 

bool processCommandLine( const std::vector< std::string >& cmdArgs, 
                         std::string& inputFileName,
                         std::string& outputFileName,
                         std::string& cipherKey, 
                         int& processMode,
                         bool& printVerbose );

#endif 