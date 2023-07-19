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
#include <string>

using namespace std;

int minx = 0;
int maxx = 0;
int maxy = 0;
int miny = 0;


//Class Point -----------------------------------------------------------------------------------------------------------
class Point {
    private:
        double x,y;
    
    public:
        Point();
        Point(double, double);
        Point(const Point&);
        void print();

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

void Point::print() {
    cout << "(" << getX() << " , " << getY() << ")";
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
        void print();

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

void Segment::print() {
    cout << "Segment from: "; 
    getP1().print();
    cout << " to: ";
    getP2().print();
    cout << endl;
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

struct PointHash {
    std::size_t operator()(const Point& p) const {
        std::hash<double> hasher;
        std::size_t xHash = hasher(p.getX());
        std::size_t yHash = hasher(p.getY());
        return xHash ^ yHash;
    }
};

struct PointEqual {
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.getX() == p2.getX() && p1.getY() == p2.getY();
    }
};

//Sobrecarga de operador para 2 puntos, para saber si son iguales
bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

//Sobrecarga de operador para 2 polygonos, sirve para saber si un triangulo es igual a otro
bool operator==(const Polygon& lhs, const Polygon& rhs) {
    const vector<Point>& lhsPoints = lhs.getPoints();
    const vector<Point>& rhsPoints = rhs.getPoints();

    // Compare the points of the two triangles
    return lhsPoints == rhsPoints;
}

//CORRECTED
bool operator==(const Segment& seg1, const Segment& seg2){
  return (seg1.getP1() == seg2.getP1() && seg1.getP2() == seg2.getP2()) || 
         (seg1.getP1() == seg2.getP2() && seg1.getP2() == seg2.getP1());
}

bool operator!=(const Segment& seg1, const Segment& seg2){
  return !((seg1.getP1() == seg2.getP1() && seg1.getP2() == seg2.getP2()) || 
         (seg1.getP1() == seg2.getP2() && seg1.getP2() == seg2.getP1()));
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

//regresar todas las aristas que comparte in triangulo con una lista de otros triangulos
bool hasSharedEdge(const Polygon& triangle_a, const Polygon& triangle_b) {

    vector<Segment> segments = triangle_a.getSegments();
    vector<Segment> otherSegments = triangle_b.getSegments();

    for (const Segment& segment : segments) {
        if (find(otherSegments.begin(), otherSegments.end(), segment) != otherSegments.end()) {
            return true;
        }
    }
    return false;
}

bool isEdgeInTriangles(const Segment& edge, const vector<Segment>& segments) {
    return find(segments.begin(), segments.end(), edge) != segments.end();
}

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

    // Checar si es lo mismo.
    //return (val > 0)? 1: 2; // clock or counterclock wise
}

void voronoiHull (Segment &seg, Segment &start, vector<Segment> connections, unordered_set<int> &set, vector<unordered_set<int>> &cycles, unordered_set<string> verticies, bool passed){
    // cout << "cyc" << cycles.size() << endl;
    // cout << "set" << set.size() << endl;
    // cout << "con" << connections.size() << endl;

    if (passed && (seg == start)){
        for (auto i: cycles){
            if (i == set){
                return;
            }
        }
        cycles.push_back(set);
        return;
    }

    for (int i = 0; i < connections.size(); i++){
        if (connections[i] != start){
            if (set.find(i) != set.end()) continue;
        }
        
        if (connections[i].getP1() == seg.getP1()){
            string vertexHash = to_string(seg.getP1().getX()) + "," + to_string(seg.getP1().getY());
            if ((orientation(seg.getP2(), seg.getP1(), connections[i].getP2()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                set.insert(i);
                verticies.insert(vertexHash);
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
                
            }
        }

        if (connections[i].getP1() == seg.getP2()){
            string vertexHash = to_string(seg.getP2().getX()) + "," + to_string(seg.getP2().getY());
            if ((orientation(seg.getP1(), seg.getP2(), connections[i].getP2()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                set.insert(i);
                verticies.insert(vertexHash);
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }
        }

        if (connections[i].getP2() == seg.getP1()){
            string vertexHash = to_string(seg.getP1().getX()) + "," + to_string(seg.getP1().getY());
            if ((orientation(seg.getP2(), seg.getP1(), connections[i].getP1()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                set.insert(i);
                verticies.insert(vertexHash);
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }        
        }

        if (connections[i].getP2() == seg.getP2()){
            string vertexHash = to_string(seg.getP2().getX()) + "," + to_string(seg.getP2().getY());
            if ((orientation(seg.getP1(), seg.getP2(), connections[i].getP1()) == 2) && (verticies.find(vertexHash) == verticies.end())){
                set.insert(i);
                verticies.insert(vertexHash);
                voronoiHull(connections[i],start,connections,set,cycles,verticies,true);
            }
        }
    }

    return;
}

void followPath(pair<float,float> start,pair<float,float> a, pair<float,float> b, pair<float,float> c, vector < pair < pair <float,float> , pair <float,float> > > temp, bool passed){
    // cout << a.first << "," << a.second << "\t\t\t" << b.first << "," << b.second << "\t\t\t" << c.first << "," << c.second << " " << endl;

    //si es que esta es la segunda vez pasando sobre el punto inicial
    if (passed && a == start){
        //terminar recursion
        return;
    }

    //si es que se esta moviendo en dirección de las manecillas del reloj los ultimos 3 puntos
    if (orientation(Point(a.first,a.second),Point(b.first,b.second),Point(c.first,c.second)) == 2){
        cout << (a.first) << " , " << (a.second) << endl;
        for (auto i: temp){
            if (i.first == c){
                followPath(start,b,c,i.second,temp,true);
            }
            if (i.second == c){
                followPath(start,b,c,i.first,temp,true);
            }
        }
        return;
    }
}

//END General use functisons -----------------------------------------------------------------------------------------------------------

vector<Polygon> delaunayTriangulation(vector<Point>& points) {
    //Paso 1 (Crear super triangulo)
    sort(points.begin(), points.end(), compareX);
  
    //determinar la corrdenada x del punto que se encuentra mas a la izquierda minx
    minx = points[0].getX();
    //determinar la coordenada x que se encuentra mas a la derecha maxx
    maxx = points[points.size()-1].getX();
    //determinar la corrdenada y del puntos que se encuentra mas hacia arriba maxy
    sort(points.begin(), points.end(), compareY);
    maxy = points[points.size()-1].getY();
    //determinar la coordenada y del punto que se encuentra mas hacia abajo miny
    miny = points[0].getY();
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
        //Asignar el valor de puntoAgregar
        puntoAgregar = points.front();

        triangulosInvalidos.clear();
        aristasComunes.clear();
        aristasInvalidas.clear();
        //Complejidad n
        //Paso 4: Iterar sobre cada triangulosDT
        for (std::vector<Polygon>::size_type i=0; i<triangulosDT.size(); i++) {
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

        //Obtener las aristas que se comparten entre triangulosInvalidos para paso 7
        for (auto i: triangulosInvalidos) {
            vector<Segment> elems = findSharedEdges(i, triangulosInvalidos);
            for (int j=0; j<elems.size(); j++) {
                if (!isEdgeInTriangles(elems[j], aristasComunes)) {
                    aristasComunes.push_back(elems[j]);
                }
            }
        }

        //Obtener todas las aristas de cada uno de los triangulos invalidos para paso 7
        for (auto i: triangulosInvalidos) {
            vector<Segment> segments = i.getSegments();
            for (int j=0; j<3; j++) {
                aristasInvalidas.push_back(segments[j]);
            }
        }

        //Paso 6: Por cada i en triangulosInvalidos
        for (int i=0; i<triangulosInvalidos.size(); i++) {
            //Para cada vertice v en triangulosInvalidos[i]
            vector<Point> trianguloInvalido = triangulosInvalidos[i].getPoints();
            for (int j=0; j<3; j++) {
                //puntos_inválidos.append(triángulos_inválidos[i][v]) en otras palabras (agregar punto a puntos invalidos)
                Point vertice = trianguloInvalido[j];
                puntosInvalidos.insert(vertice);
            }
            //triángulos_DT.Remover(triángulos_inválidos[i]) -- Todos los triangulos invalidos tienen que quitarse
            triangulosDT.erase(std::remove(triangulosDT.begin(), triangulosDT.end(), triangulosInvalidos[i]), triangulosDT.end());
        }

        // Paso 7: Por cada punto en puntosInvalidos
        std::unordered_set<Point, PointHash, PointEqual>::iterator pi;
        std::unordered_set<Point, PointHash, PointEqual>::iterator pj;
        //for pi in (puntos_invalidos[inicio] … puntos_invalidos[fin-1])
        for (pi = puntosInvalidos.begin(); pi != puntosInvalidos.end(); pi++) {
            //for pj in (pi+1… puntos_invalidos[fin])
            for (pj = next(pi); pj != puntosInvalidos.end(); pj++) {
                // siempre y cuando se cumplan las siguientes dos condiciones:
                // Primera condición, la arista (pi,pj) es una arista de alguno de los triángulos en triángulos_inválidos. (aristasInvalidas) 
                // Segunda condición, la arista (pi,pj) no se encuentra en aristas_comunes de los triangulos invalidos (aristasComunes)
                if (!isEdgeInTriangles(Segment(*pi,*pj), aristasComunes) && isEdgeInTriangles(Segment(*pi,*pj), aristasInvalidas)) {
                    // Hacer triángulos_DT.append((pi,pj,punto_a_añadir))
                    vector<Point> newTriangle = {*pi, *pj, puntoAgregar};
                    triangulosDT.push_back(Polygon(3, newTriangle));
                }
            }
        }
        points.erase(points.begin());
    }
    //Paso 8: Si no hay mas puntos, terminar el algoritmo
    return triangulosDT;
}


void voronoi(vector<Point>& points) {
    vector<Polygon> delaunay = delaunayTriangulation(points);
    vector< pair<Point, Polygon> > triangles;

    vector<Segment> connections;

    for (auto i: delaunay) {
        triangles.push_back(std::make_pair(circumcenter(i),i));
    }

    for (int i = 0; i < triangles.size(); i++){
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

    for (int i = 0; i < connections.size(); i++){
        tempCycle.insert(i);
        voronoiHull(connections[i],connections[i], connections,tempCycle,cycles,verticies,false);
        tempCycle.clear();
    }

    vector< vector < pair < pair <float,float> , pair <float,float> > > > result;
    vector < pair < pair <float,float> , pair <float,float> > > temp;

    for (auto i : cycles){
        cout << endl;
        for (auto itr = i.begin(); itr != i.end(); ++itr){
            cout << "Segment from: (" << (connections[*itr].getP1().getX()) << " , " << (connections[*itr].getP1().getY()) << ") to: (" << (connections[*itr].getP2().getX()) << " , " << (connections[*itr].getP2().getY()) << ")" << endl;
            temp.push_back(make_pair( make_pair(connections[*itr].getP1().getX(),connections[*itr].getP1().getY()) , make_pair(connections[*itr].getP2().getX(),connections[*itr].getP2().getY())));
        }
        result.push_back(temp);
        temp.clear();
    }

    cout << endl;

    bool foundFirst = false;
    pair<float,float> lowestX;
    pair<float,float> contra;
    pair<float,float> contra2;
    pair<float,float> third;
    pair<float,float> thrid2;

    // cout << result.size() << endl;
    for (auto i : result){
        cout << "iter\n" << endl;

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

        // cout << "low " << lowestX.first << " , " << lowestX.second << endl;
        // cout << "con " << contra.first << " , " << contra.second << endl;
        // cout << "con2 " << contra2.first << " , " << contra2.second << endl;


        for (auto j : i){
            // cout << "I have " << j.first.first << " m " << j.second.first << endl;
            if (j.first == contra && j.second != lowestX){
                // cout << "aa" << endl;
                followPath(lowestX,lowestX,contra,j.second,i,false);
            }
            if (j.second == contra && j.first != lowestX){
                // cout << "bb" << endl;
                followPath(lowestX,lowestX,contra,j.first,i,false);
            }
            if (j.first == contra2 && j.second != lowestX){
                // cout << "cc" << endl;
                followPath(lowestX,lowestX,contra2,j.second,i,false);
            }
            if (j.second == contra2 && j.first != lowestX){
                // cout << "dd" << endl;
                followPath(lowestX,lowestX,contra2,j.first,i,false);
            }
        }
        
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
        Point(120, 339)};

    
    voronoi(points);


    return 0;
}