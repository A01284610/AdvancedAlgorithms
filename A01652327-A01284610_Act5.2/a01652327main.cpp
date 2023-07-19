/*
 * Fecha: 08 Junio 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 5.2 - Implementacion encontrarse en el medio (meet in the middle).
 *    Se reciben 'n' enteros con un valor y una suma objetivo. Se busca obtener el numero de subconjuntos cuya suma de todos los elementos sea igual a la suma objetivo.
 *    Donde n <= 50 ; valor <= 10^12.
 *    Se imprime el numero total de combinaciones cuya suma es igual a la suma objetivo.
 *
 * Para compilar: 
 * g++ -o a.out a01652327main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::lower_bound;
using std::upper_bound;
using std::distance;

// Tipo de dato para los valores numericos.
typedef long long ll;

/* CAMBIAR
 * Metodo backtrack:
 * Descripcion: Obtiene las sumas de todos los subconjuntos que se pueden formar con los elementos un conjunto.
 * Entrada: vector<ll> 'nums' que es el arreglo con los numeros con los que se formaran los subconjuntos ; int 'index' que es el indice del elemento de 'nums' a considerar ; 
 *          ll 'sum' que es la suma del subconjunto ; vector<ll> 'sums' que es el vector donde se almacenan las sumas de los subconjuntos.
 * Salida: Ninguna.
 * Precondicion: Se debe de contar con un arreglo de numeros valido, un indice valido (0 <= indice < n), un valor de 'sum' valido y un vector de sumas valido.
 * Postcondicion: Se han obtenido todas las sumas de los subconjuntos y se almacenan en el vector 'sums'.
 * Complejidad: O(2^n) ; n = numero de elementos del arreglo.
*/
void backtrack(vector<ll>& nums, int index, ll sum, vector<ll>& sums) {

    // En caso de que ya se hayan revisado todos los elementos del arreglo.
    if (index == nums.size()) {
        // Se agrega la suma del subconjunto al vector 'sums'.
        sums.push_back(sum);
        return;
    }
    
    // Se realiza la llamada al siguiente elemento incluyendo el valor del indice actual en la suma y subarreglo.
    backtrack(nums, index + 1, sum + nums[index], sums);
    // Se realiza la llamada al siguiente elemento sin incluir el valor del indice actual en la suma o subarreglo.
    backtrack(nums, index + 1, sum, sums);
}

/* 
 * Metodo meetInTheMiddle:
 * Descripcion: Divide el espacio de busqueda en dos partes aproximadamente del mismo tamaño, realiza los subconjuntos y sus sumas por separado y luego combina los resultados.
 * Entrada: vector<ll> 'nums' que es el arreglo con los numeros con los que se formaran los subconjuntos ; ll 'sumaObjetivo' que es la suma del subconjunto que se busca encontrar.
 * Salida: Devuelve el numero de subconjuntos cuya suma es igual a la suma objetivo.
 * Precondicion: Se debe de contar con un vector 'nums' valido y un valor de 'sumaObjetivo' valida.
 * Postcondicion: Se devuelve el numero de subconjuntos cuya suma es igual a la suma objetivo.
 * Complejidad: O(n 2^(n/2)) ; n = numero de elementos del arreglo.
*/
int meetInTheMiddle(vector<ll>& nums, ll sumaObjetivo) {

    // Se obtiene el numero de elementos del arreglo.
    int n = nums.size();

    // Se dividen los elementos en dos suarreglos de tamaño n/2.
    vector<ll> mitadIzq(nums.begin(), nums.begin() + n/2);
    vector<ll> mitadDer(nums.begin() + n/2, nums.end());

    // Se generan dos vectores donde se almacenaran las sumas de cada uno de los subconjuntos de ambos subarreglos de tamaño n/2.
    vector<ll> sums1, sums2;

    // Se obtienen todos los subconjuntos de cada subarreglo y se calcula la suma de cada uno de los subconjuntos. 
    backtrack(mitadIzq, 0, 0, sums1);
    backtrack(mitadDer, 0, 0, sums2);

    // Se ordenan de forma ascendente las sumas de los subconjuntos de la segunda mitad.
    sort(sums2.begin(), sums2.end());

    // Variable int 'count' para almacenar la cantidad de subconjuntos cuya suma sea igual a la objetivo.
    int count = 0;

    // Se revisa por cada uno de los subarreglos izquierdos, si se complementa con los del lado derecho.
    for (int i = 0; i < sums1.size(); i++) {

        // Se calcula el complemento o diferencia entre la suma del subarreglo con el valor objetivo.
        ll complement = sumaObjetivo - sums1[i];
        
        // Se realiza una busqueda binaria para encontrar el borde izquierdo del complemento en las sumas de los subconjuntos del subarreglo derecho.
        auto left = lower_bound(sums2.begin(), sums2.end(), complement);
        
        // Se realiza una busqueda binaria para encontrar el borde derecho del complemento en las sumas de los subconjuntos del subarreglo derecho.
        auto right = upper_bound(sums2.begin(), sums2.end(), complement);
        
        // Se obtiene la cantidad de subconjuntos que pueden complementar al subconjunto de la izquierda y se suman al contador.
        cout <<"Antes:   " << "Sums1: "<<sums1[i] << " Complement: " << complement << " Distance: " << distance(left, right) << " count: " << count << endl;
        count += distance(left, right);
        cout <<"Despues:   " << "Sums1: "<<sums1[i] << " Complement: " << complement << " Distance: " << distance(left, right) << " count: " << count << endl;
        cout << endl;
    }
    
    return count;
}

// Inicio del main().
int main() {
    // Variable int 'n' para almacenar el numero de enteros (Restringido a n <= 50).
    int n;
    // Se recibe el numero de enteros.
    cin >> n;
    
    // Se inicializa un vector<long long> 'nums' de tamaño 'n' para almacenar los enteros.
    vector<ll> nums(n);
    // Se reciben los enteros.
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // Variable long long 'S' que almacenara el valor de la suma a buscar.
    ll sumaObjetivo;
    // Se recibe el valor de la suma a buscar.
    cin >> sumaObjetivo;
    
    // Se obtiene el numero de subconjuntos cuya suma es el valor buscado.
    int result = meetInTheMiddle(nums, sumaObjetivo);
    // Se imprime el resultado.
    cout << result << endl;
    
    return 0;
}