// g++ -o a.out a01652327main.cpp
// ./a.out < test01.txt

// A divide and conquer program in C++
// to find the smallest distance from a
// given set of points.

/*
 * Para compilar: 
 * g++ -std=c++17 -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <climits>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::istream;
using std::list;
using std::min;
using std::sort;

// Kruskal
// Se define 'aristaKruskal' que será un pair<int,int> donde se almacena la conexion entre dos nodos 'A' y 'B'.
#define aristaKruskal pair<int, int>

//Kruskal
// Clase para el grafo.
class GrafoKruskal {
    private:
        // Vector 'G' que almacena las aristas con la distancia con las que cuenta el grafo.
        vector<pair<int, aristaKruskal> > G;
        // Vector 'T' que almacena las aristas que entran al MST (Entero)
        vector<pair<int, aristaKruskal> > T;
        int *parent;
        // Entero 'V' que almacena la cantidad de nodos.
        int V;
    public:
        // Constructor.
        GrafoKruskal(int V);
        // Constructor vacio.
        GrafoKruskal();
        // Metodo para agregar una arista al grafo.
        void AgregarArista(int u, int v, int peso);
        // Metodo para encontrar el set en el que se encuentra un nodo.
        int EncontrarSet(int i);
        // Metodo para unir los sets de dos nodos en uno mismo.
        void UnirSets(int u, int v);
        // Metodo de Kruskal.
        void Kruskal();
};

GrafoKruskal::GrafoKruskal() {

}

/* Constructor GrafoKruskal:
 * Descripción: Genera un objeto 'GrafoKruskal' con 'V' numero de nodos y asigna a cada nodo como su padre (propio set).
 * Entrada: int 'V' que representa la cantidad de nodos que conforman el grafo.
 * Salida: ninguna.
 * Precondición: Se recibe una variable 'V' de tipo int.
 * Postcondición: Se instancia un objeto del tipo 'GrafoKruskal' con sus respectivos atributos.
 * Complejidad: O(V) 
 *      V = Numero de nodos.
*/
GrafoKruskal::GrafoKruskal(int V) {

    // Arreglo 'parent' que almacena al representante de grupo de cada nodo.
    parent = new int[V];

    // Cada nodo es su propio representate al inicio.
    for (int i = 0; i < V; i++){
        parent[i] = i;
    }

    // Borrar valores de los vectores de aristas y MST.
    G.clear();
    T.clear();
}

/* Método AgregarArista:
 * Descripción: Recibe un valor entero 'nodo1' y 'nodo2' que representa una conexión entre ambos nodos; recibe el entero 'peso' que representa el peso de la arista. 
 *              Esta arista se agrega a la lista de aristas del objeto 'GrafoKruskal'.
 * Entrada: int 'nodo1' que es el valor numerico del primer nodo; int 'nodo2' que es el valor numerico de segundo nodo; int 'peso' que representa en peso/longitud de la arista.
 * Salida: Ninguna.
 * Precondición: Se recibe variables 'nodo1', 'nodo2' y 'peso' de tipos integer.
 * Postcondición: Se agrega al vector de conexiones la arista ingresada.
 * Complejidad: O(1) 
*/
void GrafoKruskal::AgregarArista(int nodo1, int nodo2, int peso) {
    // Agregar a vector de conexiones el vertice. 
    G.push_back(make_pair(peso, aristaKruskal(nodo1, nodo2)));
}

/* Método EncontrarSet:
 * Descripción: Encuentra el nodo representativo del set en el que se encuentra el nodo 'i'.
 * Entrada: Integer 'i'.
 * Salida: Devuelve el entero del nodo representativo.
 * Precondición: Se recibe el integer 'i' que representa el nodo del que se quiere buscar su padre.
 * Postcondición: Retorna el nodo representativo del set.
 * Complejidad: O(V).
 *      V = Numero de nodos.
*/
int GrafoKruskal::EncontrarSet(int i) {
    // Si el padre en la posicion i es el mismo.
    if (i == parent[i])
        return i;
    else
        // Si no es, buscar el padre para encontrar al representante del set.
        return EncontrarSet(parent[i]);
}

/* Método UnirSets:
 * Descripción: Une los sets de dos nodos 'u' y 'v' al igualar el padre entre ambos nodos.
 * Entrada: int 'u' que representa el valor numerico del primer nodo ; int 'v' que representa el valor numerico del segundo nodo.
 * Salida: Ninguna.
 * Precondición: Se reciben los int 'u' y 'v' que representa los nodos a unir.
 * Postcondición: Se igualan los padres entre ambos nodos.
 * Complejidad: O(1) 
*/
void GrafoKruskal::UnirSets(int u, int v) {
    // Igualar representante de nodo 'u' y 'v'.
    parent[u] = parent[v];
}

/* Método Kruskal:
 * Descripción: Se utiliza el metodo de Kruskal para agregar al vector 'T' los vertices del MST.
 * Entrada: Ninguna.
 * Salida: Se imprimen las longitudes de las aristas en el orden en el que fueron agregadas y la longitud total del MST.
 * Precondición: Contener en 'G' las aristas del grafo.
 * Postcondición: Se guardan las aristas que forman parte del MST en el vector 'T'.
 *                Se imprimen las longitudes de las aristas del MST en el orden en el que fueron agregadas y su longitud total.
 * Complejidad: O(E log(E)) 
 *      E = Numero de Aristas.
*/
void GrafoKruskal::Kruskal() {

    //Ordenar las aristas por peso/longitud O(E log(E))
    // E = Numero de Aristas
    sort(G.begin(), G.end());

    //Por cada arista conseguir representantes del set.
    for (int i = 0; i < G.size(); i++) {
        // Representante de set de la primera arista.
        int uRep = EncontrarSet(G[i].second.first);
        // Representante de set de la segunda arista.
        int vRep = EncontrarSet(G[i].second.second);

        //Si los representantes son diferentes, agregar al vector de MST y unir sets de los nodos.
        if (uRep != vRep) {
            T.push_back(G[i]);
            UnirSets(uRep, vRep);
        }
    }

    // Variable int 'sum' que almacena la suma total de la longitud del MST.
    int sum = 0; 

    // Por cada arista en la lista de MST, imprimir longitud/peso y sumar su valor a la variable 'sum' para total de longitud.
    for (int i = 0; i < T.size(); i++) {
        sum += T[i].first;
        cout << T[i].first << endl;
    }

    // Imprimir sumatoria de pesos de MST.
    cout << sum << endl;

}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

// Flujo
// A structure to represent a edge between
// two vertex
struct EdgeFlow {
    int v; // Vertex v (or "to" vertex)
           // of a directed edge u-v. "From"
           // vertex u can be obtained using
           // index in adjacent array.
 
    int flow; // flow of data in edge
 
    int C; // capacity
 
    int rev; // To store index of reverse
             // edge in adjacency list so that
             // we can quickly find it.
};
 
// Residual Graph
class GraphFlow {
    int V; // number of vertex
    int* level; // stores level of a node
    vector<EdgeFlow>* adj;
 
public:
    GraphFlow(){

    }
    GraphFlow(int V)
    {
        adj = new vector<EdgeFlow>[V];
        this->V = V;
        level = new int[V];
    }
 
    // add edge to the graph
    void addEdgeFlow(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        EdgeFlow a{ v, 0, C, (int)adj[v].size() };
 
        // Back edge : 0 flow and 0 capacity
        EdgeFlow b{ u, 0, 0, (int)adj[u].size() };
 
        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }
 
    bool BFSFlow(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};
 
// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool GraphFlow::BFSFlow(int s, int t)
{
    for (int i = 0; i < V; i++)
        level[i] = -1;
 
    level[s] = 0; // Level of source vertex
 
    // Create a queue, enqueue source vertex
    // and mark source vertex as visited here
    // level[] array works as visited array also.
    list<int> q;
    q.push_back(s);
 
    vector<EdgeFlow>::iterator i;
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            EdgeFlow& e = *i;
            if (level[e.v] < 0 && e.flow < e.C) {
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;
 
                q.push_back(e.v);
            }
        }
    }
 
    // IF we can not reach to the sink we
    // return false else true
    return level[t] < 0 ? false : true;
}
 
// A DFS based function to send flow after BFS has
// figured out that there is a possible flow and
// constructed levels. This function called multiple
// times for a single call of BFS.
// flow : Current flow send by parent function call
// start[] : To keep track of next edge to be explored.
//           start[i] stores  count of edges explored
//           from i.
//  u : Current vertex
//  t : Sink
int GraphFlow::sendFlow(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;
 
    // Traverse all adjacent edges one -by - one.
    for (; start[u] < adj[u].size(); start[u]++) {
        // Pick next edge from adjacency list of u
        EdgeFlow& e = adj[u][start[u]];
 
        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            // find minimum flow from u to t
            int curr_flow = std::min(flow, e.C - e.flow);
 
            int temp_flow
                = sendFlow(e.v, curr_flow, t, start);
 
            // flow is greater than zero
            if (temp_flow > 0) {
                // add flow  to current edge
                e.flow += temp_flow;
 
                // subtract flow from reverse edge
                // of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
 
    return 0;
}
 
// Returns maximum flow in graph
int GraphFlow::DinicMaxflow(int s, int t)
{
    // Corner case
    if (s == t)
        return -1;
 
    int total = 0; // Initialize result
 
    // Augment the flow while there is path
    // from source to sink
    while (BFSFlow(s, t) == true) {
        // store how many edges are visited
        // from V { 0 to V }
        int* start = new int[V + 1]{ 0 };
 
        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT_MAX, t, start)) {
 
            // Add path flow to overall flow
            total += flow;
        }
       
          // Remove allocated array
          delete[] start;
    }
 
    // return maximum flow
    return total;
}

struct Datos {
    int N;
    GrafoKruskal pesos;
    GraphFlow flujos;

    Datos(int _N){
        this->N = _N;
        pesos = GrafoKruskal(N);
        flujos = GraphFlow(N);
    }
};

void getFileText(){

    // Se inicializa la variable 'N' para almacenar las dimensiones del arreglo.
    int N = 0;

    // Se obtienen las dimensiones (NxN) y se almacenan.
    cin >> N;
    //inicializar Datos
    Datos datos(N);


    // Se obtiene la matriz de tamaño NxN que representa el grafo con las distancias en kilometros entre las colonias de la ciudad.
    for (int i = 0; i < N; i++){
        for (int j=0; j < N; j++){
            int val = 0;
            cin >> val;
            // Se agrega la arista al objeto tipo 'GrafoKruskal'.
            datos.pesos.AgregarArista(i, j, val);

        }
    }
    cout << -1 << endl;
    datos.pesos.Kruskal();

    cout << -2 << endl;

    // Se obtiene la matriz de tamaño NxN que representa las capacidades maximas de flujo de datos entre colonia i y colonia j.
    for (int i = 0; i < N; i++){
        // Se separan y obtienen los valores de la matriz.
        for (int j=0; j < N; j++){
          int val = 0;
          cin >> val;
          if (val != 0)
            datos.flujos.addEdgeFlow(i, j, val);
        }
    }
    cout << -3 << endl;
    cout << datos.flujos.DinicMaxflow(0,9) << endl;

    cout << -4 << endl;

    // Se obtiene la lista de N pares ordenados que representan la ubicacion en un plano coordenado de las centrales.
    for (int i = 0; i < N; i++){
      for (int j = 0; j < 2; j++){
        int val = 0;
        cin >> val;
        cout << val << " "; 
      }
      cout << endl;
    }

  cout << -4 << endl;
  for (int i = 0; i < 5; i++){
    cout << -4 << i << endl;
  }


}

int main(){
    getFileText();
    return 0;
}