/*
 * Para compilar: 
 * g++ -std=c++17 -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

// string vectorToWords(queue<pair<int,int>> &myQ){
//     string result = "";
//     while (!myQ.empty()){
//         result += to_string(myQ.front().second);
//         result += to_string(myQ.front().first);
        
//         myQ.pop();
//     }
//     return result;
// }

// queue<pair<int,int>> vectorProcess(queue<pair<int,int>> &myQ){
//     queue<pair<int,int>> result;
//     result.push(make_pair(myQ.front().first,1));
//     cout << myQ.front().first << ";" << myQ.front().second << endl; 
    
//     while (!myQ.empty()){
//         cout << "myQ has: " << myQ.front().first << "," << myQ.front().second << endl;
//         cout << "result has: " << result.front().first << "," << result.front().second << endl;
//         if (myQ.front().first == result.front().first){
//             result.front().second = result.front().second + 1;
//             cout << result.front().first << ",," << result.front().second << endl;

//         } else {
//             cout << myQ.front().first << "," << 1<< endl;
//             result.push(make_pair(myQ.front().first,1));
//         }
//         myQ.pop();
//     }

//     return result;
// }

string process (string &str){
    string result = "";
    char toCompare = str[0];
    int count = 0;

    for (int i = 0; i < str.length(); i++){

        if (str[i] == toCompare){
            count++;
        } else {
            result += to_string(count);
            result += toCompare;
            toCompare = str[i];
            count = 1;
        }
    }
    result += to_string(count);
    result += toCompare;
    return result;
}

int main(){
    int n = 6;
    // queue<pair<int,int>> base;
    // base.push(make_pair(1,1));
    string base = "1";

    for (int i = 0; i < n-1; i++){
        base = process(base);
    }

    cout << base;
    return 0;

}