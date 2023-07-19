/*
* Fecha: 2 Marzo 2023
* Autores:
*   Matricula: A01652327
*   Nombre: Diego Esparza Hurtado
*
*   Matricula: A01284610
*   Nombre: Alejandro Lizarraga Vizcarra
*
* Actividad 3.4 Implementación de Kruskal
*
*    En el programa se busca el árbol de expansión mínima (MST) en un grafo no dirigido. 
*    Para esto se utiliza la implementación del algoritmo Kruskal, donde se lee una matriz de vertices de tamaño 'n' x 'n'
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
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;
using std::pair;
using std::sort;

#define edge pair<int, int>

/* Clase Graph:
 * Descripción: Clase
 * Entrada: ninguna.
 * Salida: ninguna.
 * Precondición: .
 * Postcondición: .
 * Complejidad: . 
*/
class Graph {
    private:
        //vector de vertices
        vector<pair<int, edge> > G;
        //vector de MST
        vector<pair<int, edge> > T;
        int *parent;
        //cantidad de nodos
        int V;
    public:
        //constructor
        Graph(int V);
        //metodo para agregar vertice
        void AddWeightedEdge(int u, int v, int peso);
        //método para encontrar representante de grupo
        int find_set(int i);
        //método para unir grupos
        void union_set(int u, int v);
        //método de kruskal
        void kruskal();
        //método para impresión de datos
        void print();
};

/* Constructor Graph:
 * Descripción: Recibe un valor entero 'V' que representa la cantidad de nodos que hay
 * Entrada: Integer 'V'.
 * Salida: ninguna.
 * Precondición: Se recibe una variable 'V' de tipo integer.
 * Postcondición: Se instancía objeto.
 * Complejidad: O(V) 
*/
Graph::Graph(int V) {
    parent = new int[V];

    // Hacer por cada nodo que su representate sea si mismo
    for (int i = 0; i < V; i++){
        parent[i] = i;
    }

    // Borrar valores de vertices y MST
    G.clear();
    T.clear();
}

/* Método AddWeightedEdge:
 * Descripción: Recibe un valor entero 'nodo1' y 'nodo2' que representa una conexión entre ambos nodos, aparte recibe el entero 'peso' que representa el peso del vertice. Este vertice lo agrega a la lista de vertices del objeto 'Graph'
 * Entrada: Integer 'nodo1', 'nodo2', 'peso'.
 * Salida: ninguna.
 * Precondición: Se recibe variable 'nodo1', 'nodo2' y 'peso' de tipos integer.
 * Postcondición: Se agrega a la matriz de conexiones el vertice de entrada.
 * Complejidad: O(1) 
*/
void Graph::AddWeightedEdge(int nodo1, int nodo2, int peso) {
    // Agregar a vector de conexiones el vertice. 
    G.push_back(make_pair(peso, edge(nodo1, nodo2)));
}

/* Método find_set:
 * Descripción: Encuentra el nodo representativo del grupo en el que se encuentra el nodo 'i'
 * Entrada: Integer 'i'.
 * Salida: Entero del nodo representativo.
 * Precondición: Se recibe el integer 'i' que representa el nodo del que se quiere buscar su padre.
 * Postcondición: Retorna el nodo representativo del grupo.
 * Complejidad: O(V) 
*/
int Graph::find_set(int i) {
    // Si el padre en la posición i es si mismo
    if (i == parent[i])
        return i;
    else
        // Si no es, buscar el padre del padre para encontrar representante del grupo
        return find_set(parent[i]);
}

/* Método union_set:
 * Descripción: Une los grupos de dos nodos 'u' y 'v' al igualar el padre entre ambos nodos
 * Entrada: Integer 'u', 'v'.
 * Salida: nada.
 * Precondición: Se recibe el integer 'u' y 'v' que representa los nodos a unir.
 * Postcondición: Se igualan los padres entre ambos nodos.
 * Complejidad: O(1) 
*/
void Graph::union_set(int u, int v) {
    //igualar representante de nodo u y v
    parent[u] = parent[v];
}

/* Método kruskal:
 * Descripción: Se utiliza el metodo de kruskal para agregar al vector 'T' los vertices del MST
 * Entrada: ninguna
 * Salida: nada.
 * Precondición: Contener en 'G' los vertices del grafo.
 * Postcondición: Se guarda en el vertice 'T' el MST.
 * Complejidad: O(V log(V)) 
 * V = vertices
*/
void Graph::kruskal() {
    int i, uRep, vRep;

    //Ordenar vertices por peso O(V log(V))
    sort(G.begin(), G.end());

    //Por cada vertice conseguir representantes del grupo
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);

        //Si los representantes son diferentes, agregar al vector de MST y unir grupos entre nodos
        if (uRep != vRep) {
            T.push_back(G[i]);
            union_set(uRep, vRep);
        }
    }
}

/* Método print:
 * Descripción: Impresión de los datos del MST
 * Entrada: ninguna
 * Salida: nada.
 * Precondición: Contener en 'T' los vertices del MST al procesar el metodo 'kruskal'.
 * Postcondición: Se imprime el peso de los vertices del MST al igual que la suma de pesos.
 * Complejidad: O(V) 
 * V = vertices
*/
void Graph::print() {
    int sum = 0;

    // Por cada vertice en la lista de MST, imprimir peso y formar sumatoria de pesos
    for (int i = 0; i < T.size(); i++) {
        sum += T[i].first;
        cout << T[i].first << endl;
    }

    // Imprimir sumatoria de pesos de MST
    cout << sum << endl;
}


int main(){

    // Se obtienen los inputs:
    std::istream& in = cin;

    // Se inicializa la variable 'N' para almacenar las dimensiones del arreglo.
    int N = 0;

    // Se obtienen las dimensiones (NxN) y se almacenan.
    cin >> N;

    // Se inicializa un objeto tipo 'Graph' con N el el constructor representando la cantidad de nodos.
    Graph g(N);

    string S;
    getline(cin, S);

    // Se inicializa variable string 'myText' que sera utilizada para obtener las M lineas y sus N valores según la diagonal menor (considerando un arbol no dirigido)
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
        // Se separan y obtienen los valores de la diagonal menor.
        for (int j=0; j < i; j++){

            pos = text.find(" ");
            string val = text.substr(0,pos);
            text = text.substr(pos+1);
            // Si hay conexión, se agrega al objeto tipo 'Graph' vertice
            if (stoi(val) != -1){
                g.AddWeightedEdge(i, j, stoi(val));
            }

        }


    }

    // Llamar a metodo kruskal
    g.kruskal();

    // Imprimir MST
    g.print();

    return 0;
}