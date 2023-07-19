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

static bool takenSeats[5][8];

void fillSeats(const string& str){
  for (int i = 0; i < str.length(); i = i + 2){
    //char to int
    int row = int(str[i]) - 'A';
    int col = int(str[i+1]) - '1';

    // cout << str[i] << "is" << row << " , " << str[i+1] << "is" << col << endl;

    takenSeats[row][col] = true;
  }
}

int calculateSeats(){
    int count = 0;
    int maxCount = 0;
    for (int i = 0; i <= 4; i++){
        for (int j = 0; j <= 8; j++){
            if (takenSeats[i][j]){ 
                count = 0;
            } else {
                count++;
                if (count > maxCount){
                    maxCount = count;
                }
            }
            cout << " " << maxCount << "||" << takenSeats[i][j] << "|" << count;
        }
    cout << endl;
    count = 0;
  }
  return maxCount;
}

int main() {
  string a = "A5B5C5D5E5";
    fillSeats(a);
    cout << calculateSeats();
  return 0;
}
