/*
 * Para compilar: 
 * g++ -std=c++17 -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
 * 
*/

#include <iostream>
#include <cmath>
#include <vector>

typedef unsigned char uchar;
typedef unsigned long long int lchar;


uchar add(uchar mask, int pos){
    return (mask | (1 << pos));
}

uchar test(uchar mask, int pos){
    return ((mask & (1 << pos)) != 0);
}

void imprimeConjunto(std::vector<int> &S, unsigned long long int mask[2]){
    std::cout << "{";
    for (int i = 0; i < S.size(); i++){
        if (test(mask[i / 64], i % 64)){
            std::cout << S[i] << " ";
        }
    }
    std::cout << "}\n";
}


void posiblesGorras(std::vector<std::vector<int>> &vect, unsigned long long int set[2], std::vector<unsigned long long int> result, std::vector<int> path, int index, int &count){
    if((set[1])==((1<<(vect.size()%64)) -1)){
        count++;
        result[index] = *set;
        return;
    }

    // if (index == 100){
    //     return;
    // }


    // posiblesGorras(vect, set, result,path, index + 1, count);

    for (int i = 0; i < vect[index].size(); i++){
        int cap = vect[index][i];
        if (!test(set[index/64],cap-1)){
            
            unsigned long long int temp_set[2] = {set[0], set[1]};
            temp_set[index / 64] = add(temp_set[index / 64], index - 1);
            path[i] = cap;
            posiblesGorras(vect,temp_set,result,path,index+1,count);
        }
    }

    // for (auto person : vect[index]){
    //     // first check if this person is not allocated any other hat
    //     if (!test(set[index / 64], person - 1)){
    //         // allocate the ith cap to this person
    //         unsigned long long int temp_set[2] = {set[0], set[1]};
    //         temp_set[index / 64] = add(temp_set[index / 64], person - 1);
    //         path[index] = person;
    //         posiblesGorras(vect, temp_set, result, path, index + 1, count);
    //     }
    // }
    return;
}

int main (){
    int n = 0;
    int m = 0;
    int data = 0;
    std::cin >> n;

    std::vector<std::vector<int>> vect(n);
    std::vector<unsigned long long int> result(n);
    std::vector<int> path(n);
    int count = 0;


    for (int i = 0; i < n; i++){
        std::cin >> m;
        for (int j = 0; j < m; j++){
            std::cin >> data;
            vect[i].push_back(data);
        }
    }

    unsigned long long int set[2] = {0, 0};



    posiblesGorras(vect, set, result, path, 0, count);

    // Printing the resulting combinations
    // for (auto res : result) {
    //     imprimeConjunto(vect, set);
    // }

    return 0;
}
