// g++ -o a.out maintsp.cpp
// ./a.out < test01tsp.txt
// Travelling Saleman Problem
// TSP con Branch & Bound

#include <iostream>
#include <climits>
#include <queue>

#define MAX 21

using namespace std;

struct Nodo {
    int niv;            // Nivel del nodo dentro del árbol de búsq. soluciones
    int costoAcum;      // Costo Acumulado hasta ese punto
    int costoPos;       // Costo Posible de esa trayectoria
    int verticeAnterior;
    int verticeActual;
    bool visitados[MAX] = { false };
    bool operator<(const Nodo& otro) const {    // Para que la fila priorizada tenga priodad
        return costoPos > otro.costoPos;        // Costo Posible mayor.
    }
};

void calculaCostoPosible(Nodo& nodoActual, int matAdj[MAX][MAX], int n) {
    nodoActual.costoPos = nodoActual.costoAcum;
    int costoObtenido;
    for (int i = 1; i <= n; i++) {
        costoObtenido = INT_MAX;
        if (!nodoActual.visitados[i] || i == nodoActual.verticeActual) {
            if (!nodoActual.visitados[i]) {
                for (int j = 1; j <= n; j++) {
                    if (i != j && (!nodoActual.visitados[j] || j == 1)) {
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            }
            else {
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
int tsp(int matAdj[MAX][MAX], int n) {
    int costoOptimo = INT_MAX;
    Nodo raiz;
    raiz.niv = 0;
    raiz.costoAcum = 0;
    raiz.verticeActual = 1;
    raiz.verticeAnterior = 0;
    raiz.visitados[1] = true;
    calculaCostoPosible(raiz, matAdj, n);
    priority_queue<Nodo> pq;
    pq.push(raiz);
    while (!pq.empty()) {
        Nodo nodoActual = pq.top();
        pq.pop();
        if (nodoActual.costoPos < costoOptimo) {
            if (nodoActual.niv == n - 2) {
                for (int i = 2; i <= n; i++) {
                    if (!nodoActual.visitados[i]) {
                        int costo = nodoActual.costoAcum + matAdj[nodoActual.verticeActual][i] + matAdj[i][1];
                        costoOptimo = min(costoOptimo, costo);
                    }
                }
            }
            else {
                for (int i = 2; i <= n; i++) {
                    if (!nodoActual.visitados[i]) {
                        Nodo nuevoNodo;
                        nuevoNodo.niv = nodoActual.niv + 1;
                        nuevoNodo.costoAcum = nodoActual.costoAcum + matAdj[nodoActual.verticeActual][i];
                        nuevoNodo.verticeActual = i;
                        nuevoNodo.verticeAnterior = nodoActual.verticeActual;
                        for (int j = 1; j <= n; j++) {
                            nuevoNodo.visitados[j] = nodoActual.visitados[j];
                        }
                        nuevoNodo.visitados[i] = true;
                        calculaCostoPosible(nuevoNodo, matAdj, n);
                        if (nuevoNodo.costoPos < costoOptimo) {
                            pq.push(nuevoNodo);
                        }
                    }
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
    char a, b;    // Las concexiones
    int  c;       // El costo de la conexión
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        matAdj[a - 'A' + 1][b - 'A' + 1] = matAdj[b - 'A' + 1][a - 'A' + 1] = c;
    }
}

int main() {
    // n = Cantidad de Nodos
    // m = Cantidad de Arcos
    int n, m;
    cin >> n >> m;
    int matAdj[MAX][MAX];
    iniciaMat(matAdj);
    leeArcos(matAdj, m);
    cout << tsp(matAdj, n) << endl;
    return 0;
}