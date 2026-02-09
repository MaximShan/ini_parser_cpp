#include <iostream>
#include "head.h"

int main() {
    try {
        ini_parser parser("filename.ini");

        //std::cout << parser.get_value<int>("Section1.var99") << "\n";
       std::cout << parser.get_value<int>("Section1.var1") << "\n";
       // std::cout << parser.get_value<int>("Section4.var1") << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}