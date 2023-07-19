/*
 * Fecha: 2 Marzo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 3.2 - Implementación de "Dijkstra and Floyd"
 *    En el programa se hace uso de un vector de vectores para almacenar el laberinto. CAMBIAR
 *    Para buscar el camino desde el origen (0, 0) hasta la meta (M-1, N-1), se hace uso de dos tecnicas: "BackTracking" (stack) y "Ramificacion y Poda" (queue). CAMBIAR
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
using std::priority_queue;
using std::greater;
using std::pair;
using std::make_pair;



/*
 * Método Dijkstra:
 * Descripción: Encuentra el camino más corto del grafo con el uso del algoritmo de Dijkstra.
 * Entrada: Un entero 'src' que representa el nodo inicial a partir del cual se calculan las distancias.
 * Salida: Imprime en pantalla el Shortest Path Tree.
 * Precondición: El grafo deberá estar correctamente cargado en memoria.
 * Postcondición: Nada.
 * Complejidad: O((V+E)log(V))
 *      V = numNodes.
 *      E = numEdges
*/
void Dijkstra(vector<vector<int> > vect, int src) {

    int n = vect.size();

    // Se crea un priority queue para almacenar los vertices que son preprocesados.
    priority_queue< pair<int,int>, vector <pair<int,int> > , greater<pair<int,int> > > pq;
            
    // Se crea el vector de distancias y se inicializa cada una en infinito.
    vector<int> dist(n, INT_MAX);
    
    // Se ingresa el nodo origen y se modifica su distancia a cero.
    pq.push(make_pair(src, 0));
    dist[src] = 0;

    //mientras la priority queue no este vacia, conseguir el valor de arriba
    while (!pq.empty()) {
        
        int u = pq.top().first;
        pq.pop();

        //por cada vertice comparar si el uso de este como intermediario llega a tener una menor distancia
        for (int i = 0; i < n; i++){
            int v = i;
            int weight = vect[u][i];
            if (dist[v] > dist[u] + weight && weight != INT_MAX){
                dist[v] = dist[u] + weight;
                pq.push(make_pair(v, dist[v]));
            }
        }

    }
    
    // Se imprimen todas las distancias.
    for (int i = 0; i < n; ++i){
        if (i != src){
            cout << "node " << src+1 << " to node " << i+1 << " : " << dist[i] << endl;
        }
    }
}


/*
 * Método fullDijkstra:
 * Descripción: Llama al metodo Dijkstra por cada nodo que hay.
 * Entrada: Un vector de vectores 'vect' que representa el peso de edges entre nodos.
 * Salida: Nada.
 * Precondición: El grafo deberá estar correctamente cargado en memoria.
 * Postcondición: Nada.
 * Complejidad: O(V)
 *      V = numNodes.
*/
void fullDijkstra(vector<vector<int> > vect){

    int n = vect.size();

    cout << "Dijkstra :" << endl;

    //por cada valor del vector se llama el metodo Dijkstra
    for (int i = 0; i < n; i++){
        Dijkstra(vect,i);
    }
}




/*
 * Método Floyd:
 * Descripción: Encuentra la distnacia más corta entre todos los nodos posibles con el algoritmo Floyd-Warshall.
 * Entrada: Un vector de vectores 'vect' que representa el peso de edges entre nodos.
 * Salida: Imprime en pantalla la matriz de valores más pequeños.
 * Precondición: El grafo deberá estar correctamente cargado en memoria.
 * Postcondición: Nada.
 * Complejidad: O(V^3)
 *      V = numNodes.
*/
void Floyd(vector<vector<int> > vect){

    int n = vect.size();
    int m = vect[0].size();

    // Por cada nodo fuente recorrer
    for (int k = 0; k < n; k++){
        // Por cada nodo destinatario recorrer
        for (int i = 0; i < n; i++){
            // Por cada nodo ultilizado como intermediario comparar si utilizarlo tiene una distnacia menor
            for (int j = 0; j < n; j++){
                if (vect[i][k] != INT_MAX && vect[k][j] != INT_MAX && vect[i][k]+vect[k][j] < vect[i][j]){
                    vect[i][j] = vect[i][k] + vect[k][j];
                }
            }
        }
    }

    cout << "Floyd :" << endl;
    // Imprimir matriz de 2 dimensiones con distancias minimas
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << vect[i][j] << " ";
        }
        cout << endl;
    }
}




int main(){

    // Se obtienen los inputs:
    std::istream& in = cin;

    // Se inicializa la variable 'N' para almacenar las dimensiones del arreglo.
    int N = 0;

    // Se obtienen las dimensiones (NxN) y se almacenan.
    cin >> N;

    // Se inicializa un vector de vectores de tamaño M con valores tipo 'int'.
    vector<vector<int> > vect;


    string S;
    getline(cin, S);

    // Se inicializa variable string 'myText' que sera utilizada para obtener las M lineas y sus N valores. 
    string myText;
    // Se obtienen las M lineas.
    for (int i = 0; i < N; i++){
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
            if (stoi(val) != -1){
                temp_vect.push_back(stoi(val));
            }
            else {
                temp_vect.push_back(INT_MAX);
            }
        }

        // Se hace un push al vector 'vect' (tamaño MxN) del vector temporal 'temp_vect' (tamaño N)
        vect.push_back(temp_vect);
        temp_vect.clear();
    }

    fullDijkstra(vect);

    cout << endl;

    Floyd(vect);


    return 0;
}