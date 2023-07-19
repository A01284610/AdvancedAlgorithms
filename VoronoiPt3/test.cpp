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
//OBSERVATION
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
//Falta que sea reversa
bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

//WRONG
//Sobrecarga de operador para 2 polygonos, sirve para saber si un triangulo es igual a otro
// bool operator==(const Polygon& lhs, const Polygon& rhs) {
//     const vector<Point>& lhsPoints = lhs.getPoints();
//     const vector<Point>& rhsPoints = rhs.getPoints();

//     // Compare the points of the two triangles
//     return lhsPoints == rhsPoints;
// }

//WRONG -- FIXING IN PROGRESS
bool operator==(const Polygon& polygon1, const Polygon& polygon2) {
    const std::vector<Segment>& segments1 = polygon1.getSegments();
    const std::vector<Segment>& segments2 = polygon2.getSegments();

    

    return true;
}

//CORRECTED
bool operator==(const Segment& seg1, const Segment& seg2){
  return (seg1.getP1() == seg2.getP1() && seg1.getP2() == seg2.getP2()) || 
         (seg1.getP2() == seg2.getP1() && seg1.getP2() == seg2.getP1());
}

//WRONG -- FIXING IN PROGRESS (MAYBE WE DONT NEED IT)
//regresar todas las aristas que comparte in triangulo con una lista de otros triangulos
vector<Segment> findSharedEdges(const Polygon& triangle, const vector<Polygon>& triangleList) {
    vector<Segment> sharedEdges;

    for (const Polygon& otherTriangle : triangleList) {
        // if (triangle == otherTriangle) {
        //     continue;  // Skip the same triangle
        // }

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

int main() {
    vector<Point> t1p = {Point(3073.5, -4398.16), Point(3073.5, 5145.16), Point(429, 98)};
    Polygon t1 = Polygon(3, t1p);

    vector<Point> t2p = {Point(3073.5, 5145.16), Point(429,98), Point(3073.5, -4398.16)};
    Polygon t2 = Polygon(3, t2p);

    return 0;
}