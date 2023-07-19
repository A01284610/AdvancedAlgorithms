/*
 * Fecha: 10 Abril 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 3.3 - Implementacion de "Knapsack problem"
 *    En el programa se hace uso de un vector de vectores para almacenar los pesos entre nodos. CAMBIAR
 *    Para buscar las distancias minimas entre nodos, se hace uso de dos tecnicas: "Dijkstra" y "Floyd-Warshall" CAMBIAR
 *
 * Para compilar: 
 * g++ -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;
using std::max;

struct obj{
    int valor, peso;
};

int mochDP(vector<obj> &datos, int PESO){
    int N = datos.size();
    int mat[N+1][PESO+1];
    for (int i=0; i<=N; i++){
        mat[i][0] = 0;
    }
    for (int j=0; j<=PESO; j++){
        mat[0][j] = 0;
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=PESO; j++){
            if (datos[i-1].peso > j){
                mat[i][j] = mat[i-1][j];
            }
            else{
                mat[i][j] = max(mat[i-1][j], datos[i-1].valor + mat[i-1][j-datos[i-1].peso]);
            }
        }
    }
    return mat[N][PESO];
}


int main(){

    int N, PESO;
    int valorTemp;
    int pesoTemp;

    cin >> N;

    vector<obj> datos(N);

    for (int i=0; i<N; i++){
        cin >> valorTemp;
        datos[i].valor = valorTemp;
    }

    for (int i=0; i<N; i++){
        cin >> pesoTemp;
        datos[i].peso = pesoTemp;
    }

    cin >> PESO;

    cout << mochDP(datos, PESO) << endl;

    return 0;
}