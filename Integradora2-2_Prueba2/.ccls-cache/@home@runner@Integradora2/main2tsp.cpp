// g++ -o a.out main2tsp.cpp
// ./a.out < test01tsp.txt
// Travelling Salesman Problem
// TSP con Branch & Bound

#include <iostream>
#include <climits>
#include <queue>
#include <vector>

#define MAX 21

using namespace std;

struct Nodo {
    int niv;             // Nivel del nodo dentro del árbol de búsq. soluciones
    int costoAcum;       // Costo Acumulado hasta ese punto
    int costoPos;        // Costo Posible de esa trayectoria
    int verticeAnterior;
    int verticeActual;
    bool visitados[MAX] = { false };
    vector<int> path;    // Path hasta este punto
    bool operator<(const Nodo& otro) const { // Para que la fila priorizada tenga priodad
        return costoPos >= otro.costoPos;     // Costo Posible menor.
    }
};

void calculaCostoPosible(Nodo& nodoActual, int matAdj[MAX][MAX], int n) {
    nodoActual.costoPos = nodoActual.costoAcum;
    int costoObtenido;
    for (int i = 1; i <= n; i++) {
        costoObtenido = INT_MAX;
        if (!nodoActual.visitados[i] || i == nodoActual.verticeActual) {
            if (!nodoActual.visitados[i]) { // Al nodo i no lo he visitado
                for (int j = 1; j <= n; j++) {
                    if (i != j && (!nodoActual.visitados[j] || j == 1)) {
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            }
            else { // El nodo i es el último visitado
                for (int j = 1; j <= n; j++) {
                    if (!nodoActual.visitados[j]) {
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            }
        }
        if (costoObtenido == INT_MAX) {
            nodoActual.costoPos = INT_MAX;
        }
        else {
            nodoActual.costoPos += costoObtenido;
        }
    }
}

// Complejidad: O(2^n)
int tsp(int matAdj[MAX][MAX], int n, vector<int>& optimalPath, int startNode) {
    int costoOptimo = INT_MAX;
    Nodo raiz;
    raiz.niv = 0;
    raiz.costoAcum = 0;
    raiz.verticeActual = startNode;
    raiz.verticeAnterior = 0;
    raiz.visitados[startNode] = true;
    raiz.path.push_back(startNode);
    calculaCostoPosible(raiz, matAdj, n);
    priority_queue<Nodo> pq;
    pq.push(raiz);
    while (!pq.empty()) {
        Nodo nodoActual = pq.top();
        pq.pop();
        if (nodoActual.costoPos >= costoOptimo) {
            continue;
        }
        if (nodoActual.niv == n - 2) {
            for (int i = 2; i <= n; i++) {
                if (!nodoActual.visitados[i]) {
                    int currentCost = nodoActual.costoAcum + matAdj[nodoActual.verticeActual][i] + matAdj[i][startNode];
                    if (currentCost < costoOptimo) {
                        costoOptimo = currentCost;
                        optimalPath = nodoActual.path;
                        optimalPath.push_back(i);
                        optimalPath.push_back(startNode);
                    }
                    break;
                }
            }
            continue;
        }
        for (int i = 2; i <= n; i++) {
            if (!nodoActual.visitados[i]) {
                Nodo nuevoNodo = nodoActual;
                nuevoNodo.niv = nodoActual.niv + 1;
                nuevoNodo.verticeActual = i;
                nuevoNodo.visitados[i] = true;
                nuevoNodo.path.push_back(i);
                nuevoNodo.costoAcum = nodoActual.costoAcum + matAdj[nodoActual.verticeActual][i];
                calculaCostoPosible(nuevoNodo, matAdj, n);
                if (nuevoNodo.costoPos < costoOptimo) {
                    pq.push(nuevoNodo);
                }
            }
        }
    }
    return costoOptimo;
}

void iniciaMat(int matAdj[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        matAdj[i][i] = 0;
        for (int j = i + 1; j < MAX; j++) {
            matAdj[i][j] = matAdj[j][i] = INT_MAX;
        }
    }
}

void leeArcos(int matAdj[MAX][MAX], int m) {
    char a, b; // Las concexiones
    int c;     // El costo de la conexión
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        matAdj[a - 'A' + 1][b - 'A' + 1] = matAdj[b - 'A' + 1][a - 'A' + 1] = c;
    }
}

void printOptimalPath(const vector<int>& optimalPath) {
    cout << "Optimal Path: ";
    for (int i = 0; i < optimalPath.size(); i++) {
        cout << static_cast<char>('A' + optimalPath[i] - 1);
        if (i < optimalPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main() {
    // n = Cantidad de Nodos
    // m = Cantidad de Arcos
    int n, m;
    cin >> n >> m;
    int matAdj[MAX][MAX];
    iniciaMat(matAdj);
    leeArcos(matAdj, m);
    char startNode;
    cin >> startNode;
    vector<int> optimalPath;
    int optimalCost = tsp(matAdj, n, optimalPath, startNode - 'A' + 1);
    cout << "Optimal Cost: " << optimalCost << endl;
    printOptimalPath(optimalPath);
    return 0;
}

// A B C D E F G H I J
// 0 1 2 3 4 5 6 7 8

// Profe:
// 0 5 3 2 7 9 4 1 6 8 0
// 104 100 488 196 259 175 162 228 112 1

//Algo
// 0 8 3 5 2 7 4 1 6 9 0