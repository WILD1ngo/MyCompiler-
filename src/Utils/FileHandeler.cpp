#include "FileHandeler.h"
#include <iostream>



std::string read_input()
{
    std::string input;
    std::string fullText;


    while (std::getline(std::cin, input)) {
        fullText += input + "\n";  // Append each line with a newline
    }

    return fullText;
}