/*
 * Para compilar: 
 * g++ -std=c++17 -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out
 * 
 * g++ -Wall -std=c++17 main.cpp -o a.out
 * 
 * g++ -Wall main.cpp -o a.out
*/


#include <iostream>
#include <cmath>
#include <string>
#include <vector>

std::string bruteForceCaesar(const std::string& input) {
    std::string result;
    
    for (int key = 0; key < 26; ++key) {
        result = ""; // Reset result for each key
        
        for (char c : input) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                char encrypted = (c - base + key) % 26 + base;
                result += encrypted;
            } else {
                result += c;
            }
        }
        
        std::cout << "Key " << key << ": " << result << std::endl;
    }
    
    return result;
}

int main() {
    std::string input;
    std::cout << "Enter the string to bruteforce: ";
    std::getline(std::cin, input);
    
    bruteForceCaesar(input);
    
    return 0;
}
