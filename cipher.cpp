#include <iostream> 
#include <fstream>
#include <vector>  
#include <string>
#include <cctype> 

#include "ProcessCommandLine.h"
#include "TransformCharacter.h"
#include "TextFormatting.h"

using namespace CharacterTransform; 

std::string formatInputString( const std::string& inputString ){ 
    std::string processedString{""};

    for ( size_t i{0}; i < inputString.size(); i++ ){ 
        if ( std::isalpha( inputString[i] ) ){
            processedString += std::toupper( inputString[i] );
        }
        else if ( std::isdigit( inputString[i] ) ){
            processedString += numberToWord( inputString[i] );
        }
    }

    return processedString;
}

std::string processFormattedString( const std::string& inputString, 
                                    const std::string& cipherKey, 
                                    const int processMode ){
     
    std::string processedString{""}; 

    for ( size_t i{0}; i < inputString.size(); i++ ){
        processedString += shiftCharacter( inputString[i], cipherKey[0], processMode );
    }

    return processedString; 
}


int main( int argc, char** argv ){ 
    const std::vector< std::string > cmdArgs{ argv, argv + argc }; 

    std::string inputFileName{""};
    std::string outputFileName{""};
    std::string cipherKey{""};

    int processMode{-1}; 
    bool printVerbose{ false };

    bool checkArgs = processCommandLine( cmdArgs, 
                        inputFileName, outputFileName, cipherKey, 
                        processMode, printVerbose );

    if ( !checkArgs ){
        std::cout << "Invalid arguments specified, exiting" << std::endl;
        return 1;
    }
    
    if( printVerbose ){ 
        std::cout << "Input  file = " << (inputFileName.empty() ? "None" : inputFileName) << std::endl;
        std::cout << "Output file = " << (outputFileName.empty() ? "None" : outputFileName) << std::endl;
    }

    if ( processMode < 0 ){
        std::cout << "No process specfied, exiting" << std::endl;
        return 1;
    }

    std::string textToProcess{""};

    if ( inputFileName.empty() ){ 
        std::getline( std::cin, textToProcess );
    }
    else { 
        std::ifstream inputFile{ inputFileName };
        if ( inputFile.good() ){ 
            inputFile >> textToProcess; 
            inputFile.close();
        }
        else { 
            std::cout << "Cannot open " << inputFileName << std::endl;
            return 1; 
        }
    }

    if ( cipherKey.size() != 1 ){ 
        std::cout << "Invalid cipher key specified" << std::endl;
        return 1;
    }

   
    std::string textAfterFormatting = formatInputString( textToProcess );
    

    if ( printVerbose ){ 
        std::cout << "Plain input text is " << textToProcess << std::endl;
        std::cout << "Processed input text is " << textAfterFormatting << std::endl;
    }

    std::string textAfterEncoding = processFormattedString( textAfterFormatting, cipherKey, processMode );

    if ( outputFileName.empty() || printVerbose ){ 
        std::cout << ( processMode ? "Decrypted" : "Encrypted" ) << " text is " << textAfterEncoding << std::endl; 
    }
    else {
        std::ofstream outputFile{ outputFileName };
        if ( outputFile.good() ){ 
            outputFile << textAfterEncoding; 
            outputFile.close();
        }
        else {
            std::cout << "Cannot open " << outputFileName << std::endl;
        }
    }

    return 0; 
}