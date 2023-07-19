/*
 * Fecha: 01 Junio 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 5.1 - Implementacion backtracking con Bitmask
 *    Se recibe un valor 'target' a buscar, un valor 'n' y 'n' valores en orden ascendente para implementar una Randomized Binary Search. CAMBIAR
 *    En caso de encontrar el 'target' se devuelve su posicion; en caso de que no se encuentre se devuelve un -1. CAMBIAR
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

using std::vector;
using std::cin;
using std::cout;
using std::endl;

typedef unsigned long long uchar;

// Variable global para almacenar el numero de soluciones viables.
int counter = 0;

/* CAMBIAR
 * Metodo nextToTop:
 * Descripcion: Encuentra el siguiente elemento al top de un stack.
 * Entrada: Stack<Point> 'S'.
 * Salida: Devuelve un 'Point' que representa el siguiente elemento al top de un stack.
 * Precondicion: Se debe de recibir un stack<Point> con al menos dos elementos 'Point'.
 * Postcondicion: Se debe devolver un 'Point' que representa el siguiente elemento al top de un stack.
 * Complejidad: O(1)
*/
uchar add(uchar mask, int pos) {
    return (mask | (1 << pos));
}

/* CAMBIAR
 * Metodo nextToTop:
 * Descripcion: Encuentra el siguiente elemento al top de un stack.
 * Entrada: Stack<Point> 'S'.
 * Salida: Devuelve un 'Point' que representa el siguiente elemento al top de un stack.
 * Precondicion: Se debe de recibir un stack<Point> con al menos dos elementos 'Point'.
 * Postcondicion: Se debe devolver un 'Point' que representa el siguiente elemento al top de un stack.
 * Complejidad: O(1)
*/
bool test(uchar mask, int pos) {
    return ((mask & (1 << pos)) != 0);
}

/* CAMBIAR
 * Metodo nextToTop:
 * Descripcion: Encuentra el siguiente elemento al top de un stack.
 * Entrada: Stack<Point> 'S'.
 * Salida: Devuelve un 'Point' que representa el siguiente elemento al top de un stack.
 * Precondicion: Se debe de recibir un stack<Point> con al menos dos elementos 'Point'.
 * Postcondicion: Se debe devolver un 'Point' que representa el siguiente elemento al top de un stack.
 * Complejidad: O(1)
*/
void printArrangement(const vector<vector<int> > &results) {
    for (int i = 0; i < results.size(); i++){
        for (int j = 0; j < results[i].size(); j++){
            cout << results[i][j] << " ";
        }
        cout << endl;
    }
}

/* CAMBIAR
 * Metodo nextToTop:
 * Descripcion: Encuentra el siguiente elemento al top de un stack.
 * Entrada: Stack<Point> 'S'.
 * Salida: Devuelve un 'Point' que representa el siguiente elemento al top de un stack.
 * Precondicion: Se debe de recibir un stack<Point> con al menos dos elementos 'Point'.
 * Postcondicion: Se debe devolver un 'Point' que representa el siguiente elemento al top de un stack.
 * Complejidad: O(1)
*/
void backtracking(const vector<vector<int> > &caps, vector<int> &arrangement, uchar mask, int person, int &count, vector<vector<int> >& results) {
    if (person == caps.size()) {
        count++;
        results.push_back(arrangement);
        return;
    }

    for (int i = 0; i < caps[person].size(); i++) {
        int cap = caps[person][i];
        if (!test(mask, cap - 1)) {
            arrangement[person] = cap;
            backtracking(caps, arrangement, add(mask, cap - 1), person + 1, count, results);
        }
    }
}

// Inicio del main.
int main() {

    // Variable int 'n' para almacenar el numero personas (Restringido a 1 <= n <= 10).
    int n;
    // Se recibe el numero de personas.
    cin >> n;

    // Se inicializa un vector<vector<int>> 'caps' de tamaño 'n' para almacenar en cada vector<int> los id's de las gorras de cada persona.
    vector<vector<int> > caps(n);
    // Se reciben los id's de las gorras de cada persona y se almacenan en 'caps'.
    for (int i = 0; i < n; i++) {
        // Variable int 'm' para almacenar los id's de las gorras de cada persona.
        int m;
        // Se recibe el numero de gorras de cada persona.
        cin >> m;
        caps[i].resize(m);
        // Se recibe y almacena cada uno de los id's de las gorras de cada persona.
        for (int j = 0; j < m; j++) {
            cin >> caps[i][j];
        }
    }

    // Se genera un vector<int> 'arrangement' de tamaño 'n' donde se almacenara cada una de 
    vector<int> arrangement(n);
    vector<vector<int> > results;
    uchar mask = 0;
    int count = 0;

    backtracking(caps, arrangement, mask, 0, count, results);
    cout << count << endl;
    printArrangement(results);

    return 0;
}