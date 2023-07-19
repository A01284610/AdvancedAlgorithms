/*
 * Fecha: 21 Feb 2023
 * Autores:
 *   Matrícula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matrícula: A01284610
 *   Nombre: Alejandro Lizárraga Vizcarra
 *
 * Actividad 1.1 - Implementación de la técnica de programación "divide y vencerás"
 *    En el programa se hace uso de un vector para almacenar los datos pertenecientes al arreglo.
 *      Algoritmo de ordenamiento implementado: Ordenamiento por fusión (merge sort).
 *
 * Para compilar: 
 * g++ -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < TestCases/test01.txt
*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


int minCambioPD(vector<int>& denoms, int n, int cambio){
  
  // Crear tabla para programacion dinamica de columnas cambio+1 y filas n (denominaciones)
  int tabla[n][cambio+1];
  bool tablaBool[n][cambio+1];


  // Igualar la primera fila de denoninador 1 a su posicion en columna
  for (int i = 0; i < cambio+1; i++){
    tabla[0][i] = i;
  }

  //llenar la tabla de datos
  for (int i = 1; i < n; i++){
    for (int j = 0; j < cambio+1; j++){
      // Si la cantidad monetaria es menor que la denominacion se agarra el valor de arriba
      if (j < denoms[i]){
        tabla[i][j] = tabla[i-1][j];
        tablaBool[i][j] = true;
        //Si el valor de arriba es menor que el valor de la izquierda
      } else if (tabla[i-1][j] < tabla[i][j-denoms[i]]){
        //Se iguala al valor de arriba
        tabla[i][j] = tabla[i-1][j];
        tablaBool[i][j] = true;
      } else {
        //Si no se iguala al valor de la izquierda +1
        tabla[i][j] = tabla[i][j-denoms[i]] + 1;
        tablaBool[i][j] = false;
      }
    }
  }

  //Conseguir informacion de la tabla generada

  //vector de resultados
  vector<int> vect(n);

  //conseguir el punto inicial de la tabla donde se ocupan las minimas monedas para el cambio total
  int minCoinsIndex = 0;


  for (int i = 0; i < n; i++){
    if (tabla[i][cambio] < tabla[minCoinsIndex][cambio]){
      minCoinsIndex = i;
    }
  }

  //recorrer tabla pd
  int currentCambio = 0;
  int index1 = minCoinsIndex;
  int index2 = cambio;
  while(currentCambio < cambio){

    // Si en la posicion que se checa tablaBool == true, entonces el valor es de arriba y se debe revisar esa celda
    if (tablaBool[index1][index2]){
      index1 = index1 - 1;
    } else {
      //Si tablaBool == false, entonces el valor se checa a la izquierda

      //agregar 1 moneda de denominacion de la fila en la que estemos
      vect[index1]++;
      currentCambio += denoms[index1];
      //agregamos una unidad de esa moneda y nos recorremos a la izquierda por la magnitud de la denominacion
      index2 = index2 - denoms[index1];
    }
  }
  
  for (int i = n-1; i > -1; i--){
    cout << denoms[i] << ": " << vect[i] << endl;
  }

  return tabla[minCoinsIndex][cambio];
}

int minCambioAvaro(vector<int>& denoms, int n, int cambio){

  //vector de resultados
  vector<int> vect(n);

  int coins = 0;
  int currentCambio = 0;

  for (int i = n-1; i > -1; i--){
    while(denoms[i] <= (cambio-currentCambio)){
      vect[i]++;
      coins++;
      currentCambio+=denoms[i];
    }
  }

  for (int i = n-1; i > -1; i--){
    cout << denoms[i] << ": " << vect[i] << endl;
  }

  return coins;

}

// Inicio del main().
int main(){

  std::istream& in = cin;
  int valorN = 0;
  int valorP = 0;
  int valorQ = 0;
  
  // Se recibe la cantidad de denominaciones
  cin >> valorN;

  // Inicializar el vector de enteros <double> 'vect' de tamaño 'N' (diferentes denominaciones disponibles).
  vector<int> vect(valorN);
  
  // Se recibe cada elemento que pertenece al arreglo a ordenar y se almacena en el vector 'vect'.
  for(int i = 0; i < valorN; i++) {
    cin >> vect[i];
  }

  // Se recibe el precio de lo que se compró
  cin >> valorP;
  // Se recibe la cantidad que se pagó
  cin >> valorQ;

  // Se calcula el cambio que se tiene que dar al restar el pago - precio.
  int cambioMonetario = valorQ - valorP;


  cout << "DP:" << endl;
  minCambioPD(vect, valorN, cambioMonetario);

  cout << "Avaro:" << endl;
  minCambioAvaro(vect, valorN, cambioMonetario);

  return 0;
}