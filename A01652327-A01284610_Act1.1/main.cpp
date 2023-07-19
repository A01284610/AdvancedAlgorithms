/*
 * Fecha: 20 Feb 2023
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

// Inicializar el vector de doubles 'vect'.
vector<double> vect;


/*
 * Método merge:
 * Descripción: Fusiona los elementos de dos arreglos con un orden ascendente.
 * Entrada: Vector <double> 'vect' pasado por referencia con los n valores; Entero 'low' que es el límite izquierdo del vector; 
 *          Entero 'm' que es el punto medio del vector; Entero 'high' que es el límite derecho del vector;
 * Salida: Nada
 * Precondición: El vector <double> debe de contener los n valores.
 * Postcondición: El vector <double> con los subarreglos fusionados y con sus valores ordenados de forma ascendente.
 * Complejidad: O(n)
*/

void merge(vector<double>& vect, int low, int m, int high) {
  /*
   * Inicializar las variables a utilizar:
   *   Entero 'i' para el índice del primer subarreglo.
   *   Entero 'j' para el índice del segundo subarreglo.
   *   Entero 'k' para el índice del vector.
   *   Entero 'n1' para el tamaño del primer subarreglo.
   *   Entero 'n2' para el tamaño del segundo subarreglo.
  */
  int i, j, k = 0;
  int n1 = m - low + 1;
  int n2 = high - m;
  // Crear los vectores que almacenarán los elementos de los subarreglos.
  vector<double> L(n1), R(n2);
  // Copiar los elementos a cada uno de los subarreglos.
  for (i = 0; i < n1; i++)  L[i] = vect[low + i];
  for (j = 0; j < n2; j++)  R[j] = vect[m + 1 + j];
  // Se fusionan los subarreglos.
  i = j = 0;
  k = low;
  while (i < n1 && j < n2) {
    // Se revisa si el elemento del primer subarreglo en la posición 'i' es menor o igual al elemento del segundo subarreglo en la posición 'j'.
    if (L[i]<=R[j]){
      // Se almacena el elemento del primer subarreglo en la posición 'i' en el vector 'vect' en la posición 'k'
      vect[k] = L[i];
      i = i + 1;
    }
    else {
      // Se almacena el elemento del segundo subarreglo en la posición 'j' en el vector 'vect' en la posición 'k'
      vect[k] = R[j];
      j = j + 1;
    }
    k = k + 1;
  }
  // Se copian los elementos restantes del primer subarreglo al vector.
  while (i < n1) {
    // Se almacena el elemento del primer subarreglo en la posición 'i' en el vector 'vect' en la posición 'k'
    vect[k] = L[i];
    i = i + 1;
    k = k + 1;
  }
  // Se copian los elementos restantes del segundo subarreglo al vector.
  while (j < n2) {
    // Se almacena el elemento del segundo subarreglo en la posición 'j' en el vector 'vect' en la posición 'k'
    vect[k] = R[j];
    j = j + 1;
    k = k + 1;
  }
}

/*
 * Método ordenaMerge:
 * Descripción: Ordena de forma ascendente los datos por el método de ordenamiento por fusión (merge).
 * Entrada: Vector <double> 'vect' pasado por referencia con los n valores; Entero 'low' que es el límite izquierdo del vector; Entero 'high' que es el límite derecho del vector; 
 * Salida: Nada
 * Precondición: El vector <double> debe de contener los n valores.
 * Postcondición: El vector <double> debe de contener los n valores ordenados de forma ascendente.
 * Complejidad: O(n log(n))
*/

void ordenaMerge(vector<double>& vect, int low, int high) {
  // Se revisa si el límite izquierdo es menor al límite derecho.
  if (low < high) {
    // Se encuentra el punto medio del vector y se almacena en el entero 'm'.
    int m = low + (high - low)/2;
    // Se ordenan las dos mitades del vector con el método 'ordenaMerge'.
    ordenaMerge(vect, low, m);
    ordenaMerge(vect, m+1, high);
    // Se fusionan ambas mitades con el método 'merge'.
    merge(vect, low, m, high);
  }
}


// Inicio del main().
int main(){

  std::istream& in = cin;
  std::string s;
  getline(in, s);

  // Se obtiene el numero de elementos y se almacena en el entero 'size':
  int size = stoi(s);

  // Inicializar el vector de enteros <double> 'vect' de tamaño 'size'.
  vector<double> vect(size);
  
  // Se recibe cada elemento que pertenece al arreglo a ordenar y se almacena en el vector 'vect'.
  for(int i = 0; i < size; i++) {
    cin >> vect[i];
  }

  // Se implementa el método de ordenamiento 'ordenaMerge' para ordenar los elementos del vector.
  ordenaMerge(vect, 0, size-1);

  // Se imprime cada uno de los elementos del arreglo ya ordenado.
  cout << "Los elementos del arreglo ordenados son: " << endl;
  for(int i = 0; i < size; i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
  

  return 0;

}