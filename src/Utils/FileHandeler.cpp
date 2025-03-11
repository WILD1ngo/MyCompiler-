#include "FileHandeler.h"
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
std::string read_input(int argc, char* argv[])
{
    if (argc < 2) { // Check if filename is provided
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        throw std::invalid_argument("No filename provided.");
    }
    
    std::ifstream file(argv[1]); // Open file using the filename from argv[1]
    if (!file) {
        std::cerr << "Error: Could not open file '" << argv[1] << "'." << std::endl;
        throw std::invalid_argument("Invalid filename.");
    }
    
    // Convert file contents to a string
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void write_output(std::string output, std::string filename)
{
    std::ofstream file(filename); // Open the file for writing
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing." << std::endl;
        return;
        
    }
    
    file << output; // Write the output string to the file

    // Optionally, check if writing was successful
    if (file.fail()) {
        std::cerr << "Error: Failed to write to file '" << filename << "'." << std::endl;
        throw std::runtime_error("Failed to write to file.");
    }
    
    // The file will be closed automatically when it goes out of scope.
}