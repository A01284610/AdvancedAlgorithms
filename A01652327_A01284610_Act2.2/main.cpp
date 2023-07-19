/*
 * Fecha: 13 Marzo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 2.2 - Implementación de "Sufix Array"
 *    Al programa se le da un archivo con un string, se calcula el arreglo de substrings y lo muestra ordenado alfabeticamente.
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

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::transform;


/*
 * Método SuffixArrayNaive:
 * Descripción: Obtiene el arreglo de substrings dado un string o lo muestra ordenado alfabeticamente.
 * Entrada: string 'S' con el string a utilizar.
 * Salida: Se imprime todos los valores de los substrings, asi como su respectivo substring ordenados alfabeticamente.
 * Precondición: Se recibe un string 'S'.
 * Postcondición: Se imprime todos los valores de los substrings, asi como su respectivo substring ordenados alfabeticamente.
 * Complejidad: O(n^2 log(n)) -> n = longitud del string 'S'
*/
void suffixArrayNaive(string S){

    // Se obtiene y almacena la longitud del string 'S'.
    int n = S.length();

    // Se genera un vector de pares<int, string> de tamaño 'n' para almacenar en cada par el valor del substring y el substring.
    vector<pair<int, string> > res(n);

    // Se genera un vector auxiliar para los substrings.
    vector<string> sa;

    // Se transforma a minusculas la palabra para poder realizar las comparaciones y tener un orden alfabetico adecuado.
    transform(S.begin(), S.end(), S.begin(), ::tolower);

    S = S+"$";

    // Se obtiene todos los substrings y almacenan en el vector 'sa'.
    for (int i=0; i<n; i++){
        sa.push_back(S.substr(n-i-1, i+1));
    }

    // Se ordena alfabeticamente el vector 'sa' que cuenta con los substrings.
    sort(sa.begin(), sa.end());

    // Se llena el vector 'res' donde cada par es el valor del substring y el respectivo substring (ya se encuentra ordenado alfabeticamente).
    for (int i=0; i<n; i++){
        // Se almacena el valor del substring.
        res[i].first = n-sa[i].size() + 1;
        // Se almacena el substring.
        res[i].second = sa[i];
        // Se imprime cada par.
        cout << res[i].first << " " << res[i].second << endl;
    }
}

// Inicio del main().
int main(){

    // Se obtiene el input.
    std::istream& in = cin;

    // Variable string 'S' para almacenar la palabra a utilizar.
    string palabra;
    // Se recibe la palabra.
    cin >> palabra;

    // Se obtienen los substrings de la palabra y muestran ordenados alfabeticamente.
    suffixArrayNaive(palabra);

    return 0;
}