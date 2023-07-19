/*
 * Fecha: 5 Mayo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 4.1 - Implementacion Interseccion y proximidad aplicando geometria computacional.
 *    En el programa se hace uso de clases para almacenar los puntos, lineas y segmentos.
 *    El programa recibe 'n' puntos (cada uno con su respectivo 'x' y 'y'), 4 por linea para determinar si el segmento generado por los primeros dos puntos intersecta con el segmento generado por los ultimos dos puntos.
 *
 * Para compilar: 
 * g++ -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out < test01.txt
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using std::istream;
using std::cin;
using std::cout;
using std::endl;
using std::stod;
using std::min;
using std::max;
using std::vector;
using std::string;
using std::getline;
using std::pair;
using std::make_pair;

# define EPSILON (1e-9)

// Clase para un punto.
class Point{

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
        Point(double x_I, double y_I){
            this->x = x_I;
            this->y = y_I;
        }

        // Constructor que recibe un punto como parametro y asigna los valores de 'x' y 'y' del punto recibido como los valores de 'x' y 'y' del nuevo punto.
        // Complejidad: O(1)
        Point(const Point& p_I){
            this->x = p_I.x;
            this->y = p_I.y;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'x' del punto.
        // Complejidad: O(1)
        double getX() const{
            return this->x;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'y' del punto.
        // Complejidad: O(1)
        double getY() const{
            return this->y;
        }
};

// Clase para una linea.
class Line{
    
    private:
        // Variables del tipo 'double' para almacenar los valores 'a' , 'b' y 'c' de la expresion de una linea en formato 'ax + by + c = 0'.
        double a, b, c;

    public:

        // Constructor sin parametros de una linea. Asigna a los valores de 'a' , 'b' y 'c' el valor de '0.0'
        // Complejidad: O(1)
        Line(){
            this->a = 0.0;
            this->b = 0.0;
            this->c = 0.0;
        }

        // Constructor que recibe tres valores 'double' 'a_I' , 'b_I' y 'c_I' que asigna a las variables 'a' , 'b' y 'c' de la linea.
        // Complejidad: O(1)
        Line(double a_I, double b_I, double c_I){
            this->a = a_I;
            this->b = b_I;
            this->c = c_I;
        }

        // Constructor que recibe una linea como parametro y asigna los valores de 'a' , 'b' y 'c' de la linea recibida como los valores de 'a' , 'b' y 'c' de la nueva linea.
        // Complejidad: O(1)
        Line(const Line& l_I){
            this->a = l_I.a;
            this->b = l_I.b;
            this->c = l_I.c;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'a' de la linea.
        // Complejidad: O(1)
        double getA() const{
            return this->a;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'b' de la linea.
        // Complejidad: O(1)
        double getB() const{
            return this->b;
        }

        // Metodo que devuelve un 'double' con el valor de la variable 'c' de la linea.
        // Complejidad: O(1)
        double getC() const{
            return this->c;
        }

};

// Clase para un segmento.
class Segment{
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
        Point getP1() const{
            return p1;
        }

        // Metodo que devuelve el 'Point' 'p2' del segmento.
        // Complejidad: O(1)
        Point getP2() const{
            return p2;
        }
};


/*
 * Metodo pointsToLine:
 * Descripción: Genera una linea dados dos puntos recibidos como parametros.
 * Entrada: Point 'p1' y Point 'p2'.
 * Salida: Devuelve un objeto Line generado con los dos puntos recibidos como parametros.
 * Precondición: Se debe de recibir dos objetos tipo 'Point'.
 * Postcondición: Se genera un objeto tipo 'Line' generado con los dos puntos recibidos.
 * Complejidad: O(1)
*/
Line pointsToLine(const Point &p1, const Point &p2){
    double aux;

    // En caso de que sea una linea vertical.
    if (fabs(p1.getX() - p2.getX()) < EPSILON){
        return Line(1.0, 0.0, -p1.getX());
    }
    // En caso de que no sea una linea vertical.
    else {
        aux = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
        return Line (-aux, 1.0, (aux * p1.getX()) - p1.getY());
    }
}


/*
 * Metodo areParallel:
 * Descripción: Revisa si dos lineas recibidas como parametros son paralelas.
 * Entrada: Recibe dos objetos tipo 'Line': 'l1' y 'l2'.
 * Salida: Devuelve un 'bool' dependiendo de si son paralelas (true) o si no lo son (false).
 * Precondición: Se debe de recibir los dos objetos de tipo 'Line'.
 * Postcondición: Devuelve un 'bool' dependiendo de si son paralelas (true) o si no lo son (false).
 * Complejidad: O(1)
*/
bool areParallel(const Line &l1, const Line &l2){
    return ((fabs(l1.getA() - l2.getA()) <= EPSILON) && (fabs(l1.getB() - l2.getB()) <= EPSILON));
}


/*
 * Metodo areSameLine:
 * Descripción: Revisa si dos lineas recibidas como parametros son la misma linea.
 * Entrada: Recibe dos objetos tipo 'Line': 'l1' y 'l2'.
 * Salida: Devuelve un 'bool' dependiendo de si son la misma linea (true) o si no lo son (false).
 * Precondición: Se debe de recibir los dos objetos de tipo 'Line'.
 * Postcondición: Devuelve un 'bool' dependiendo de si son la misma linea (true) o si no lo son (false).
 * Complejidad: O(1)
*/
bool areSameLine(const Line &l1, const Line &l2){
    // Revisa si son paralelas ambas lineas y si la constante de ambas es igual.
    return(areParallel(l1, l2) && (fabs(l1.getC() - l2.getC()) <= EPSILON));
}


/*
 * Metodo intersectsAt:
 * Descripción: Encuentra el punto de interseccion entre dos lineas.
 * Entrada: Recibe dos objetos tipo 'Line': 'l1' y 'l2'.
 * Salida: Devuelve un apuntador de tipo 'Point': En caso de que no haya interseccion devuelve 'NULL' ; en caso de que haya interseccion lo devuelve con el punto generado con sus respectivos valores de 'x' y 'y' calculados.
 * Precondición: Recibe dos objetos tipo 'Line': 'l1' y 'l2'.
 * Postcondición: Devuelve un apuntador de tipo 'Point': En caso de que no haya interseccion devuelve 'NULL' ; en caso de que haya interseccion lo devuelve con el punto generado con sus respectivos valores de 'x' y 'y' calculados.
 * Complejidad: O(1)
*/
Point* intersectsAt(const Line &l1, const Line &l2){
    // Variables 'double' para almacenar las coordenadas 'x' y 'y' de la interseccion.
    double x, y;

    // En caso de que sean paralelas, no hay punto de interseccion.
    if (areParallel(l1, l2)){
        return NULL;
    }

    // Se calcula el valor de 'x' en la interseccion.
    x = ((l1.getB() * l1.getC()) - (l1.getB() * l2.getC())) / ((l2.getA() * l1.getB()) - (l1.getA() * l2.getB()));

    // Se calcula el valor de 'y' en la interseccion.
    if (fabs(l1.getB()) < EPSILON){
        y = -((l1.getA() * x) + l1.getC());
    }
    else {
        y = -((l2.getA() * x) + l2.getC());
    }

    return new Point (x, y);

}


/*
 * Metodo pointInBox:
 * Descripción: Se revisa si un punto se encuentra dentro del espacio generado por el rectangulo generado por dos puntos que se encuentran en vertices cuya diagonal es opuesta entre ellos.
 * Entrada: Recibe tres objetos tipo 'Point': 'p' , 'b1' y 'b2'.
 * Salida: Devuelve un 'bool' dependiendo de si el punto 'p' se encuentra en el rectangulo generado por los otros dos puntos.
 * Precondición: Recibe tres objetos tipo 'Point': 'p' , 'b1' y 'b2'.
 * Postcondición: Devuelve un 'bool' dependiendo de si el punto 'p' se encuentra en el rectangulo generado por los otros dos puntos.
 * Complejidad: O(1)
*/
bool pointInBox(const Point &p, const Point &b1, const Point &b2){
    return ((p.getX() >= min(b1.getX(), b2.getX())) &&
            (p.getX() <= max(b1.getX(), b2.getX())) &&
            (p.getY() >= min(b1.getY(), b2.getY())) &&
            (p.getY() <= max(b1.getY(), b2.getY())) );
}


/*
 * Metodo intersectAt:
 * Descripción: Recibe dos segmentos de linea y revisa si se intersectan entre ellos.
 * Entrada: Recibe dos objetos tipo 'Segment': 's1' y 's2'.
 * Salida: Revuelve un valor 'bool' dependiendo de si se intersectan los segmentos (true) o si no se intersectan (false).
 * Precondición: Se debe de recibir dos objetos tipo 'Segment': 's1' y 's2'.
 * Postcondición: Revuelve un valor 'bool' dependiendo de si se intersectan los segmentos (true) o si no se intersectan (false).
 * Complejidad: O(1)
*/
bool intersectAt(const Segment &s1, const Segment &s2){
    // Genera dos lineas con los puntos de los segmentos recibidos como parametros.
    Line l1 = pointsToLine(s1.getP1(), s1.getP2());
    Line l2 = pointsToLine(s2.getP1(), s2.getP2());

    // Variable 'bool' para almacenar el resultado.
    bool result;

    // Se revisa si es la misma linea y en caso de serlo, si se encuentran en algun mismo tramo.
    if(areSameLine(l1,l2)){
        return(pointInBox(s1.getP1(),s2.getP1(),s2.getP2()) ||
               pointInBox(s1.getP2(),s2.getP1(),s2.getP2()) ||
               pointInBox(s2.getP1(),s1.getP1(),s1.getP2()) ||
               pointInBox(s2.getP2(),s1.getP1(),s1.getP2()) );
    }

    // En caso de que no sean la misma linea y sea paralela, significa que no intersectan, por lo que se regresa un 'false'.
    if (areParallel(l1, l2)){
        return false;
    }

    // Se obtiene el punto donde se intersectan ambas lineas.
    Point *p = intersectsAt(l1, l2);

    // Se corrobora que la interseccion de las lineas ocurra en los segmentos recibidos como parametro.
    result = (pointInBox(*p, s1.getP1(), s1.getP2()) &&
              pointInBox(*p, s2.getP1(), s2.getP2()));
    
    // Se borra el punto generado.
    delete p;

    // Se devuelve el valor booleano dependiendo de si se intersectan o no.
    return result;

}


/*
 * Metodo checkIntersection:
 * Descripción: Revisa si cada par de segmentos recibidos en un vector se intersectan o no.
 * Entrada: vector<pair<Segment, Segment> > 'vect' con los pares de segmentos a revisar si intersectan o no.
 * Salida: Imprime por cada par de segmentos si se intersectan o no. En caso de interseccion imprime "true", en caso de no intersectarse imprime "false".
 * Precondición: Se debe de recibir el vector 'vect' con los segmentos a revisar si intersectan.
 * Postcondición: Imprime por cada par de segmentos si se intersectan o no. En caso de interseccion imprime "true", en caso de no intersectarse imprime "false".
 * Complejidad: O(n) -> n=numero de pares de segmentos.
*/
void checkIntersection(vector< pair<Segment,Segment> > vect){

    // Revisa para cada par de segmentos si estos se intersectan.
    for (int j = 0; j < vect.size(); j++){
        // En caso de que se intersecten imprime un "true".
        if (intersectAt(vect[j].first, vect[j].second) == true){
            cout << "true" << endl;
        }
        // En caso de que se no intersecten imprime un "false".
        else {
            cout << "false" << endl;
        }
    }
}

// Inicio del main().
int main(){

    // Se obtiene el input.
    istream& in = cin;

    // Variable int 'N' que sera el numero de puntos a recibir.
    int N = 0;  
    // Se recibe el numero de puntos a recibir.
    cin >> N;

    string S;
    getline(cin, S);

    // Se inicializa un vector de pares de segmentos 'vect' para almacenar los pares de segmentos que se revisara si intersectan.
    vector< pair<Segment,Segment> > vect;

    // Se inicializa variable string 'myText' que sera utilizada para obtener los N puntos.
    string myText;
    

    // Se obtienen las N/4 lineas.
    for (int i = 0; i < N/4; i++){
        // Se obtiene la linea y guarda en 'myText'.
        getline(cin, myText);
        // Variable auxiliar para obtener fragmentos de la linea.
        string text = myText;
        // Variable para saber la posicion de cada ' ' entre los valores.
        int pos = 0;

        // Se genera un vector de tipo 'double' para almacenar los ocho valores recibidos por linea.
        vector<double> temp_vect;

        // Se separa cada valor y se almacena en el vector 'temp_vect'.
        for (int j=0; j < 8; j++){
            pos = text.find(" ");
            string val = text.substr(0,pos);
            text = text.substr(pos+1);
            // Se almacena el valor obtenido.
            temp_vect.push_back(stod(val));
        }

        // Se generan ambos segmentos 'seg1' y 'seg2' de cada linea recibida en el archivo.
        Segment seg1 = Segment(Point(temp_vect[0],temp_vect[1]),Point(temp_vect[2],temp_vect[3]));
        Segment seg2 = Segment(Point(temp_vect[4],temp_vect[5]),Point(temp_vect[6],temp_vect[7]));

        // Se genera un par 'segmentPair' con los segmentos creados.
        pair<Segment, Segment> segmentPair = make_pair(seg1,seg2);

        // Se inserta al vector 'vect' el par 'segmentPair' generado.
        vect.push_back(segmentPair);
        temp_vect.clear();
    }

    // Se revisan las intersecciones entre los segmentos genedados con los puntos recibidos.
    checkIntersection(vect);

    return 0;
}