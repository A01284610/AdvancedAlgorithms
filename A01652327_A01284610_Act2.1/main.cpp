/*
 * Fecha: 13 Marzo 2023
 * Autores:
 *   Matricula: A01652327
 *   Nombre: Diego Esparza Hurtado
 *
 *   Matricula: A01284610
 *   Nombre: Alejandro Lizarraga Vizcarra
 *
 * Actividad 2.1 - Implementación de "Hash String"
 *    Es un programa que recibe por entrada redireccionada el nombre de un archivo y un valor 'n' multiplo de 4 (16 <= n <= 64).
 *      La salida es una cadena de longitud 2*n como representacion hexadecimal correspondiente al hasheo del archivo de texto de entrada.
 *
 * Para compilar: 
 *      g++ -o a.out main.cpp
 *
 * Para ejecutar:
 *      ./a.out 'nombre del archivo' 'n'
 *      
 *      Ejemplo:
 *          ./a.out test01.txt 16
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::string;
using std::fstream;
using std::ios_base;
using std::hex;
using std::setfill;
using std::setw;
using std::uppercase;


/* Método decToHexa:
 * Descripción: Recibe un solo valor en decimal como valor 'n' y convierte este integro a hexadecimal asegurandose de llenar los espacios vacios de 0 e imprimiendo en mayusculas.
 * Entrada: Integer 'n'.
 * Salida: Se imprime el hexadecimal.
 * Precondición: Se recibe una variable 'n' de tipo integer.
 * Postcondición: Se imprime el valor decimal en hexadecimal.
 * Complejidad: O(1) 
*/
void decToHexa(int n) { cout << setfill('0') << setw(2) << hex << uppercase << n; }


/* 
 * Método hashString:
 * Descripción: Recibe un vector de chars y un valor 'n' para imprimir su hasheo en hexadecimal con longitud 2*n.
 * Entrada: Vector <char> 'vect' que cuenta con todos los caracteres del archivo de texto.
 *          int 'nValor' que es el multiplo de 4 que se utilizara para realizar el hashing.
 * Salida: Se imprime una matriz con el camino a seguir indicado por '1'.
 * Precondición: El vector<char> 'vect' cuenta con los caracteres del archivo de texto. El int 'nValor' es un multiplo de 4 que cumple con (16 <= nValor <= 64) y (nValor % 4 = 0).
 * Postcondición: Se imprime el hashing en hexadecimal del archivo.
 * Complejidad: O(n) ; n = longitud del vector 'vect' , es decir, cantidad de caracteres del archivo.
*/
void hashString(vector<char> vect, int nValor){

    // int 'nColumnas' que almacena la cantidad de columnas que contendra la tabla.
    int nColumnas = nValor;

    // Calcula y guarda la cantidad de renglones necesarios para la tabla.
    float n1 = vect.size();
    float n2 = nValor;
    int nFilas = ceil(n1 / n2);

    int numChar = vect.size();

    
    // Se genera la tabla con dimension (nColumnas x nFilas) y se llena de 0.
    vector<vector<int> > vectorHash(nFilas);
    for (int i=0; i<nFilas; i++){
        vectorHash[i].resize(nColumnas, 0);
    }

    // Contador para revisar si ya se termino de recorrer el arreglo de caracteres del archivo.
    int counterTexto = 0;
    // Se genera un vector<int> 'vectFinal' de tamaño 'nColumnas' con 0, donde se registraran la suma de los valores ASCII de cada columna.
    vector<int> vectFinal(nColumnas, 0);

    
    /*
     * Opcion 1:
     *      Lineas 95-113. Se genera la tabla y se utiliza para la suma.
    */
    // Se recorre toda la tabla.
    for (int i=0; i<nFilas; i++){
        for (int j=0; j<nColumnas; j++){
            // En caso de que aun haya caracteres que leer, se agrega el valor ASCII del caracter.
            if (counterTexto < numChar){
                // Se almacena el valor ASCII en la tabla.
                vectorHash[i][j] = int(vect[counterTexto]);
                // Se suma el valor ASCII en el contador respectivo de su columna.
                vectFinal[j] = vectFinal[j] + vectorHash[i][j];
                counterTexto++;
            }
            else{
                // Se almacena el valor ASCII del "0" (30) en la tabla.
                vectorHash[i][j] = 30;
                // Se suma el valor ASCII del "0" (30) en el contador respectivo de su columna.
                vectFinal[j] = vectFinal[j] + 30;
            }
        }
    }

    /*
     * Opcion 2:
     *      Lineas 119-136. Se utiliza un contador para saber en la columna que iria el caracter, pero no se genera ninguna tabla. Se ahorra dicha memoria.
    */
    // Contador para saber la columna en la que se debe de sumar el valor ASCII del caracter.
    int counterCol = 0;
    // Mientras haya caracteres que leer, se agrega el valor ASCII del caracter.
    while (counterTexto < numChar){
        // Si se alcanza el final de la fila, se reinicia el contador.
        if (counterCol != 0 && counterCol % nColumnas == 0){
            counterCol = 0;
        }
        // Se suma a su respectiva suma de columna el valor ASCII.
        vectFinal[counterCol] = vectFinal[counterCol] + int(vect[counterTexto]);
        counterTexto++;
        counterCol++;
    }
    // En caso de que se tenga que rellenar con el valor ASCII del "0" en alguna de las columnas.
    while (counterCol < nColumnas){
        vectFinal[counterCol] = vectFinal[counterCol] + 30;
        counterCol++;
    }


    // Se recorre el vector 'vectFinal' que cuenta con la suma de las columnas, se obtiene su modulo 256 y se imprime el valor hexadecimal resultante.
    for (int i = 0; i < vectFinal.size(); i++){
        // Modulo 256 de cada suma de columna.
        vectFinal[i] = vectFinal[i] % 256;
        // Se obtiene e imprime el valor hexadecimal a dos digitos en mayusculas.
        decToHexa(vectFinal[i]);
    }
}


/* main con varios argumentos.
 * El primer argumento es el programa que se corre.
 * El segundo argumento es el nombre del archivo de texto.
 * El tercer argumento es el valor 'n' que se empleara en el Hashing.
*/
int main(int argc, char** argv)
{

    // Se genera la variable para almacenar el nombre del archivo.
    string nombreArchivo;
    // Se obtiene el nombre del segundo argumento recibido en el main.
    nombreArchivo = argv[1];

    // Se obtiene el valor 'n' a utilizar del tercer argumento recibido en el main.
    int n = std::stoi(argv[2]);

    // Donde se almacenara el contenido del archivo.
    fstream strm;

    // Si el archivo no se puede abrir, se indica al usuario y termina el programa.
    strm.open(nombreArchivo, ios_base::in);
    if (!strm.is_open()) {
        cout << "Open file failed" << endl;
        return 1;
    }

    // Variable char 'c' para recibir cada caracter del archivo.
    char c;
    // Vector de tipo char 'vect' para almacenar los caracteres del archivo.
    vector<char> vect;

    // Se obtienen todos los caracteres del archivo y se almacenan en el vector 'vect'.
    while (strm.get(c)){
        vect.push_back(c);
    }

    // Se obtiene el Hash String Hexadecimal del archivo.
    hashString(vect, n);
    cout << endl;

    return 0;
}