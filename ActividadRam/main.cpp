/*
 * Fecha: 2 Marzo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 1.3 - Implementacion de la tecnica de programacion "backtracking" y "ramificacion y poda"
 *    En el programa se hace uso de un vector de vectores para almacenar el laberinto.
 *      Para buscar el camino desde el origen (0, 0) hasta la meta (M-1, N-1), se hace uso de dos tecnicas: "BackTracking" (stack) y "Ramificacion y Poda" (queue).
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
#include <stack>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::string;
using std::stack;
using std::queue;
using std::pair;
using std::make_pair;


/*
 * Método BackTracking:
 * Descripción: Obtiene la solucion del problema haciendo uso del metodo "BackTracking" con apoyo de un Stack. Imprime el camino a seguir para salir del laberinto.
 * Entrada: Vector < Vector <int> > 'vect' (tamaño MxN) con la estructura del laberinto.
 * Salida: Se imprime una matriz con el camino a seguir indicado por '1'.
 * Precondición: El vector 'vect' debe de contener los MxN valores del laberinto, asi como minimo una solución.
 * Postcondición: Se imprime la matriz del resultado del camino obtenido con el algoritmo.
 * Complejidad: O(4^(M*N)) -> M = Alto del laberinto  ;  N = Ancho del laberinto
*/
void BackTracking(vector<vector<int> > vect){

    // Se obtienen los valores de M y N.
    int size_M = vect.size();
    int size_N = vect[0].size();

    // Se genera el arreglo de coordenadas Padre.
    vector<vector<pair<int,int> > > Padre(size_M);

    // Dimensiones Arreglo Padre.
    for (int i = 0; i < size_M ; i++){
        Padre[i].resize(size_N);
    }

    // Se genera el stack.
    stack<pair<int,int> > stack;

    // Se inserta el primer elemento (0,0) al stack (Celda superior izquierda).
    stack.push(make_pair(0,0));
    // Equivale a None para el padre en (0,0).
    Padre[0][0] = make_pair(-1,-1);

    // Bandera para saber que ya se alcanzo la casilla (M-1, N-1).
    bool flag = 1;

    // Comienza a revisar siempre y cuando el stack no este vacio y no se haya alcanzado la meta.
    while(!stack.empty() && flag == 1){

        // Se obtiene el top del stack y asigna a celdaActual. 
        pair<int,int> celdaActual = stack.top();

        // Se elimina del stack el elemento guardado en celdaActual.
        stack.pop();

        // Se revisa si la celdaActual es la celda meta (M-1, N-1).
        if (celdaActual.first == size_M - 1 && celdaActual.second == size_N - 1){
            flag = 0;
            cout << "La ruta de salida es:" << endl;

            // Se genera una matriz (MxN) con '0' para señalar el camino.
            vector<vector<int> > vect_salida(size_M);
            for (int i = 0; i < size_M ; i++){
                vect_salida[i].resize(size_N, 0);
            }

            // Mientras la celda sea distinta al origen, se siguen revisando los padres.
            while (celdaActual.first > -1){
                // Se cambia a '1' en las celdas que son parte de la solucion.
                vect_salida[celdaActual.first][celdaActual.second] = 1;
                // Se busca al padre de la celda actual.
                celdaActual = Padre[celdaActual.first][celdaActual.second];
            }

            // Se imprime el arreglo (MxN) con el camino de la solucion.
            for (int i = 0; i < size_M ; i++){
                for (int j = 0; j < size_N ; j++){
                    cout << vect_salida[i][j] << " ";   
                }
                cout << endl;
            }
        }

        // Si la celdaActual no es la celda meta (M-1, N-1).
        else {

            // Se hace '0' el valor de la celdaActual.
            vect[celdaActual.first][celdaActual.second] = 0;

            // Hacer un push al stack de cada celda adyacente valida con valor 1 y poner como padres de ellas a celdaActual:

            // Abajo.
            if (celdaActual.first + 1 < size_M){
                if (vect[celdaActual.first + 1][celdaActual.second] == 1){
                    stack.push(make_pair(celdaActual.first + 1, celdaActual.second));
                    Padre[celdaActual.first + 1][celdaActual.second] = make_pair(celdaActual.first, celdaActual.second);
                }
            }

            // Derecha.
            if (celdaActual.second + 1 < size_N){
                if (vect[celdaActual.first][celdaActual.second + 1] == 1){
                    stack.push(make_pair(celdaActual.first, celdaActual.second + 1));
                    Padre[celdaActual.first][celdaActual.second + 1] = make_pair(celdaActual.first, celdaActual.second);
                }
            }

            // Arriba.
            if (celdaActual.first - 1 >= 0){
                if (vect[celdaActual.first - 1][celdaActual.second] == 1){
                    stack.push(make_pair(celdaActual.first - 1, celdaActual.second));
                    Padre[celdaActual.first - 1][celdaActual.second] = make_pair(celdaActual.first, celdaActual.second);
                }
            }
            
            // Izquierda.
            if (celdaActual.second - 1 >= 0){
                if (vect[celdaActual.first][celdaActual.second - 1] == 1){
                    stack.push(make_pair(celdaActual.first, celdaActual.second - 1));
                    Padre[celdaActual.first][celdaActual.second - 1] = make_pair(celdaActual.first, celdaActual.second);
                }
            }
        }
    }
}


/*
 * Método RamificacionPoda:
 * Descripción: Obtiene la solucion del problema haciendo uso del metodo "Ramificacion y Poda" con apoyo de un Queue. Imprime el camino a seguir para salir del laberinto.
 * Entrada: Vector < Vector <int> > 'vect' (tamaño MxN) con la estructura del laberinto.
 * Salida: Se imprime una matriz con el camino a seguir indicado por '1'.
 * Precondición: El vector 'vect' debe de contener los MxN valores del laberinto, asi como minimo una solución.
 * Postcondición: Se imprime la matriz del resultado del camino obtenido con el algoritmo.
 * Complejidad: O(4^(M*N)) -> M = Alto del laberinto  ;  N = Ancho del laberinto
*/
void RamificacionPoda(vector<vector<int> > vect){
    
    // Se obtienen los valores de M y N.
    int size_M = vect.size();
    int size_N = vect[0].size();

    // Se genera el arreglo de coordenadas Padre.
    vector<vector<pair<int,int> > > Padre(size_M);

    // Dimensiones Arreglo Padre.
    for (int i = 0; i < size_M ; i++){
        Padre[i].resize(size_N);
    }

    // Se genera el queue.
    queue<pair<int,int> > queue;

    // Se inserta el primer elemento (0,0) al queue (Celda superior izquierda).
    queue.push(make_pair(0,0));
    // Equivale a None para el padre en (0,0).
    Padre[0][0] = make_pair(-1,-1);

    // Bandera para saber que ya se alcanzo la casilla (M-1, N-1).
    bool flag = 1;

    // Comienza a revisar siempre y cuando el queue no este vacio y no se haya alcanzado la meta.
    while(!queue.empty() && flag == 1){

        // Se obtiene el front del queue y asigna a celdaActual. 
        pair<int,int> celdaActual = queue.front();

        // Se elimina del queue el elemento guardado en celdaActual.
        queue.pop();

        // Se revisa si la celdaActual es la celda meta (M-1, N-1).
        if (celdaActual.first == size_M - 1 && celdaActual.second == size_N - 1){
            flag = 0;
            cout << "La ruta de salida es:" << endl;

            // Se genera una matriz (MxN) con '0' para señalar el camino.
            vector<vector<int> > vect_salida(size_M);
            for (int i = 0; i < size_M ; i++){
                vect_salida[i].resize(size_N, 0);
            }

            // Mientras la celda sea distinta al origen, se siguen revisando los padres.
            while (celdaActual.first > -1){
                // Se cambia a '1' en las celdas que son parte de la solucion.
                vect_salida[celdaActual.first][celdaActual.second] = 1;
                // Se busca al padre de la celda actual.
                celdaActual = Padre[celdaActual.first][celdaActual.second];
            }

            // Se imprime el arreglo (MxN) con el camino de la solucion.
            for (int i = 0; i < size_M ; i++){
                for (int j = 0; j < size_N ; j++){
                    cout << vect_salida[i][j] << " ";   
                }
                cout << endl;
            }
        }

        // Si la celdaActual no es la celda meta (M-1, N-1).
        else {

            // Se hace '0' el valor de la celdaActual.
            vect[celdaActual.first][celdaActual.second] = 0;

            // Hacer un push al queue de cada celda adyacente valida con valor 1 y poner como padres de ellas a celdaActual:

            // Abajo.
            if (celdaActual.first + 1 < size_M){
                if (vect[celdaActual.first + 1][celdaActual.second] == 1){
                    queue.push(make_pair(celdaActual.first + 1, celdaActual.second));
                    Padre[celdaActual.first + 1][celdaActual.second] = make_pair(celdaActual.first, celdaActual.second);
                }
            }

            // Derecha.
            if (celdaActual.second + 1 < size_N){
                if (vect[celdaActual.first][celdaActual.second + 1] == 1){
                    queue.push(make_pair(celdaActual.first, celdaActual.second + 1));
                    Padre[celdaActual.first][celdaActual.second + 1] = make_pair(celdaActual.first, celdaActual.second);
                }
            }

            // Arriba.
            if (celdaActual.first - 1 >= 0){
                if (vect[celdaActual.first - 1][celdaActual.second] == 1){
                    queue.push(make_pair(celdaActual.first - 1, celdaActual.second));
                    Padre[celdaActual.first - 1][celdaActual.second] = make_pair(celdaActual.first, celdaActual.second);
                }
            }
            
            // Izquierda.
            if (celdaActual.second - 1 >= 0){
                if (vect[celdaActual.first][celdaActual.second - 1] == 1){
                    queue.push(make_pair(celdaActual.first, celdaActual.second - 1));
                    Padre[celdaActual.first][celdaActual.second - 1] = make_pair(celdaActual.first, celdaActual.second);
                }
            }
        }
    }
}


// Inicio del main().
int main(){

    // Se obtienen los inputs:
    std::istream& in = cin;

    // Se inicializan las variables 'int' 'M' y 'N' para almacenar las dimensiones del arreglo.
    int M = 0;
    int N = 0;

    // Se obtienen las dimensiones (MxN) y se almacenan.
    cin >> M;
    cin >> N;

    // Se inicializa un vector de vectores de tamaño M con valores tipo 'int'.
    vector<vector<int> > vect;


    string S;
    getline(cin, S);

    // Se inicializa variable string 'myText' que sera utilizada para obtener las M lineas y sus N valores. 
    string myText;
    // Se obtienen las M lineas.
    for (int i = 0; i < M; i++){
        // Se obtiene la linea y guarda en 'myText'.
        getline(cin, myText);
        // Variable auxiliar para obtener fragmentos de la linea.
        string text = myText;
        // Variable para saber la posicion de cada ' ' entre los N valores.
        int pos = 0;
        // Se genera un vector auxiliar para llenar la matriz.
        vector<int> temp_vect;
        // Se separan y obtienen los N valores de cada linea.
        for (int j=0; j < N; j++){
            pos = text.find(" ");
            string val = text.substr(0,pos);
            text = text.substr(pos+1);
            // Se almacena cada valor.
            temp_vect.push_back(stoi(val));
        }

        // Se hace un push al vector 'vect' (tamaño MxN) del vector temporal 'temp_vect' (tamaño N)
        vect.push_back(temp_vect);
        temp_vect.clear();
    }

    // Se llama al metodo BackTracking con la matriz (MxN) obtenida como parametro.
    cout << "BackTracking:" << endl;
    BackTracking(vect);

    cout << endl;
    cout << endl;

    // Se llama al metodo RamificacionPoda con la matriz (MxN) obtenida como parametro.
    cout << "Ramificacion y Poda:" << endl;
    RamificacionPoda(vect);


    return 0;
    }