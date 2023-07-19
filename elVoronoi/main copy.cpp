/*
 * Para compilar: 
 * g++ -std=c++17 -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out
 * 
 * g++ -Wall -std=c++17 main.cpp -o a.out
 * 
 * g++ -Wall main.cpp -o a.out
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <unordered_set>

using namespace std;

//Class Point -----------------------------------------------------------------------------------------------------------
class Point {
    private:
        double x,y;
    
    public:
        Point();
        Point(double, double);
        Point(const Point&);

        double getX() const;
        double getY() const;
};

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point(const Point& other) {
    x = other.x;
    y = other.y;
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

//END Class Point -----------------------------------------------------------------------------------------------------------

//Class Segment -----------------------------------------------------------------------------------------------------------

class Segment {
    private:
        Point p1, p2;
    
    public:
        Segment();
        Segment(const Point&, const Point&);
        Segment(const Segment&);

        Point getP1() const;
        Point getP2() const;
};

Segment::Segment() {
    // Default constructor, initializes both points to the origin (0, 0)
    p1 = Point();
    p2 = Point();
}

Segment::Segment(const Point& point1, const Point& point2) {
    // Parameterized constructor, initializes the segment with the given points
    p1 = point1;
    p2 = point2;
}

Segment::Segment(const Segment& other) {
    // Copy constructor, creates a copy of the other segment
    p1 = other.p1;
    p2 = other.p2;
}

Point Segment::getP1() const {
    // Getter for the first point of the segment
    return p1;
}

Point Segment::getP2() const {
    // Getter for the second point of the segment
    return p2;
}

//END Class Segment -----------------------------------------------------------------------------------------------------------



//Class Polygon -----------------------------------------------------------------------------------------------------------

class Polygon {
    private:
        vector<Point> points;
    public:
        Polygon(int n, const Point& startPoint);
        Polygon(int n, vector<int>& xs, vector<int>& ys); //cambie int xs[]/ys[] por vectores en lugar de arrays
        Polygon(int n, vector<Point>& points); //Alomejor usar este en lugar del de arriba
        Polygon(const Polygon&);

        vector<Point> getPoints() const;
        vector<Segment> getSegments() const;
        int getSize() const;
};

Polygon::Polygon(int n, const Point& startPoint) {
    points.push_back(startPoint);
}

Polygon::Polygon(int n, vector<int>& xs, vector<int>& ys) {
    for (int i=0; i<n; i++) {
        points.push_back(Point(xs[i], ys[i]));
    }
}

Polygon::Polygon(int n, vector<Point>& points) {
    this->points = points;
}

Polygon::Polygon(const Polygon& other) {
    points = other.points;
}

vector<Point> Polygon::getPoints() const {
    return points;
}

int Polygon::getSize() const {
    return points.size();
}

//Retorna un vector de segmentos que forman el polygono
vector<Segment> Polygon::getSegments() const {
    vector<Segment> segments;

    const size_t numPoints = points.size();
    if (numPoints >= 2) {
        for (size_t i = 0; i < numPoints - 1; ++i) {
            segments.push_back(Segment(points[i], points[i+1]));
        }
        // Connect the last point with the first point to close the polygon
        segments.push_back(Segment(points[numPoints - 1], points[0]));
    }

    return segments;
}

//END Class Polygon -----------------------------------------------------------------------------------------------------------

//General use functions -----------------------------------------------------------------------------------------------------------

//Obtener la distancia entre 2 puntos
double distanceBetweenPoints(const Point& p1, const Point& p2) {
    double x1 = p1.getX(), y1 = p1.getY();
    double x2 = p2.getX(), y2 = p2.getY();
    double dx = x2 - x1, dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

//Funcion que compara 2 puntos por su componente X. Sirve para ordenar vectores de Puntos ascendente con respecto a X
bool compareX(const Point& a, const Point& b) {
    if (a.getX() != b.getX()) {
        return a.getX() < b.getX();
    } else {
        return a.getY() < b.getY();
    }
}

//Funcion que compara 2 puntos por su componente Y. Sirve para ordenar vectores de Puntos ascendente con respecto a Y
bool compareY(const Point& a, const Point& b) {
    if (a.getX() != b.getX()) {
        return a.getY() < b.getY();
    } else {
        return a.getX() < b.getX();
    }
}

Point circumcenter(Polygon& triangle) {
    vector<Point> points = triangle.getPoints();
    Point a = points[0];
    Point b = points[1];
    Point c = points[2];
    //Calculate midpoints of AB and
    Point abMidpoint((a.getX() + b.getX()) / 2.0, (a.getY() + b.getY()) / 2.0);
    Point bcMidpoint((b.getX() + c.getX()) / 2.0, (b.getY() + c.getY()) / 2.0);
    //Calculate the slopes of the lines passing through segments AB and BC
    double abSlope = (b.getX() - a.getX()) / (a.getY() - b.getY()); // Perpendicular slope to AB
    double bcSlope = (c.getX() - b.getX()) / (b.getY() - c.getY()); // Perpendicular slope to BC
    //Calculate x-coordinate of the circumcenter using slopes and midpoints
    double circumcenterX = (bcMidpoint.getY() - abMidpoint.getY() + abSlope * abMidpoint.getX() - bcSlope * bcMidpoint.getX()) / (abSlope - bcSlope);
    //Calculate y-coordinate of the circumcenter using the x-coordinate and the line passing through AB
    double circumcenterY = abMidpoint.getY() + abSlope * (circumcenterX - abMidpoint.getX());
    //Return circumcenter 
    return Point(circumcenterX, circumcenterY);
}

//Formula Hash Para usar un unordered_set para la clase Point
struct PointHash {
    std::size_t operator()(const Point& p) const {
        std::size_t xHash = std::hash<double>{}(p.getX());
        std::size_t yHash = std::hash<double>{}(p.getY());
        return xHash ^ yHash;
    }
};

//Sobrecarga de operador para usar unordered_set para la clase Point
struct PointEqual {
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.getX() == p2.getX() && p1.getY() == p2.getY();
    }
};

//Sobrecarga de operador para 2 puntos, para saber si son iguales
bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

//Sobrecarga de operador para 2 polygonos, sirve para saber si un triangulo es igual a otro
bool operator==(const Polygon& lhs, const Polygon& rhs) {
    const vector<Point>& lhsPoints = lhs.getPoints();
    const vector<Point>& rhsPoints = rhs.getPoints();

    // Compare the points of the two triangles
    return lhsPoints == rhsPoints;
}

bool operator==(const Segment& seg1, const Segment& seg2){
  return seg1.getP1() == seg2.getP1() && seg1.getP2() == seg2.getP2();
}

//Revisar si la arista es igual
bool isSharedEdge(const Segment& segment1, const Segment& segment2) {
    return (segment1.getP1() == segment2.getP1() && segment1.getP2() == segment2.getP2()) ||
           (segment1.getP1() == segment2.getP2() && segment1.getP2() == segment2.getP1());
}

//regresar todas las aristas que comparte in triangulo con una lista de otros triangulos
vector<Segment> findSharedEdges(const Polygon& triangle, const vector<Polygon>& triangleList) {
    vector<Segment> sharedEdges;

    for (const Polygon& otherTriangle : triangleList) {
        if (triangle == otherTriangle) {
            continue;  // Skip the same triangle
        }

        vector<Segment> segments = triangle.getSegments();
        vector<Segment> otherSegments = otherTriangle.getSegments();

        for (const Segment& segment : segments) {
            if (find(otherSegments.begin(), otherSegments.end(), segment) != otherSegments.end()) {
                sharedEdges.push_back(segment);
            }
        }
    }

    return sharedEdges;
}

bool isEdgeInTriangles(const Segment& edge, const vector<Polygon>& triangles) {
    for (const Polygon& triangle : triangles) {
        vector<Segment> segments = triangle.getSegments();
        if (find(segments.begin(), segments.end(), edge) != segments.end()) {
            return true; // Edge found in one of the triangles
        }
    }
    return false; // Edge not found in any of the triangles
}

//END General use functions -----------------------------------------------------------------------------------------------------------





//Real Name: vector<Polygon> delaunayTriangulation(vector<Point>& points)
vector<Polygon> delaunayTriangulation(vector<Point>& points) {
    //Esto se recibe 

    //Paso 1 (Crear super triangulo)
    sort(points.begin(), points.end(), compareX);
  
    //determinar la corrdenada x del punto que se encuentra mas a la izquierda minx
    int minx = points[0].getX();
    //determinar la coordenada x que se encuentra mas a la derecha maxx
    int maxx = points[points.size()-1].getX();
    //determinar la corrdenada y del puntos que se encuentra mas hacia arriba maxy
    sort(points.begin(), points.end(), compareY);
    int maxy = points[points.size()-1].getY();
    //determinar la coordenada y del punto que se encuentra mas hacia abajo miny
    int miny = points[0].getY();
    //Hay que calcular distx = maxx-minx;
    int distx = maxx - minx;
    //Hay que calcular disty = maxy-miny;
    int disty = maxy - miny;
    //Los vertices del super_triangulo son:
    vector<Point> super = {
        Point(minx-9.5*distx, miny+0.5*disty), 
        Point(minx+5.5*distx, miny+9.16*disty), 
        Point(minx+5.5*distx, miny-8.16*disty)};

    Polygon superTriangle = Polygon(3, super);

    //Paso 2: Crear una estructura triangulos_DT donde se iran guardando los triangulos creados. En esta estructura incluir este primer tirangulo
    vector<Polygon> triangulosDT = {superTriangle};
    //Crear estructura triangulosInvalidos
    vector<Polygon> triangulosInvalidos;

    //Paso 3: Hay un punto a agregar? Si si entonces escoger el siguiente puntoAgregar
    Point puntoAgregar, circumcentro;
    double circumradio, distance;
    while (!points.empty()) {
        
        //Asignar el valor de puntoAgregar
        puntoAgregar = points.front();

        triangulosInvalidos.clear();
        cout << "a" << endl;
        //Paso 4: Iterar sobre cada triangulosDT
        for (int i=0; i<triangulosDT.size(); i++) {
            //Encontrar el circuncentro
            circumcentro = circumcenter(triangulosDT[i]);
            //Encontrar el circunradio
            circumradio = distanceBetweenPoints(circumcentro, triangulosDT[i].getPoints()[0]);
            //Determinar distancia entre punto_a_añadir y el circuncentro.
            distance = distanceBetweenPoints(circumcentro, puntoAgregar);
            //Si la distancia es menor que el circunradio, entonces el triangulo actual es invalido
            if (distance < circumradio) {
                triangulosInvalidos.push_back(triangulosDT[i]);
            } 
        }

      
        //Paso 5: Hacer puntos_inválidos como un unordered_set
        unordered_set<Point, PointHash, PointEqual> puntosInvalidos;
        vector<Segment> aristasComunes;

        //Paso 6: Por cada i en triangulosInvalidos
        for (int i=0; i<triangulosInvalidos.size(); i++) {
            //triángulos_DT.Remover(triángulos_inválidos[i]) si hay aristas en comun
            //Hay que buscar cuáles de las aristas de triángulos_inválidos[i] son comunes con las aristas del resto de los triángulos en triángulos_inválidos.
            aristasComunes = findSharedEdges(triangulosInvalidos[i], triangulosInvalidos);
            if (aristasComunes.size() > 0) {
                triangulosDT.erase(std::remove(triangulosDT.begin(), triangulosDT.end(), triangulosInvalidos[i]), triangulosDT.end());
            }
            //Para cada vertice v en triangulosInvalidos[i]
            vector<Point> trianguloInvalido = triangulosInvalidos[i].getPoints();
            for (int j=0; j<3; j++) {
                //puntos_inválidos.append(triángulos_inválidos[i][v]) en otras palabras (agregar punto a puntos invalidos)
                Point vertice = trianguloInvalido[j];
                puntosInvalidos.insert(vertice);
            }

            //Paso 7: Por cada punto en puntosInvalidos
            unordered_set<Point>::iterator pi, pj;

            //for pi in (puntos_invalidos[inicio] … puntos_invalidos[fin-1])
            
            for (pi = puntosInvalidos.begin(); pi != puntosInvalidos.end(); pi++) {
                //for pj in (pi+1… puntos_invalidos[fin])
                for (pj = next(pi); pj != puntosInvalidos.end(); pj++) {
                    // siempre y cuando se cumplan las siguientes dos condiciones:
                    // Primera condición, la arista (pi,pj) es una arista de alguno de los triángulos en triángulos_inválidos. 
                    //Segunda condición, la arista (pi,pj) no se encuentra en aristas_comunes.
                    auto it = std::find(aristasComunes.begin(), aristasComunes.end(), Segment(*pi, *pj));
                    if (isEdgeInTriangles(Segment(*pi,*pj), triangulosInvalidos) && it == aristasComunes.end()) {
                        // Hacer triángulos_DT.append((pi,pj,punto_a_añadir))
                        vector<Point> newTriangle = {*pi, *pj, puntoAgregar};
                        triangulosDT.push_back(Polygon(3, newTriangle));
                    }
                }
            }

        }
        points.erase(points.begin());
    }
    
    return triangulosDT;
    
}

void voronoi(vector<Point>& points) {
    cout << "Hola" << endl;
    vector<Polygon> delaunay = delaunayTriangulation(points);
    vector<Point> polygons;
    //calcular el circumcentro y almacenarlo
    cout << "Hola" << endl;
    for (auto i: delaunay) {
        polygons.push_back(circumcenter(i));
    }

    for(auto i: polygons) {
        cout << "(" <<i.getX() << " , " << i.getY() << ")" << endl;
    }
}

int main (){
    vector<Point> points = {
        Point(656, 607),
        Point(349, 228),
        Point(460, 380),
        Point(657, 378),
        Point(618, 187),
        Point(155, 99),
        Point(541, 570),
        Point(272, 649),
        Point(429, 98),
        Point(120, 339)
    };

    voronoi(points);

    return 0;
}

//Pruebas que ya son confirmadas:
//PRUEBAS PASO 1
    // cout << "minx: " << minx << endl;
    // cout << "maxx: " << maxx << endl;
    // cout << "maxy: " << maxy << endl;
    // cout << "miny: " << miny << endl;
    // cout << "distx: " << distx << endl;
    // cout << "disty: " << disty << endl;

    //PRUEBA DE LA CREACION DEL SUPER TRIANGULO
    // cout << "minx: " << minx << endl;
    // cout << "maxx: " << maxx << endl;
    // cout << "maxy: " << maxy << endl;
    // cout << "miny: " << miny << endl;
    // cout << "distx: " << distx << endl;
    // cout << "disty: " << disty << endl;

    // vector<Point> test = superTriangle.getPoints();
    // for (int i=0; i<test.size(); i++) {
    //     cout << "point " << i + 1 << ": (" << test[i].getX() << ", " << test[i].getY() << ")" << endl;
    // }

    //Prueba CIRCUNCENTRO
    // Point circumcentro = circumcenter(superTriangle);
    // cout << circumcentro.getX() << " " << circumcentro.getY() << endl;