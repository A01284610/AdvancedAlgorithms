/*
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Para compilar: 
 * g++ -o a.out main.cpp
 * 
 * g++ -std=c++17 -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
 * 
 * ./a.out
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, int> set;

string traverseString(string& str){
    int largestCurrent = 9;
    string result = "";


    for (int i = 0; i < str.length(); i++){
        char currentChar = str[i];
        cout << currentChar << " ";

        if (set.find(currentChar) != set.end()){
            cout << "it is in" << endl;
            result += to_string(set[currentChar]);
        } else {
                        set[currentChar] = largestCurrent;

                        cout << "it is NOT in" << endl;

            result += to_string(largestCurrent);
            largestCurrent++;
        }
    }

    return result;
}

int main() {
  string a = "BABBC";
  cout << traverseString(a);
  return 0;
}
