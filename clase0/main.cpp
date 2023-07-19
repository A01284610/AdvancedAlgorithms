#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

int main(){

    istream& in = cin;
    string s;
    getline(in, s);
    int number = stoi(s);

    while (in >> number){
        cout << (number) << endl;
    }


    return 0;
}