/*
 * Fecha: 29 Mayo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 * 
 *   Matricula: A00833547
 *   Nombre: Samuel Acosta Ugarte
 *
 * Actividad Integradora 2 - Alta demanda para los Proveedores de Servicios de Internet (ISP)
 *    Parte 1:
 *          Se busca la forma optima de cablear con fibra optica conectando colonias.
 *          Se imprimen las aristas en orden en que son agregadas al Minimum Spanning Tree (MST) y la longitud total.
 *    Parte 2:
 *          Se busca la ruta mas corta posible para visitar cada colonia exactamente una vez y al finalizar regresar a la colonia de origen (Travelling Salesman Problem - TSP).
 *          Se imprime el ciclo hamiltoniano mas corto y la distancia total de dicho ciclo.
 *    Parte 3:
 *          Se busca el flujo maximo de informacion que se puede compartir entre un nodo origen (0) y un nodo destino (9) (Problema del Flujo Maximo con algoritmo de Dinic).
 *          Se imprime el flujo maximo entre el nodo origen (0) y el nodo destino (9).
 *    Parte 4:
 *          Se buscan identificar los poligonos de Voronoi basados en 10 centrales para saber cual es la mas cercana dependiendo de un punto dado.
 *          Se imprimen los poligonos de Voronoi que todos sus puntos se encuentren dentro de un area delimitada por el rectangulo de los valores de 'x' y 'y' minimos y maximos de las centrales.
 *
 * Para compilar: 
 * g++ -std=c++17 -o a.out a01652327main.cpp
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
#include <utility>
#include <cmath>
#include <unordered_set>
//#include <bits/stdc++.h>

using namespace std;

// Se define 'aristaKruskal' que será un pair<int,int> donde se almacena la conexion entre dos nodos 'A' y 'B'.
#define aristaKruskal pair<int, int>



// Kruskal ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

// Constructor vacio.
// Complejidad: O(1)
GrafoKruskal::GrafoKruskal() {}

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



// TSP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Método printPath:
 * Descripción: Imprime el minimo ciclo hamiltoniano.
 * Entrada: vector<int> 'path' con el camino a seguir.
 * Salida: Se imprime el camino con los nodos en orden a visitarlos.
 * Precondición: Recibir un vector<int> 'path' con el camino que resuelve el TSP.
 * Postcondición: Se imprime el camino con los nodos en orden a visitarlos.
 * Complejidad: O(n) ; n = numero de nodos. 
*/
void printPath(vector<int>& path)
{
    // Se imprime cada uno de los nodos en el orden a visitar.
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
}

/* Método travellingSalesmanProblem:
 * Descripción: Implementacion del Travelling Salesman Problem (TSP) utilizando la tecnica de fuerza bruta para encontrar la ruta mas corta que visite todos los vertices de un grafo ponderado.
 * Entrada: vector<vector<int>> 'graph' que representa el grafo ponderado ; int 's' que representa el nodo donde se inicia y termina el camino.
 * Salida: Se imprime la ruta a seguir y la distancia total de dicha ruta.
 * Precondición: 'graph' debe contener la representacion de un grafo poderado valido.
 * Postcondición: Se imprime la ruta a seguir y la distancia total de dicha ruta.
 * Complejidad: O(n!) 
 *      n = Numero de nodos.
*/
int travellingSalesmanProblem(const std::vector<std::vector<int>>& graph, int s)
{
    // Variable int 'n' que almacena el numero de nodos.
    int n = graph.size();

    // Se almacenan todos los nodos menos el inicial en un vector<int> 'vertex'.
    vector<int> vertex;
    for (int i = 0; i < n; i++)
        if (i != s)
            vertex.push_back(i);

    // Variable int 'min_path' donde se almacena el peso minimo del ciclo hamiltoniano.
    int min_path = INT_MAX;
    // Vector<int> 'min_path_vertex' donde se almacena el camino a seguir del ciclo hamiltoniano.
    vector<int> min_path_vertex;

    // Mientras aun haya algun camino posible a explorar.
    do {
        // Variable int 'current_pathweight' que almacena el peso actual.
        int current_pathweight = 0;

        // Se obtiene el costo actual.
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];

        // Se actualiza el camino mas corto y su vertice.
        if (current_pathweight < min_path) {
            min_path = current_pathweight;
            min_path_vertex = vertex;
        }
    } while (next_permutation(vertex.begin(), vertex.end()));

    // Se imprimen los nodos en el orden que se deben de visitar.
    cout << s << " ";
    printPath(min_path_vertex);
    cout << s << endl;

    // Se devuelve la distancia minima.
    return min_path;
}



// MaxFlow ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Estructura para representar una arista entre dos vertices.
struct EdgeFlow {
    
    // Indice del vertice destino de una conexion u-v de un grafo dirigido.
    int v;

    // Flujo de la arista.
    int flow;

    // Capacidad de la arista.
    int C;

    // Indice del vertice origen.
    int rev;
};
 
// Grafo residual.
class GraphFlow {
    // Numero de nodos.
    int V;
    // Almacena el nivel de un nodo.
    int* level;
    vector<EdgeFlow>* adj;
 
public:
    GraphFlow(){

    }
    GraphFlow(int V) {
        adj = new vector<EdgeFlow>[V];
        this->V = V;
        level = new int[V];
    }
 
    // Metodo para añadir una arista.
    void addEdgeFlow(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        EdgeFlow a{ v, 0, C, (int)adj[v].size() };
 
        // Back edge : 0 flow and 0 capacity
        EdgeFlow b{ u, 0, 0, (int)adj[u].size() };
 
        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    //
    bool BFSFlow(int s, int t);

    //
    int sendFlow(int s, int flow, int t, int ptr[]);

    //
    int DinicMaxflow(int s, int t);
};
 
/* Método BFSFlow:
 * Descripción: Revisa si es posible mandar mas flujo desde el nodo 's' hacia el nodo 't' y le asigna su nivel a los nodos.
 * Entrada: int 's' que es el nodo origen ; int 't' que es el nodo destino.
 * Salida: Devuelve un valor booleano dependiendo de si aun se puede o no mandar flujo desde el nodo 's' al nodo 't'.
 * Precondición: Se deben recibir dos int 's' y 't' validos, asi como tener una estructura que representa al grafo dirigido valida.
 * Postcondición: El nivel de cada nodo se actualiza en el arreglo 'level', donde el nivel del nodo origen es 0.
 *                Devuelve un valor booleano dependiendo de si aun se puede o no mandar flujo desde el nodo 's' al nodo 't'.
 * Complejidad: O(E) 
 *      E = Numero de Aristas.
*/
bool GraphFlow::BFSFlow(int s, int t)
{
    // Inicializar el nivel de los nodos en -1.
    for (int i = 0; i < V; i++)
        level[i] = -1;
    // Nivel del nodo origen.
    level[s] = 0;
 
    // Se crea un queue, se inserta el nodo origen y se marca el nodo origen como visitado en 'level'
    list<int> q;
    q.push_back(s);
 
    vector<EdgeFlow>::iterator i;
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            EdgeFlow& e = *i;
            if (level[e.v] < 0 && e.flow < e.C) {
                // Nivel del vertice actual es el del padre + 1.
                level[e.v] = level[u] + 1;
 
                q.push_back(e.v);
            }
        }
    }

    // Si se puede enviar flujo, se devuelve 'true', sino 'false'.
    return level[t] < 0 ? false : true;
}

/* Método sendFlow:
 * Descripción: Una implementacion de DFS para enviar flujo despues de que el BFS sabe que se puede enviar un flujo.
 * Entrada: int 'u' que es el nodo actual ; int 'flow' que es el flujo enviado por la llamada del padre ;
 *          int 't' que es el nodo destino ; int[] 'start' para saber cual es el siguiente nodo a explorar. 
 * Salida: Devuelve un int con el flujo total enviado a traves del camino.
 * Precondición: La red de flujo y sus aristas deben haber sido previamente inicializadas.
 * Postcondición: Se actualizan los flujos de las aristas y se incrementa el flujo total en la red.
 * Complejidad: O(V*E)
 *      V = Numero de Vertices.
 *      E = Numero de Aristas.
*/
int GraphFlow::sendFlow(int u, int flow, int t, int start[])
{
    // Si ya se alcanzo el destino, se devuelve el flujo
    if (u == t)
        return flow;
 
    // Se recorren todos los nodos adyacentes.
    for (; start[u] < adj[u].size(); start[u]++) {
        // Se selecciona la siguiente arista.
        EdgeFlow& e = adj[u][start[u]];
 
        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            // Se encuentra el flujo minimo desde 'u' hasta 't'.
            int curr_flow = std::min(flow, e.C - e.flow);
 
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
 
            // En caso de que el flujo sea mayor a 0.
            if (temp_flow > 0) {
                // Se añade el flujo a la arista actual.
                e.flow += temp_flow;
 
                // Se resta el flujo a la arista inversa.
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
 
    return 0;
}
 
/* Método DinicMaxflow:
 * Descripción: Implementa el algoritmo de Dinic para obtener el flujo maximo desde un nodo origen y un nodo destino en un grafo dirigido.
 * Entrada: int 's' que es el nodo origen ; int 't' que es el nodo destino.
 * Salida: Devuelve el flujo maximo desde el nodo 's' hasta el nodo 't'.
 * Precondición: Contar con un grafo dirigido valido y contar con los nodos origen y destino.
 * Postcondición: Devuelve el flujo maximo desde el nodo 's' hasta el nodo 't'.
 * Complejidad: O(EV^2) 
 *      V = Numero de Vertices.
 *      E = Numero de Aristas.
*/
int GraphFlow::DinicMaxflow(int s, int t)
{
    // Caso base en caso de que el nodo origen sea el nodo destino.
    if (s == t)
        return -1;
    
    // Variable int 'total' donde se almacenara el flujo maximo.
    int total = 0;
 
    // Se aumenta el flujo mientras haya un camino desde el nodo origen hasta el nodo destino.
    while (BFSFlow(s, t) == true) {
        // Se almacena la cantidad de nodos visitados hacia 'V'.
        int* start = new int[V + 1]{ 0 };
 
        // Mientras el flujo no sea igual a 0.
        while (int flow = sendFlow(s, INT_MAX, t, start)) {
 
            // Se añade el flujo al flujo maximo.
            total += flow;
        }
       
          // Se libera la memoria de 'start'.
          delete[] start;
    }
 
    // Se devuelve el flujo maximo.
    return total;
}



// Voronoi ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Puntos para delimintar el cuadrado de la region de Voronoi.
// Variable int 'minx' para almacenar el valor minimo de 'x' para el cuadrado de la region para Voronoi.
int minx = 0;
// Variable int 'maxx' para almacenar el valor maximo de 'x' para el cuadrado de la region para Voronoi.
int maxx = 0;
// Variable int 'miny' para almacenar el valor minimo de 'y' para el cuadrado de la region para Voronoi.
int miny = 0;
// Variable int 'maxy' para almacenar el valor maximo de 'y' para el cuadrado de la region para Voronoi.
int maxy = 0;


// Clase para un punto.
class Point {
    
    private:
        // Variables del tipo 'double' para almacenar las coordenadas 'x' y 'y' del punto.
        double x,y;
    
    public:
        // Constructor sin parametros de un punto. Asigna al punto las coordenadas 'x=0.0' y 'y=0.0'.
        // Complejidad: O(1)
        Point(){
            this->x = 0.0;
            this->y = 0.0;
        }

        // Constructor que recibe dos valores 'double' 'x_I' y 'y_I' que asigna a las variables 'x' y 'y' del punto.
        // Complejidad: O(1)
        Point(double xI, double yI){
            this->x = xI;
            this->y = yI;
        }

        // Constructor que recibe un punto como parametro y asigna los valores de 'x' y 'y' del punto recibido como los valores de 'x' y 'y' del nuevo punto.
        // Complejidad: O(1)
        Point(const Point& other) {
            this->x = other.x;
            this->y = other.y;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'x' del punto.
        // Complejidad: O(1)
        double getX() const {
            return this->x;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'y' del punto.
        // Complejidad: O(1)
        double getY() const {
            return this->y;
        }

        // Metodo que modifica el valor 'x' de un punto con el valor 'double' recibido como parametro.
        // Complejidad: O(1)
        void setX(double xI) {
            this->x = xI;
        }

        // Metodo que modifica el valor 'y' de un punto con el valor 'double' recibido como parametro.
        // Complejidad: O(1)
        void setY(double yI){
            this->y = yI;
        }
};

// Clase para un segmento.
class Segment {
    
    private:
        // Objetos de tipo 'Point' para almacenar los dos puntos que generan al segmento.
        Point p1, p2;
    
    public:
        // Constructor sin parametros de un segmento. Asigna a los puntos 'p1' y 'p2' los dos Puntos construidos por el constructor sin parametros.
        // Complejidad: O(1)
        Segment(){
            this->p1 = Point();
            this->p2 = Point();
        }

        // Constructor que recibe dos Puntos 'p1_I' y 'p2_I' que son asignados a los Puntos 'p1' y 'p2' del nuevo segmento.
        // Complejidad: O(1)
        Segment(const Point& p1_I, const Point& p2_I){
            this->p1 = p1_I;
            this->p2 = p2_I;
        }

        // Constructor que recibe un segmento como parametro y asigna los valores de 'p1' y 'p2' del segmento recibido como los valores de 'p1' y 'p2' del nuevo segmento.
        // Complejidad: O(1)
        Segment(const Segment& s_I){
            this->p1 = s_I.p1;
            this->p2 = s_I.p2;
        }

        // Metodo que devuelve el 'Point' 'p1' del segmento.
        // Complejidad: O(1)
        Point getP1() const {
            return this->p1;
        }

        // Metodo que devuelve el 'Point' 'p2' del segmento.
        // Complejidad: O(1)
        Point getP2() const {
            return this->p2;
        }
};


// Clase para un poligono.
class Polygon {

    private:
        // Vector<Point> para almacenar los puntos (objetos tipo 'Point') que conforman a un poligono.
        vector<Point> points;

    public:
        // Constructor que recibe un valor int 'n' y un punto inicial tipo 'Point' con nombre 'startPoint' para agregarlo al vector de puntos.
        // Complejidad: O(1)
        Polygon(int n, const Point& startPoint) {
            this->points.push_back(startPoint);
        }

        // Constructor que recibe un valor int 'n' y dos vector<int> 'xs' y 'ys' que reprensentan las coordenadas 'x' y 'y' de 'n' puntos.
        // Complejidad: O(n) ; n = numero de puntos.
        Polygon(int n, vector<int>& xs, vector<int>& ys) {
            for (int i=0; i<n; i++) {
                this->points.push_back(Point(xs[i], ys[i]));
            }
        }

        // Constructor que recibe un valor int 'n' y un vector<Point> 'points' con los puntos del poligono.
        // Complejidad: O(n) ; n = numero de puntos.
        Polygon(int n, vector<Point>& points) {
            this->points = points;
        }

        // Constructor que recibe otro objeto 'Polygon' con nombre 'other' con los puntos del nuevo poligono.
        // Complejidad: O(n) ; n = numero de puntos.
        Polygon(const Polygon& other) {
            this->points = other.points;
        }

        // Metodo que devuelve el vector<Point> 'points' del poligono.
        // Complejidad: O(1)
        vector<Point> getPoints() const {
            return points;
        }

        // Metodo que devuelve un vector<Segment> 'segments' que representan los segmentos del poligono.
        // Complejidad: O(n) ; n = numero de segmentos.
        vector<Segment> getSegments() const {
            vector<Segment> segments;

            const size_t numPoints = this->points.size();
            if (numPoints >= 2) {
                for (size_t i = 0; i < numPoints - 1; ++i) {
                    segments.push_back(Segment(points[i], points[i+1]));
                }
                // Conecta el ultimo punto al primero para cerrar el poligono.
                segments.push_back(Segment(points[numPoints - 1], points[0]));
            }

            return segments;
        }

        // Metodo que devuelve el numero de puntos que conforman al poligono.
        // Complejidad: O(1)
        int getSize() const {
            return this->points.size();
        }
};


// Funciones de uso general ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * Metodo distanceBetweenPoints:
 * Descripción: Calcula la distancia euclidiana entre dos puntos.
 * Entrada: Point 'p1' y Point 'p2'.
 * Salida: Devuelve un 'double' con el valor de la distancia euclidiana entre ambos puntos.
 * Precondición: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondición: Se devuelve un 'double' con el valor de la distancia entre ambos puntos.
 * Complejidad: O(1)
*/
double distanceBetweenPoints(const Point& p1, const Point& p2) {
    double x1 = p1.getX(), y1 = p1.getY();
    double x2 = p2.getX(), y2 = p2.getY();
    double dx = x2 - x1, dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

/*
 * Metodo compareX:
 * Descripción: Compara puntos por sus coordenadas 'x' y en caso de ser necesario por sus coordenadas 'y'.
 * Entrada: Point 'a' y Point 'b'.
 * Salida: Devuelve un 'bool' dependiendo de si el valor de 'x' de ambos puntos es distinto, devuelve 'true' si es menor el valor de 'p1', o 'false si el valor de 'p2' es menor.
 *         En caso de contar con el mismo 'x', se realiza la misma comparacion con los valores de 'y'
 * Precondición: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondición: Se devuelve un valor 'bool' de la comparacion del valor 'x' de 'p1' y 'p2', en caso necesario, tambien con la comparacion del valor de 'y' de ambos puntos.
 * Complejidad: O(1)
*/
bool compareX(const Point& a, const Point& b) {
    if (a.getX() != b.getX()) {
        return a.getX() < b.getX();
    } else {
        return a.getY() < b.getY();
    }
}

/*
 * Metodo compareY:
 * Descripción: Compara puntos por sus coordenadas 'y' y en caso de ser necesario por sus coordenadas 'x'.
 * Entrada: Point 'a' y Point 'b'.
 * Salida: Devuelve un 'bool' dependiendo de si el valor de 'y' de ambos puntos es distinto, devuelve 'true' si es menor el valor de 'p1', o 'false si el valor de 'p2' es menor.
 *         En caso de contar con el mismo 'y', se realiza la misma comparacion con los valores de 'x'
 * Precondición: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondición: Se devuelve un valor 'bool' de la comparacion del valor 'y' de 'p1' y 'p2', en caso necesario, tambien con la comparacion del valor de 'x' de ambos puntos.
 * Complejidad: O(1)
*/
bool compareY(const Point& a, const Point& b) {
    if (a.getX() != b.getX()) {
        return a.getY() < b.getY();
    } else {
        return a.getX() < b.getX();
    }
}

/*
 * Metodo circumcenter:
 * Descripción: Calcula el circumcentro de un triangulo.
 * Entrada: Polygon 'triangle' que cuenta con los puntos de un traigulo valido.
 * Salida: Devuelve un objeto 'Point' con las coordenadas 'x' y 'y' del circumcentro del triangulo.
 * Precondición: Se debe de recibir un objeto 'Polygon' con tres puntos que formen un triangulo valido.
 * Postcondición: Devuelve un objeto 'Point' con las coordenadas 'x' y 'y' del circumcentro del triangulo.
 * Complejidad: O(1)
*/
Point circumcenter(Polygon& triangle) {

    // Se obtienen los puntos del trianglo.
    vector<Point> points = triangle.getPoints();
    Point a = points[0];
    Point b = points[1];
    Point c = points[2];

    // Calcula los puntos medios de AB y BC.
    Point abMidpoint((a.getX() + b.getX()) / 2.0, (a.getY() + b.getY()) / 2.0);
    Point bcMidpoint((b.getX() + c.getX()) / 2.0, (b.getY() + c.getY()) / 2.0);

    // Calcula las pendientes de las lineas que pasan por los segmentos AB y BC.
    // Pendiente perpendicular a AB.
    double abSlope = (b.getX() - a.getX()) / (a.getY() - b.getY());
    // Pendiente perpendicular a BC.
    double bcSlope = (c.getX() - b.getX()) / (b.getY() - c.getY());

    // Calcula la coordenada 'x' del circumcentro usando las pendientes y puntos medios.
    double circumcenterX = (bcMidpoint.getY() - abMidpoint.getY() + abSlope * abMidpoint.getX() - bcSlope * bcMidpoint.getX()) / (abSlope - bcSlope);
    // Calcula la coordenada 'y' del circumcentro usando los puntos medios y la linea que pasa por AB.
    double circumcenterY = abMidpoint.getY() + abSlope * (circumcenterX - abMidpoint.getX());
    
    // Devuelve el circumcentro.
    return Point(circumcenterX, circumcenterY);
}

// Estructura PointHash para hashear un punto 'Point' basado en sus coordenadas 'x' y 'y'.
struct PointHash {
    // Metodo para obtener el hash del punto.
    // Complejidad: O(1)
    std::size_t operator()(const Point& p) const {
        std::hash<double> hasher;
        std::size_t xHash = hasher(p.getX());
        std::size_t yHash = hasher(p.getY());
        return xHash ^ yHash;
    }
};

// Estructura para revisar si dos puntos son iguales.
struct PointEqual {
    // Metodo que revisa si dos puntos 'Point' son iguales.
    // Complejidad: O(1)
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.getX() == p2.getX() && p1.getY() == p2.getY();
    }
};

// Sobrecarga de operador para 2 objetos tipo 'Point' , para saber si sus valores de 'x' y 'y' son iguales.
// Complejidad: O(1)
bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

// Sobrecarga de operador para 2 objetos tipo 'Point' , para saber si sus valores de 'x' y 'y' no son iguales.
// Complejidad: O(1)
bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

// Sobrecarga de operador para 2 objetos tipo 'Polygon' , para saber si todos sus puntos son iguales.
// Complejidad: O(n) ; n = numero de puntos del poligono.
bool operator==(const Polygon& lhs, const Polygon& rhs) {
    const vector<Point>& lhsPoints = lhs.getPoints();
    const vector<Point>& rhsPoints = rhs.getPoints();

    // Compara los puntos.
    return lhsPoints == rhsPoints;
}

// Sobrecarga de operador para 2 objetos tipo 'Segment' , para saber si dos segmentos son el mismo, ya sea en la misma direccion o invertidos.
// Complejidad: O(1)
bool operator==(const Segment& seg1, const Segment& seg2){
  return (seg1.getP1() == seg2.getP1() && seg1.getP2() == seg2.getP2()) || 
         (seg1.getP1() == seg2.getP2() && seg1.getP2() == seg2.getP1());
}

// Sobrecarga de operador para 2 objetos tipo 'Segment' , para saber si dos segmentos no son el mismo, ya sea en la misma direccion o invertidos.
// Complejidad: O(1)
bool operator!=(const Segment& seg1, const Segment& seg2){
  return !((seg1.getP1() == seg2.getP1() && seg1.getP2() == seg2.getP2()) || 
         (seg1.getP1() == seg2.getP2() && seg1.getP2() == seg2.getP1()));
}

/*
 * Metodo findSharedEdges:
 * Descripción: Regresa todas las aristas que comparte un triangulo con una lista con otros triangulos.
 * Entrada: Polygon 'triangle' que representa el triangulo a revisar y vector<Polygon> 'triangleList' que cuenta con los triangulos a comparar.
 * Salida: Devuelve un vector<Segment> con todas las aristas que comparte el triangulo con los otros triangulos.
 * Precondición: Se debe de recibir un objeto Polygon y un vector<Polygon> validos.
 * Postcondición: Se devuelve un vector<Segment> con todas las aristas que comparte el triangulo con los otros triangulos.
 * Complejidad: O(n) ; n = Numero de triangulos en triangleList, ya que el numero de segmentos por triangulo es constante.
*/
vector<Segment> findSharedEdges(const Polygon& triangle, const vector<Polygon>& triangleList) {

    vector<Segment> sharedEdges;

    // Compara cada triangulo.
    for (const Polygon& otherTriangle : triangleList) {
        // En caso de ser el mismo triangulo, lo salta.
        if (triangle == otherTriangle) {
            continue;
        }

        vector<Segment> segments = triangle.getSegments();
        vector<Segment> otherSegments = otherTriangle.getSegments();

        // Revisa si alguno de los segmentos del triangulo se encuentra en los demas segmentos.
        for (const Segment& segment : segments) {
            if (find(otherSegments.begin(), otherSegments.end(), segment) != otherSegments.end()) {
                sharedEdges.push_back(segment);
            }
        }
    }

    return sharedEdges;
}

/*
 * Metodo hasSharedEdge:
 * Descripción: Verifica si dos triangulos comparten una arista.
 * Entrada: Dos objetos tipo Polygon que representan los triangulos a revisar.
 * Salida: Devuelve un valor booleano indicando si los triangulos tienen una arista compartida (true) o no (false).
 * Precondición: Se debe de recibir dos objetos tipo 'Polygon'.
 * Postcondición: Devuelve un valor booleano indicando si los triangulos tienen una arista compartida (true) o no (false).
 * Complejidad: O(1) ; Ya que el numero de segmentos en un triangulo es constante.
*/
bool hasSharedEdge(const Polygon& triangle_a, const Polygon& triangle_b) {

    // Se obtienen los segmentos de los triangulos.
    vector<Segment> segments = triangle_a.getSegments();
    vector<Segment> otherSegments = triangle_b.getSegments();

    // Se revisa si alguno de los segmentos es compartido.
    for (const Segment& segment : segments) {
        if (find(otherSegments.begin(), otherSegments.end(), segment) != otherSegments.end()) {
            return true;
        }
    }
    return false;
}

/* 
 * Metodo isEdgeInTriangles:
 * Descripción: Verifica si un borde dado está presente en una lista de segmentos.
 * Entrada: Segment 'edge' que es el segmento a buscar y vector<Segment> 'segments' que son los segmentos donde se buscara.
 * Salida: Devuelve un valor booleano indicando si el segmento se encuentra en la lista de segmentos (true) o no (false).
 * Precondición: Se debe de recibir un objeto tipo 'Segment' y un vector<Segment> 'segments' validos.
 * Postcondición: Devuelve un valor booleano indicando si el segmento se encuentra en la lista de segmentos (true) o no (false).
 * Complejidad: O(n) ; n = Numero de segmentos en 'segments'.
*/
bool isEdgeInTriangles(const Segment& edge, const vector<Segment>& segments) {
    return find(segments.begin(), segments.end(), edge) != segments.end();
}

/*
 * Metodo orientation:
 * Descripcion: Busca la orientacion del trio de puntos 'p', 'q' y 'r'.
 * Entrada: Point 'p' ; Point 'q' ; Point 'r'.
 * Salida: Devuelve un 'int' que representa la orientacion de los puntos:
 *         0-> p,q,r son colineales ; 1->Sentido de las manecillas del reloj ; 2->Sentido en contra de las manecillas del reloj.
 * Precondicion: Se debe de recibir tres objetos tipo 'Point'.
 * Postcondicion: Se debvolver un 'int' representa la orientacion de los puntos.
 * Complejidad: O(1)
*/
int orientation(Point p, Point q, Point r) {
    
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) - (q.getX() - p.getX()) * (r.getY() - q.getY());

    // Colinealidad.
    if (val == 0){
        return 0;
    }

    // Sentido de las manecillas del reloj.
    if (val > 0){
        return 1;
    }
    
    // Sentido en contra de las manecillas del reloj.
    return 2;
}

/* 
 * Metodo voronoiHull:
 * Descripción: recorre los polígonos en sentido del reloj y agerga los ciclos encontrados al vector de cycles.
 * Entrada: Segment &seg, Segment &start, vector<Segment> connections, unordered_set<int> &set, vector<unordered_set<int>> &cycles, unordered_set<string> verticies, bool passed
 * Salida: No hay
 * Precondición: Se debe den recibir los objetos por referencia.
 * Postcondición: Se modifica por referencia el vector de cycles conteniendo diccionarios de los indices de segmentos que forman un polígono.
 * Complejidad: O(n^2) donde n es la cantidad de segmentos
*/
void voronoiHull (Segment &seg, Segment &start, vector<Segment> connections, unordered_set<int> &set, vector<unordered_set<int>> &cycles, unordered_set<string> verticies, bool passed){

    //si es que estamos llegando al punto inicial una segunda vez
    if (passed && (seg == start)){
        //revisar si ya contamos con el polygono guardado
        for (auto i: cycles){
            //si ya existe, terminar recursión
            if (i == set){
                return;
            }
        }
        //si no existe, agregar a la lista de ciclos
        cycles.push_back(set);
        return;
    }

    //por cada segmento que tenemos
    for (int i = 0; i < connections.size(); i++){
        //mientras que el segmento a revisar actual no sea el inicial
        if (connections[i] != start){
            //si ya contamos con el segmento agregado no volver a procesar
            if (set.find(i) != set.end()) continue;
        }
        
        //si el vertice se encuentra en el punto1 del segmento a analizar y el punto1 del segmento a comparar
        if (connections[i].getP1() == seg.getP1()){
            //conseguir un hash de la tupla del vertice para agregar a un set
            string vertexHash = to_string(seg.getP1().getX()) + "," + to_string(seg.getP1().getY());
            //si la conexión va en sentido del reloj y no ya contmos con el vertice
            if ((orientation(seg.getP2(), seg.getP1(), connections[i].getP2()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                //agregar segmento al set
                set.insert(i);
                //agergar vertice al set
                verticies.insert(vertexHash);
                //recorrer recursivamente comparando el nuevo segmento
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }
        }

        //si el vertice se encuentra en el punto1 del segmento a analizar y el punto2 del segmento a comparar
        if (connections[i].getP1() == seg.getP2()){
            //conseguir un hash de la tupla del vertice para agregar a un set
            string vertexHash = to_string(seg.getP2().getX()) + "," + to_string(seg.getP2().getY());
            //si la conexión va en sentido del reloj y no ya contmos con el vertice
            if ((orientation(seg.getP1(), seg.getP2(), connections[i].getP2()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                //agregar segmento al set
                set.insert(i);
                //agergar vertice al set
                verticies.insert(vertexHash);
                //recorrer recursivamente comparando el nuevo segmento
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }
        }
       
        //si el vertice se encuentra en el punto2 del segmento a analizar y el punto1 del segmento a comparar
        if (connections[i].getP2() == seg.getP1()){
            //conseguir un hash de la tupla del vertice para agregar a un set
            string vertexHash = to_string(seg.getP1().getX()) + "," + to_string(seg.getP1().getY());
            //si la conexión va en sentido del reloj y no ya contmos con el vertice
            if ((orientation(seg.getP2(), seg.getP1(), connections[i].getP1()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                //agregar segmento al set
                set.insert(i);
                //agergar vertice al set
                verticies.insert(vertexHash);
                //recorrer recursivamente comparando el nuevo segmento
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }        
        }

        //si el vertice se encuentra en el punto2 del segmento a analizar y el punto2 del segmento a comparar
        if (connections[i].getP2() == seg.getP2()){
            //conseguir un hash de la tupla del vertice para agregar a un set
            string vertexHash = to_string(seg.getP2().getX()) + "," + to_string(seg.getP2().getY());
            //si la conexión va en sentido del reloj y no ya contmos con el vertice
            if ((orientation(seg.getP1(), seg.getP2(), connections[i].getP1()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                //agregar segmento al set
                set.insert(i);
                //agergar vertice al set
                verticies.insert(vertexHash);
                //recorrer recursivamente comparando el nuevo segmento
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }
        }
    }

    return;
}

/* 
 * Metodo followPath:
 * Descripción: Sigue en sentido de manecillas del reloj un polígono e imprime los puntos.
 * Entrada: pair<float,float> start,pair<float,float> a, pair<float,float> b, pair<float,float> c, vector < pair < pair <float,float> , pair <float,float> > > temp, bool passed.
 * Salida: No hay
 * Precondición: Se debe de recibir los objetos de entrada y temp debe contener las coordenadas de segmentos que forman un poligono.
 * Postcondición: Se imprimen los puntos empezando por la x menor y siguiendo las manecillas del reloj.
 * Complejidad: O(n^2) ; n = Numero de puntos que conforman un poligono.
*/
void followPath(pair<float,float> start,pair<float,float> a, pair<float,float> b, pair<float,float> c, vector < pair < pair <float,float> , pair <float,float> > > temp, bool passed){

    //si es que estamos llegando al punto inicial una segunda vez
    if (passed && a == start){
        //terminar recursion
        return;
    }

    //si es que los ultimos 3 puntos forman dos segmenots en orientacion a manecillas del reloj
    if (orientation(Point(a.first,a.second),Point(b.first,b.second),Point(c.first,c.second)) == 1){
        //imprimir el punto inicial
        cout << round(a.first) << " " << round(a.second) << endl;
        //recorrer los segmentos
        for (auto i: temp){
            //si el segmento comparte un punto con 'c' (el primero)
            if (i.first == c){
                //mandar recursivamente con 'b' inicial, 'c' intermedio y el punto desconocido del segmento (el segundo)
                followPath(start,b,c,i.second,temp,true);
            }
            //si el segmento comparte un punto con 'c' (el segundo)
            if (i.second == c){
                //mandar recursivamente con 'b' inicial, 'c' intermedio y el punto desconocido del segmento (el primero)
                followPath(start,b,c,i.first,temp,true);
            }
        }
        return;
    }
}

/* 
 * Metodo delauntayTriangulation:
 * Descripción: Regresa un vector de tipo polygonos, donde cada polygono es un triangulo, donde todos los triangulos del vector forman la triangulacion de delaunay
 * Entrada: vector<Point>& points
 * Salida: vector<Polygon> triangulosDT
 * Precondición: Se debe obtener los puntos de los cuales se quiere sacar la triangulacion
 * Postcondición: Se obtiene la lista de triangulacion de delaunay listos para ser procesados en voronoi
 * Complejidad: O(n^4) donde n es la cantidad de puntos que se quiere agregar
*/
vector<Polygon> delaunayTriangulation(vector<Point>& points) {
    //Paso 1 (Crear super triangulo).
    sort(points.begin(), points.end(), compareX);
  
    //determinar la corrdenada x del punto que se encuentra mas a la izquierda minx.
    minx = points[0].getX();
    //determinar la coordenada x que se encuentra mas a la derecha maxx.
    maxx = points[points.size()-1].getX();
    //determinar la corrdenada y del puntos que se encuentra mas hacia arriba maxy.
    sort(points.begin(), points.end(), compareY);
    maxy = points[points.size()-1].getY();
    //determinar la coordenada y del punto que se encuentra mas hacia abajo miny.
    miny = points[0].getY();
    //Hay que calcular distx = maxx-minx.
    int distx = maxx - minx;
    //Hay que calcular disty = maxy-miny.
    int disty = maxy - miny;
    //Los vertices del super_triangulo son:
    vector<Point> super = {
        Point(minx-9.5*distx, miny+0.5*disty), 
        Point(minx+5.5*distx, miny+9.16*disty), 
        Point(minx+5.5*distx, miny-8.16*disty)};

    Polygon superTriangle = Polygon(3, super);

    //Paso 2: Crear una estructura triangulos_DT donde se iran guardando los triangulos creados. En esta estructura incluir este primer triangulo.
    vector<Polygon> triangulosDT = {superTriangle};

    //Crear estructura triangulosInvalidos
    vector<Polygon> triangulosInvalidos;
    //Crear estructura ariastasComunes
    vector<Segment> aristasComunes;
    //Crear aristas en triangulos invalidos
    vector<Segment> aristasInvalidas;


    //Paso 3: Hay un punto a agregar? Si si entonces escoger el siguiente puntoAgregar
    Point puntoAgregar, circumcentro;
    double circumradio, distance;
    //BORRAR
    int count = 0;
    while (!points.empty()) {
        //Asignar el valor de puntoAgregar.
        puntoAgregar = points.front();

        triangulosInvalidos.clear();
        aristasComunes.clear();
        aristasInvalidas.clear();
        //Complejidad O(n)
        //Paso 4: Iterar sobre cada triangulosDT.
        for (std::vector<Polygon>::size_type i=0; i<triangulosDT.size(); i++) {
            //Encontrar el circuncentro.
            circumcentro = circumcenter(triangulosDT[i]);
            //Encontrar el circunradio.
            circumradio = distanceBetweenPoints(circumcentro, triangulosDT[i].getPoints()[0]);
            //Determinar distancia entre punto_a_añadir y el circuncentro.
            distance = distanceBetweenPoints(circumcentro, puntoAgregar);
            //Si la distancia es menor que el circunradio, entonces el triangulo actual es invalido.
            if (distance < circumradio) {
                triangulosInvalidos.push_back(triangulosDT[i]);
            } 
        }

        //Paso 5: Hacer puntos_inválidos como un unordered_set.
        unordered_set<Point, PointHash, PointEqual> puntosInvalidos;

        //Obtener las aristas que se comparten entre triangulosInvalidos para paso 7.
        for (auto i: triangulosInvalidos) {
            vector<Segment> elems = findSharedEdges(i, triangulosInvalidos);
            for (int j=0; j<elems.size(); j++) {
                if (!isEdgeInTriangles(elems[j], aristasComunes)) {
                    aristasComunes.push_back(elems[j]);
                }
            }
        }

        //Obtener todas las aristas de cada uno de los triangulos invalidos para paso 7.
        for (auto i: triangulosInvalidos) {
            vector<Segment> segments = i.getSegments();
            for (int j=0; j<3; j++) {
                aristasInvalidas.push_back(segments[j]);
            }
        }

        //Paso 6: Por cada i en triangulosInvalidos.
        for (int i=0; i<triangulosInvalidos.size(); i++) {
            //Para cada vertice v en triangulosInvalidos[i].
            vector<Point> trianguloInvalido = triangulosInvalidos[i].getPoints();
            for (int j=0; j<3; j++) {
                //puntos_inválidos.append(triángulos_inválidos[i][v]) en otras palabras (agregar punto a puntos invalidos).
                Point vertice = trianguloInvalido[j];
                puntosInvalidos.insert(vertice);
            }
            //triángulos_DT.Remover(triángulos_inválidos[i]) -- Todos los triangulos invalidos tienen que quitarse.
            triangulosDT.erase(std::remove(triangulosDT.begin(), triangulosDT.end(), triangulosInvalidos[i]), triangulosDT.end());
        }

        // Paso 7: Por cada punto en puntosInvalidos.
        std::unordered_set<Point, PointHash, PointEqual>::iterator pi;
        std::unordered_set<Point, PointHash, PointEqual>::iterator pj;
        for (pi = puntosInvalidos.begin(); pi != puntosInvalidos.end(); pi++) {
            for (pj = next(pi); pj != puntosInvalidos.end(); pj++) {
                // Siempre y cuando se cumplan las siguientes dos condiciones:
                // Primera condición, la arista (pi,pj) es una arista de alguno de los triángulos en triángulos_inválidos. (aristasInvalidas).
                // Segunda condición, la arista (pi,pj) no se encuentra en aristas_comunes de los triangulos invalidos (aristasComunes).
                if (!isEdgeInTriangles(Segment(*pi,*pj), aristasComunes) && isEdgeInTriangles(Segment(*pi,*pj), aristasInvalidas)) {
                    // Hacer triangulos_DT.append((pi,pj,punto_a_añadir)).
                    vector<Point> newTriangle = {*pi, *pj, puntoAgregar};
                    triangulosDT.push_back(Polygon(3, newTriangle));
                }
            }
        }
        points.erase(points.begin());
    }
    //Paso 8: Si no hay mas puntos, terminar el algoritmo.
    return triangulosDT;
}

/* 
 * Metodo voronoi:
 * Descripción: Calcula el diagrama de Voronoi para un conjunto de puntos dados.
 * Entrada: vector<Point> 'points que cuenta con los puntos que seran usados para calcular los poligonos de Voronoi.
 * Salida: Imprime los puntos de los poligonos validos de Voronoi ordenados de forma ascendente con respecto al valor minimo de 'x' de cada poligono. Luego cada poligono es impreso en sentido de las manecillas del reloj.
 * Precondición: Se debe de recibir un vector<Point> con los puntos para formar el diagrama de Voronoi.
 * Postcondición: Imprime los puntos de los poligonos validos de Voronoi ordenados de forma ascendente con respecto al valor minimo de 'x' de cada poligono. Luego cada poligono es impreso en sentido de las manecillas del reloj.
 * Complejidad: O(n^4) ; n = Numero de puntos.
*/
void voronoi(vector<Point>& points) {

    // Se calcula la triangulacion de Delaunay.
    vector<Polygon> delaunay = delaunayTriangulation(points);
    vector< pair<Point, Polygon> > triangles;

    vector<Segment> connections;

    // Se obtienen los circumcentros de los triangulos de Delaunay.
    for (auto i: delaunay) {
        triangles.push_back(std::make_pair(circumcenter(i),i));
    }

    // Se obtienen las aristas que son compartidas por los circumcentros.
    for (int i = 0; i < triangles.size(); i++){
        // Se revisa si los puntos se encuentran dentro del rectangulo delimitado.
        if (triangles[i].first.getX() > maxx || triangles[i].first.getX() < minx || triangles[i].first.getY() > maxy || triangles[i].first.getY() < miny){
            continue;
        }
        for (int j = i+1; j < triangles.size(); j++){
            if (triangles[j].first.getX() > maxx || triangles[j].first.getX() < minx || triangles[j].first.getY() > maxy || triangles[j].first.getY() < miny){
            continue;
            }
            if (hasSharedEdge(triangles[i].second,triangles[j].second)){
                connections.push_back(Segment(triangles[i].first,triangles[j].first));
            }
        }
    }

    vector<unordered_set<int>> cycles;
    unordered_set<int> tempCycle;
    unordered_set<string> verticies;

    // Se obtienen los poligonos validos.
    for (int i = 0; i < connections.size(); i++){
        tempCycle.insert(i);
        voronoiHull(connections[i],connections[i], connections,tempCycle,cycles,verticies,false);
        tempCycle.clear();
    }

    vector< vector < pair < pair <float,float> , pair <float,float> > > > result;
    vector < pair <float, int> > ordenarResult;
    vector < pair < pair <float,float> , pair <float,float> > > temp;

    // Se obtienen las conexiones de los poligonos.
    for (auto i : cycles){
        for (auto itr = i.begin(); itr != i.end(); ++itr){
            temp.push_back(make_pair( make_pair(connections[*itr].getP1().getX(),connections[*itr].getP1().getY()) , make_pair(connections[*itr].getP2().getX(),connections[*itr].getP2().getY())));
        }
        result.push_back(temp);
        temp.clear();
    }
    
    // Se obtiene la coordenada 'x' minima de cada poligono.
    float tempMinX = 0;
    for (int i = result.size()-1; i >= 0; i--){
        tempMinX = result[i][0].first.first;
        for (int j = 0; j < result[i].size(); j++){
            if (result[i][j].first.first < tempMinX){
                tempMinX = result[i][j].first.first;
            }
            if (result[i][j].second.first < tempMinX){
                tempMinX = result[i][j].second.first;
            }
        }
        ordenarResult.push_back(make_pair(tempMinX, i));
    }

    // Se ordenan los poligonos basados en la coordenada minima de 'x'.
    sort(ordenarResult.begin(), ordenarResult.end());
    
    vector< vector < pair < pair <float,float> , pair <float,float> > > > resultTemp(ordenarResult.size());
    
    // Se ordenan en un arreglo.
    int counter1 = 0;
    for(auto i : ordenarResult){
        resultTemp[counter1] = result[i.second];
        counter1++;
    }

    bool foundFirst = false;
    pair<float,float> lowestX;
    pair<float,float> contra;
    pair<float,float> contra2;
    pair<float,float> third;
    pair<float,float> thrid2;

    // Se busca el camino de cada poligono para ser recorrido en sentido a favor de las manecillas del reloj con respecto al punto con el menor 'x'.
    int counter = 1;
    for (auto i : resultTemp){
        cout << -4 << counter << endl;

        lowestX = i[0].first;
        foundFirst = false;

        for (auto j : i){
            if (j.first.first <= lowestX.first){
                    lowestX = j.first;
                    contra = j.second;
            }
            if (j.second.first <= lowestX.first){
                    lowestX = j.second;
                    contra = j.first;
            }
        }


        for (auto j : i){
            if (j.first.first == lowestX.first){
                if (!foundFirst){
                    contra = j.second;
                    foundFirst = true;
                } else {
                    contra2 = j.second;
                }
            }
            if (j.second.first == lowestX.first){
                if (!foundFirst){
                    contra = j.first;
                    foundFirst = true;
                } else {
                    contra2 = j.first;
                }
            }
        }

        // Se busca el camino que satisface el recorrido en sentido de las manecillas y se imprime.
        for (auto j : i){
            if (j.first == contra && j.second != lowestX){
                followPath(lowestX,lowestX,contra,j.second,i,false);
            }
            if (j.second == contra && j.first != lowestX){
                followPath(lowestX,lowestX,contra,j.first,i,false);
            }
            if (j.first == contra2 && j.second != lowestX){
                followPath(lowestX,lowestX,contra2,j.second,i,false);
            }
            if (j.second == contra2 && j.first != lowestX){
                followPath(lowestX,lowestX,contra2,j.first,i,false);
            }
        }
        counter++;
        
    }
    
}

// Procesamiento ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Estructura para almacenar todos los datos recibidos y los resultados de cada parte.
struct Datos {

    // Variable int 'N' que indica la cantidad de nodos.
    int N;
    // Objeto GrafoKruskal 'pesos' para almacenar los pesos del grafo para obtener el Minimum Expansion Tree.
    GrafoKruskal pesos;
    // vector<vector<int> > 'distancias' para almacenar las distancias del grafo para obtener la solucion al Travelling Salesman Problem (TSP).
    vector<vector<int> >distancias;
    // Objeto GraphFlow 'flujos' para almacenar las capacidad maximas del grafo dirigido para obtener el Flujo Maximo entre un nodo i y un nodo j.
    GraphFlow flujos;
    // vector<Point> 'points' para almacenar los puntos que seran utilizados para generar los poligonos de Voronoi.
    vector<Point> points;

    // Constructor que recibe un valor int '_N' que representa el numero de nodos.
    // Complejidad: O(n^2) ; n = numero de nodos.
    Datos(int _N){
        // Se almacena el numero 'N' de nodos recibido como parametro.
        this->N = _N;
        // Se inicializa 'pesos' con tamaño 'N'.
        pesos = GrafoKruskal(N);
        // Se inicializa 'distancias' con tamaño 'N'.
        distancias = vector<vector<int> >(N, vector<int>(N));
        // Se inicializa 'flujos' con tamaño 'N'.
        flujos = GraphFlow(N);
        // Se inicializa 'points' con tamaño 'N'.
        points = vector<Point>(N);
    }
};

/*
 * Método getFileText:
 * Descripción: Obtiene la matriz (NxN) de adyacencia de un grafo ponderado, la matriz(NxN) de capacidad maxima de transmision de datos y un numero 'N' de puntos(x y) que representan centrales.
 * Entrada: Se realiza por entrada redirecccionada por ambiente de linux.
 * Salida: Devuelve una estructura 'Datos'.
 * Precondición: Realizar la entrada redireccionada con un archivo o valores validos.
 * Postcondición: Devuelve una estructura 'Datos'.
 * Complejidad: O(n^2) ; n = numero de colonias.
*/
Datos getFileText(){

    // Se inicializa la variable 'N' para almacenar las dimensiones del arreglo.
    int N = 0;

    // Se obtienen las dimensiones (NxN) y se almacenan.
    cin >> N;
    //inicializar Datos.
    Datos datos(N);


    // Se obtiene la matriz de tamaño NxN que representa el grafo con las distancias en kilometros entre las colonias de la ciudad.
    for (int i = 0; i < N; i++){
        for (int j=0; j < N; j++){
            int val = 0;
            cin >> val;
            // Se agrega la arista al objeto tipo 'GrafoKruskal' con nombre 'pesos'.
            datos.pesos.AgregarArista(i, j, val);
            // Se agrega la arista al vector<vector<int> > con nombre 'distancias'.
            datos.distancias[i][j] = val;

        }
    }

    // Se obtiene la matriz de tamaño NxN que representa las capacidades maximas de flujo de datos entre colonia i y colonia j.
    for (int i = 0; i < N; i++){
        // Se separan y obtienen los valores de la matriz.
        for (int j=0; j < N; j++){
          int val = 0;
          cin >> val;
          // Se agrega la arista al objeto tipo 'GraphFlow' con nombre 'flujos' cuando existe una conexion en el grafo dirigido.
          if (val != 0)
            datos.flujos.addEdgeFlow(i, j, val);
        }
    }

    // Se inicializa la variable 'tempX' para almacenar temporalmente al valor 'x' de cada punto.
    int tempX = 0;
    // Se inicializa la variable 'tempY' para almacenar temporalmente al valor 'y' de cada punto.
    int tempY = 0;

    // Se obtiene la lista de 'N' pares ordenados que representan la ubicacion en un plano coordenado de las 'N' centrales.
    for (int i = 0; i < N; i++){
        cin >> tempX;
        cin >> tempY;
        // Se agrega el punto al vector<Point> con nombre 'points'.
        datos.points[i].setX(tempX);
        datos.points[i].setY(tempY);
    }

    // Se devuelve una estructura tipo 'Datos' con los datos recibidos del archivo.    
    return datos;

}

/*
 * Método getResults:
 * Descripción: Recibe una estructura tipo 'Datos' con nombre 'datos', calcula e imprime los resultados de Kruskal, TSP, Flujo Maximo y Voronoi.
 * Entrada: Estructura tipo 'Datos' con nombre 'datos'.
 * Salida: Imprime los resultados de Kruskal, TSP, Flujo Maximo y Voronoi.
 * Precondición: Una estructura 'Datos' valida para realizar dichos calculos.
 * Postcondición: Imprime los resultados de Kruskal, TSP, Flujo Maximo y Voronoi.
 * Complejidad: O(n) ; CHECAR
*/
void getResults(Datos datos){

    // Se calculan e imprimen los resultados de Kruskal.
    // Complejidad: O(E log(E)) ; E = Numero de Aristas.
    cout << -1 << endl;
    datos.pesos.Kruskal();

    // Se calculan e imprimen los resultados de TSP desde el nodo origen (0).
    // Complejidad: (n!) ; n = Numero de nodos.
    cout << -2 << endl;
    cout << travellingSalesmanProblem(datos.distancias, 0) << endl;

    // Se calculan e imprimen los resultados de Flujo Maximo del nodo origen (0) al nodo destino (9).
    // Complejidad: O(EV^2) ; V = Numero de Vertices ; E = Numero de Aristas.
    cout << -3 << endl;
    cout << datos.flujos.DinicMaxflow(0,9) << endl;

    // Se calculan e imprimen los resultados de Voronoi.
    // Complejidad: O(n^4) ; n = Numero de puntos.
    cout << -4 << endl;
    voronoi(datos.points);

}

// Inicio del main.
int main(){

    // Se obtienen los datos por entrada redireccionada de linux.
    Datos datosObtenidos = getFileText();

    // Se calculan y despliegan los resultados para el cableado, la ruta a seguir por el personal de correspondencia, el flujo maximo del nodo inicial (0) al nodo final (9) y los poligonos de Voronoi validos.
    getResults(datosObtenidos);

    return 0;
}