/*
 * Fecha: 25 Mayo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 4.3 - Implementacion Poligonos Convexos aplicando geometria computacional
 *    En el programa se hace uso de una estructura 'Point' para almacenar cada punto que se recibe.
 *    Se reciben 'n' puntos (cada uno con su respectivo 'x' y 'y'), uno por linea.
 * 
 *    Se busca encontrar el poligono convexo mas pequeño en el conjunto de puntos recibidos aplicando el algoritmo de Graham's Scan.
 *    Se devuelve un arreglo de puntos (vertices) en orden contrario al sentido de las manecillas del reloj que definen el poligono convexo, empezando con el punto que tiene la coordenada y mas pequeña.
 *
 * Para compilar: 
 * g++ -o a.out a01652327main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
 * 
 * Referencia:
 *      https://www.geeksforgeeks.org/convex-hull-using-graham-scan/
*/

#include <iostream>
#include <stack>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::stack;
 

// Estructura para un punto.
struct Point {
    // Variable de tipo 'int' para el valor 'x' del punto.
    int x;
    // Variable de tipo 'int' para el valor 'y' del punto.
    int y;
};


// Punto global para usar como referencia para ordenar el resto con el uso de qsort()
Point p0;
 

/*
 * Metodo nextToTop:
 * Descripcion: Encuentra el siguiente elemento al top de un stack.
 * Entrada: Stack<Point> 'S'.
 * Salida: Devuelve un 'Point' que representa el siguiente elemento al top de un stack.
 * Precondicion: Se debe de recibir un stack<Point> con al menos dos elementos 'Point'.
 * Postcondicion: Se debe devolver un 'Point' que representa el siguiente elemento al top de un stack.
 * Complejidad: O(1)
*/
Point nextToTop(stack<Point> &S) {
    // Se recupera y almacena en Point 'p' el top del stack para volverlo a meter luego.
    Point p = S.top();
    // Se saca el top del stack para poder recuperar el siguiente elemento.
    S.pop();
    // Se obtiene y almacena en Point 'res' el siguiente elemento al top original.
    Point res = S.top();
    // Se regresa al stack el Point 'p' que era el top original.
    S.push(p);
    // Se regresa el siguiente elemento al top del stack.
    return res;
}
 
/*
 * Metodo swap:
 * Descripcion: Intercambia dos puntos que recibe.
 * Entrada: Point 'p1' y Point 'p2'.
 * Salida: No cuenta con salida.
 * Precondicion: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondicion: Se debe de contar con los dos puntos intercambiados entre ellos.
 * Complejidad: O(1)
*/
void swap(Point &p1, Point &p2) {
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}
 

/*
 * Metodo distSq:
 * Descripcion: Devuelve el cuadrado de la distancia entre dos puntos recibidos.
 * Entrada: Point 'p1' y Point 'p2'.
 * Salida: Devuelve un 'int' con el valor del cuadrado de la distancia entre ambos puntos.
 * Precondicion: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondicion: Se debe devolver un 'int' con el valor del cuadrado de la distancia entre ambos puntos.
 * Complejidad: O(1)
*/
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
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
    
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

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

    // Checar si es lo mismo.
    //return (val > 0)? 1: 2; // clock or counterclock wise
}


/*
 * Metodo compare:
 * Descripcion: Funcion usada para ordenar con 'qsort()' el arreglo de puntos con respecto al primer punto.
 * Entrada: const void *'vp1' y const void *'vp2'.
 * Salida: Devuelve un 'int' con valor '1' o '-1' dependiendo del orden a seguir.
 * Precondicion: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondicion: Devuelve un 'int' con valor '1' o '-1' dependiendo del orden a seguir.
 * Complejidad: O(1)
*/
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    
    // Se encuentra la orientacion.
    int o = orientation(p0, *p1, *p2);

    // Si se encuentran los tres puntos en la misma linea (colinealidad).
    if (o == 0){
        if (distSq(p0, *p2) >= distSq(p0, *p1)){
            return -1;
        }
        return 1;
    }
    // En caso de que no haya colinealidad.
    else {
        // En caso de que el sentido del angulo sea en contra de las manecillas del reloj.
        if (o == 2){
            return -1;
        }
        // En caso de que el sentido del angulo sea en sentido de las manecillas del reloj.
        return 1;
    }

    // Checar si es lo mismo.
    //if (o == 0){
    //    return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    //}
    
    //return (o == 2)? -1: 1;
}


/* 
 * Metodo convexHull:
 * Descripcion: Devuelve el set de los 'm' puntos del poligono convexo.
 * Entrada: Point 'points'[] que almacena los puntos de los cuales se quiere obtener el poligono convexo ;
 *          int 'n' que representa la cantidad de puntos de los cuales se quiere obtener el poligono convexo.
 * Salida: Imprime los valores de 'x' y 'y' de los 'm' puntos que conforman el poligono convexo.
 *         en orden contrario al sentido de las manecillas del reloj que definen el poligono convexo, empezando con el punto que tiene la coordenada y mas pequeña.
 * Precondicion: Se debe de recibir el arreglo de objetos tipo 'Point' y el valor 'n' que representa el numero de puntos.
 * Postcondicion: Imprime los valores de 'x' y 'y' de los 'm' puntos que conforman el poligono convexo.
 *                en orden contrario al sentido de las manecillas del reloj que definen el poligono convexo, empezando con el punto que tiene la coordenada y mas pequeña.
 * Complejidad: O(n log(n)) ; n = numero de puntos.
*/
void convexHull(Point points[], int n) {
    
    // Encontrar el punto con el valor de 'y' minimo.
    int ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        // Se toma el punto de hasta abajo o el de la izquierda en caso de contar con dos o mas puntos con el valor de 'y' minimo.
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }
    
    // Se pone el punto con el valor menor de 'y' en la primera posicion del arreglo.
    swap(points[0], points[min]);
    
    // Se ordenan el resto de puntos (n-1) con respecto al primer punto 'p0'.
    p0 = points[0];
    // Un punto 'p1' esta antes de 'p2' si su angulo en sentido opuesto a las manecillas del reloj es menor que el de 'p2' con respecto a p0 y el eje horizontal.
    qsort(&points[1], n-1, sizeof(Point), compare);

    // Variable int 'm' que se inicializa con el tamaño del arreglo modificado.
    // En caso de que dos o mas puntos tengan el mismo angulo con 'p0', se eliminan todos menos el mas lejano a 'p0'.
    // El punto mas lejano se puso al final de los puntos con angulos iguales en el ordenamiento previo.
    int m = 1;
    for (int i=1; i<n; i++) {

        // Se sigue eliminando el elemento 'i' mientras el angulo de 'i' e 'i+1' sea el mismo con respecto a 'p0'.
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0) {
            i++;
        }
        
        // Se pone el punto 'pi' en 'pm' para representar que es un punto del poligono convexo.
        points[m] = points[i];
        // Se actualiza el tamaño del arreglo modificado.
        m++;
    }
    
    // Si el arreglo modificado cuenta con menos de tres puntos, no es posible tener un poligono convexo.
    if (m < 3) {
        return;
    }
    
    // Se crea un stack de puntos stack<Point> 'S' y se insertan los primeros tres puntos.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    
    // Se procesan el resto de puntos.
    for (int i = 3; i < m; i++) {
        // Se elimina el top del stack mientras el angulo que se forme entre los tres puntos sea hacia la derecha.
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2){
            S.pop();
        }
        // Se inserta el punto pi al stack.
        S.push(points[i]);
    }
    
    // Stack de puntos stack<Point> 'SFinal' para imprimir los puntos en el orden solicitado (invertir stack 'S').
    stack<Point> SFinal;
    
    // Mientras haya puntos en el stack 'S', se sacan del stack y cada uno se mete al nuevo stack 'SFinal' para invertir su orden.
    while (!S.empty())
    {
        Point p = S.top();
        SFinal.push(p);
        S.pop();
    }

    // Se imprimen los puntos pertenecientes al poligono convexo.
    while (!SFinal.empty())
    {
        Point p = SFinal.top();
        cout << p.x << " " << p.y << endl;
        SFinal.pop();
    }
}
 
// Inicio del main.
int main() {

    // Variable int 'n' para almacenar el numero de puntos a recibir.
    int n;
    // Se recibe el numero de puntos a recibir.
    cin >> n;

    // Arreglo 'points' de tamaño 'n' donde se almacenaran los 'n' puntos.
    Point *points = new Point[n];
    // Se obtiene y almacena cada uno de los puntos en el arreglo.
    for (int i = 0; i < n; i++) {
        // Se recuperan y almacenan los valores de 'x' y 'y' de cada punto.
        cin >> points[i].x >> points[i].y;
    }

    // Se obtienen los puntos del poligono convexo con el uso del metodo 'convexHull'.
    convexHull(points, n);

    // Se eliminan los puntos para limpiar la memoria.
    delete[] points;

    return 0;
}