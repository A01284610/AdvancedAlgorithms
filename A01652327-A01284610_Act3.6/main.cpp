/*
* Fecha: 27 Abril 2023
* Autores:
*   Matricula: A01652327
*   Nombre: Diego Esparza Hurtado
*
*   Matricula: A01284610
*   Nombre: Alejandro Lizarraga Vizcarra
*
* Actividad 3.6 Implementacion de "Graph Coloring"
*
*   CAMBIAR
*    En el programa se busca el arbol de busqueda binaria optimo (BSTOp) que minimice el tiempo promedio de busqueda de 'n' nodos.
*    Para esto se utiliza la implementacion del algoritmo de Gilbert and Moore, donde se leen 'n' probabilidades, cuya suma de todas debe ser 1.
*       El programa imprime todas las relaciones padre-hijo de los nodos pertenecientes al BSTOp.
*       Finalmente, imprime la el minimo tiempo promedio de busqueda posible con las probabilidades y nodos proporcionados.
*
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
#include <unordered_set>
#include <queue>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;
using std::string;
using std::getline;
using std::pair;
using std::make_pair;
using std::sort;
using std::greater;
using std::stack;
using std::queue;

// Se obtiene el vector con los numeros de nodo ordenados de manera descendiente por cantidad de aristas.
    // En caso de contar con el mismo numero de aristas, se ordenan de manera ascendente los valores de los nodos.


/*
 * Método ordenarNodosGrado:
 * Descripción: Ordena los numeros de nodos de manera descendiente por la cantidad de aristas.
 * Entrada: vector<pair<int,int> > 'numeroAristasPorNodo' con pares donde el primer valor representa la cantidad de aristas y el segundo el numero de nodo.
 * Salida: Devuelve un vector<int> 'vect' con los numeros de nodo ordenados de manera descendiente por la cantidad de aristas.
 *         En caso de que dos o mas nodos cuenten con la misma cantidad de aristas, los ordena de manera ascendente entre ellos.
 * Precondición: Se recibe un vector<pair<int,int> > 'numeroAristasPorNodo' con pares donde el primer valor representa la cantidad de aristas y el segundo el numero de nodo.
 * Postcondición: Devuelve un vector<int> 'vect' con los numeros de nodo ordenados de manera descendiente por la cantidad de aristas.
 * Complejidad: O(n log(n)).
 *      n = numero de nodos.
*/
vector<int> ordenarNodosGrado(vector<pair<int,int> > numeroAristasPorNodo){

    // Obtiene el numero de nodos.
    int n = numeroAristasPorNodo.size();

    // Genera un vector<int> 'vect' de tamaño 'n' para almacenar los nodos en orden descendiente por la cantidad de aristas.
    vector<int> vect(n);
    // Se genera un stack de pares 'stack' auxiliar para invertir el orden de los nodos cuando cuentan con la misma cantidad de aristas.
    stack <pair<int,int> > stack;
    // Se genera un queue de pares 'queue' auxiliar para almacenar el orden final descendiente de los nodos. Este queue almacenara tambien los nodos con mismo numero de aristas en orden ascendente.
    queue <pair<int,int> > queue;

    // Se ordena el vector 'numeroAristasPorNodo' de manera descendiente con respecto al numero de aristas.
    // Los nodos con la misma cantidad de aristas se encuentran ordenados de manera descendiente.
    sort(numeroAristasPorNodo.begin(), numeroAristasPorNodo.end(), greater<pair<int,int> >()); 

    // Entero 'tamp_val' que almacena el numero de aristas mas grande hasta el momento para buscar si algun otro nodo cuenta con ese mismo.
    int temp_val = numeroAristasPorNodo[0].first;

    // Ordena todos los nodos de manera descendiente por numero de aristas.
    // En caso de haber dos o mas nodos con el mismo numero de aristas, se ordenan de manera ascendente.
    for (int i = 0; i < n; i++){
        // En caso de que haya mas de un nodo con el mismo numero de aristas, se almacenan en un stack.
        if (numeroAristasPorNodo[i].first == temp_val){
            stack.push(numeroAristasPorNodo[i]);
        }
        // En caso de que ya no haya mas nodos con el mismo numero de aristas.
        else{
            // Se vacia el stack y se almacenan en el queue.
            while (!stack.empty()){
                queue.push(stack.top());
                stack.pop();
            }
            // Se almacena en el stack el nodo actual y el valor de 'temp_val' se vuelve el numero de aristas nuevo.
            temp_val = numeroAristasPorNodo[i].first;
            stack.push(numeroAristasPorNodo[i]);
        }
    }

    // Se vacia el stack y agregan al queue los nodos con el numero de aristas mas bajo.
    while (!stack.empty()){
        queue.push(stack.top());
        stack.pop();
    }

    // Se almacenan los nodos ordenados en el vector 'vect' y se vacia el queue.
    for (int i = 0; i < n; i++){
        vect[i] = queue.front().second;
        queue.pop();
    }

    // Se devuelve el vector con los nodos ordenados.
    return vect;

}


/* CAMBIAR
 * Método colorGraph:
 * Descripción: Imprime cada una de las relaciones padre-hijo de los nodos pertenecientes al BTSOp.
 * Entrada: vector<vector<int> > 'vect' 
 *          vector<int> 'ordenPorGrado'
 * Salida: Imprime cada una de las relaciones padre-hijo desde el nodo raiz recibido.
 * Precondición: Se recibe un vector<vector<int> > 'K' obtenido con el algoritmo Gilbert and Moore, asi como los valores int 'i' e int 'j' adecuados.
 * Postcondición: Imprime cada una de las relaciones padre-hijo desde el nodo raiz recibido.
 * Complejidad: O(n^3).
 *      n = numero de nodos.
*/
void colorGraph(vector<vector<int> > vect, vector<int> ordenPorGrado){
    
    //
    int colNum = 0;
    //
    int n = vect.size();

    //
    vector<int> colored(n, 0);

    //
    for (int it = 0; it < n; it++){
        int i = ordenPorGrado[it];
        if (!colored[i]){
            if (colNum != 0){}
            colored[i] = ++colNum;
            unordered_set<int> conj;
            for (int it2 = it+1; it2 < n; it2++){
                int j = ordenPorGrado[it2];
                if(!colored[j] && !vect[i][j]){
                    int cia = 0;
                    for (auto ia : conj){
                        if (vect[ia][j]){
                            cia++;
                        }
                    }
                    if (!cia){
                        colored[j] = colNum;
                        conj.insert(j);
                    }
                }
            }
        }
    }

    // Se imprime el numero de nodo, asi como el numero de color que se le asigno.
    for (int idx = 0; idx < n; idx++){
        cout << "Node: " << idx << ", Assigned Color: " << colored[idx]-1 << endl;
    }
}

// Inicio del main().
int main(){

    // Se obtienen los inputs:
    std::istream& in = cin;

    // Se inicializa la variable 'N' para almacenar las dimensiones del arreglo.
    int N = 0;

    // Se obtienen las dimensiones (NxN) y se almacenan.
    cin >> N;

    // Se inicializa un vector de vectores 'vect' con valores tipo 'int'.
    vector<vector<int> > vect;

    // Se inicializa un vector de pares de enteros 'ordenPorGrado' de tamaño 'N'.
    // Se almacenan 
    vector<pair<int,int> > numeroAristasPorNodo(N);

    // Se almacena en el segundo valor de cada par el valor del nodo al que pertenece.
    for (int i = 0; i < N; i++){
        numeroAristasPorNodo[i].second = i;
    }

    string S;
    getline(cin, S);

    // Se inicializa variable string 'myText' que sera utilizada para obtener las N lineas y sus N valores. 
    string myText;
    // Se obtienen las N lineas.
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

            // Se almacena el valor obtenido en el vector 'temp_vect'.
            temp_vect.push_back(stoi(val));

            // En caso de que haya una conexion desde el nodo 'j', se agrega al contador del vector 'numeroAristasPorNodo'.
            if (stoi(val) == 1){
                numeroAristasPorNodo[j].first++;
            }
            
        }

        // Se hace un push al vector 'vect' (tamaño NxN) del vector temporal 'temp_vect' (tamaño N)
        vect.push_back(temp_vect);
        // Se limpia el vector 'temp_vect' para reutilizarlo.
        temp_vect.clear();
    }

    // Se obtiene el vector con los numeros de nodo ordenados de manera descendiente por cantidad de aristas.
    // En caso de contar con el mismo numero de aristas, se ordenan de manera ascendente los valores de los nodos.
    vector<int> ordenPorGrado = ordenarNodosGrado(numeroAristasPorNodo);

    // Se obtienen los resultados del coloreo del grafo a traves del metodo 'colorGraph'.
    colorGraph(vect, ordenPorGrado);

    return 0;

}