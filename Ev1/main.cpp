/*
 * Fecha: 30 Marzo 2023
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
 * Actividad Integradora 1 - Transmisiones de datos comprometidas
 *    Parte 1:
 *          Se busca si el contenido de alguno de tres archivos 'mcodeX.txt' se encuentra en alguno de los dos archivos de transmision 'transmissionY.txt'.
 *          En caso de estarlo, se imprime un 'true' y la posicion donde inician. En caso de no hacerlo, se imprime un false.
 *    Parte 2:
 *          Se busca el palindromo mas largo contenido en cada uno de los archivos 'transmissionY.txt'.
 *          Se imprime la posicion inicial y final del palindromo mas largo de cada archivo iniciando en '1'.
 *    Parte 3:
 *          Se busca la subcadena comun mas larga (LCS - Longest Common Substring) entre los dos archivos 'transmissionY.txt'.
 *          Se imprime la posicion inicial y final de la subcadena comun mas larga (LCS - Longest Common Substring) con respecto al archivo 'transmission1.txt' iniciando en '1'.
 *
 * Para compilar: 
 * g++ -o a.out main.cpp
 *
 * Para ejecutar:
 * ./a.out
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::fstream;
using std::ios_base;

/*
 * Método getFileText:
 * Descripción: Recibe el nombre de un archivo y, en caso de poder acceder a él, genera y devuelve un string con todo el contenido del mismo.
 * Entrada: string 'fileName' con el nombre del archivo.
 * Salida: Devuelve un string 'res' con cada uno de los caracteres del archivo abierto.
 * Precondición: Un nombre de archivo valido de texto (terminacion .txt) que pueda ser accesado.
 * Postcondición: Se devuelve un string 'res' con todos los caracteres contenidos en el archivo.
 * Complejidad: O(n) ; n = cantidad de caracteres en el archivo.
*/
string getFileText(string fileName){

    // Donde se almacenara el archivo.
    fstream strm;

    // Se abre el archivo.
    strm.open(fileName, ios_base::in);
    // En caso de que no se haya podido acceder al archivo, se le notifica al usuario.
    if (!strm.is_open()) {
        cout << "Open file failed" << endl;
        return "Failed";
    }

    // string 'res' para almacenar el contenido del archivo.
    string res;
    // char 'temp_char' que sera utilizado para almacenar temporalmente cada caracter del archivo.
    char temp_char;
    // Mientras haya un caracter en el archivo, se obtiene, almacena en 'temp_char' y se concatena al string 'res'.
    while (strm.get(temp_char)){
            res += temp_char;
    }

    return res;
}

/* 
 * Método preProcesoPatron:
 * Descripción: Se buscan coincidencias internas dentro del string 'P' y se devuelve un vector con los valores obtenidos de las coincidencias.
 * Entrada: string 'P' con el string a utilizar.
 * Salida: Devuelve el vector 'V' de preproceso del string 'P'.
 * Precondición: Se recibe un string 'P'.
 * Postcondición: Devuelve el vector 'V' de preproceso del string 'P'.
 * Complejidad: O(m) ; m = Longitud del string 'P'.
*/
vector<int> preProcesoPatron(string P){

    // Se obtiene la longitud del string 'P' y se almacena en el int 'm'.
    int m = P.length();
    // Se genera un vector de int de tamaño 'n'.
    vector<int> V(m);
    // Se inicializan dos variables int que serviran para recorrer el string 'P' y el vector 'V'.
    int i=1, j=0;
    V[0] = 0;

    // se buscan coincidencias internas mientras aun haya letras en el string 'P'.
    while (i < m){
        // Si sigue habiendo similitud.
        if (P[i] == P[j]){
            V[i] = j + 1;
            i++, j++;
        }
        // En caso de que ya no haya similitud.
        else {
            if (j == 0){
                V[i] = 0;
                i++;
            }
            else {
                j = V[j-1];
            }
        }
    }

    return V;
}

/* 
 * Método KMP:
 * Descripción: Metodo que busca un string 'P' en un string 'T' , en caso de encontrarlo, devuelve un 'true' y la posicion en 'T' donde fue encontrado, en caso de no encontrarlo devuelve un 'false'.
 * Entrada: string 'P' a buscar ; string 'T' que es el texto en el que se buscara.
 * Salida: Devuelve e imprime un valor booleano que indica si se encontro o no el string 'P', en caso de encontrarlo tambien devuelve la posicion en 'T' donde inicia.
 * Precondición: Se recibe un string 'P' y un string 'T' que es mas grande que 'P'.
 * Postcondición: Devuelve e imprime un valor booleano que indica si se encontro o no el string 'P', en caso de encontrarlo tambien devuelve la posicion en 'T' donde inicia.
 * Complejidad: O(m+n) -> O(max(m,n)) ; m = Longitud del string 'P' ; n = Longitud del string 'T'.
*/
bool KMP(string P, string T){

    // int 'n' que es la longitud del string 'T'.
    int n = T.length();
    // int 'm' que es la longitud del string 'P'.
    int m = P.length();
    // vector<int> 'V' que tiene el vector de preproceso de patron del string 'P'.
    vector<int> V = preProcesoPatron(P);

    // int 'pos' que indica la posicion en la que inicia, en caso de encontrarse, el string 'P' en el string 'T'.
    int pos = 0;
    // int 'i' y 'j' para recorrer los strings 'P' y 'T'.
    int i=0, j=0;
    while (i<n){
        // En caso de que se encuentre un caracter de 'P' en 'T'.
        if (T[i] == P[j]){
            i++, j++;
            // En caso de que se haya encontrado todo el string 'P' en el string 'T', se imprime un 'True (pos) | ' y devuelve un bool 'true'.
            if (j == m){
                cout << "true " << pos << " | ";
                return true;
            }
        }
        // En caso de que no se cuente con el mismo caracter de 'P' en 'T'.
        else {
            if (j == 0){
                i++;
                pos = i;
            }
            else {
                pos = i - V[j-1];
                j = V[j-1];
            }
        }
    }

    // En caso de que no se haya encontrado el string 'P' en el string 'T', se imprime un 'False | ' y devuelve un bool 'true'.
    cout << "false | ";
    return false;
}

/* 
 * Método aumenta:
 * Descripción: Genera un nuevo string de tamaño impar al agregar el caracter '|' entre cada caracter del string 'S' original, asi como al principio y final del mismo.
 * Entrada: string 'S' con el string a aumentar.
 * Salida: Se devuelve el string 'S' con el caracter '|' al inicio, entre cada uno de los caracteres originales y, al final del mismo.
 * Precondición: Se recibe un string 'S'.
 * Postcondición: Se devuelve el string 'S' con el caracter '|' al inicio, entre cada uno de los caracteres originales y, al final del mismo.
 * Complejidad: O(n) ; n = Longitud del string 'S'
*/
string aumenta(string S){

    // string 's' donde se almacenara el nuevo string aumentado.
    string s = "";
    // int 'n' donde se almacena la longitud de 'S'.
    int n = S.length();
    // Se agrega al inicio y entre cada caracter un '|'.
    for (int i=0; i < n; i++){
        s = s + "|" + S[i];
    }

    return s + "|";
}

/* 
 * Método manacher:
 * Descripción: Obtiene el palindromo mas largo de un string, imprime la posicion inicial y final del mismo en el string.
 * Entrada: string 'S' con el string a utilizar.
 * Salida: Se imprime la posicion inicial y final del palindromo mas largo del string 'S'.
 * Precondición: Se recibe un string 'S'.
 * Postcondición: Se imprime la posicion inicial y final del palindromo mas largo del string 'S'.
 * Complejidad: O(n) ; n = longitud del string 'S'.
*/
pair<int, int> manacher(string S) {
    pair<int, int> res; // Resultado (inicio,final).
    if (S.length() == 0) // S es nulo.
        return res; 
    string T = aumenta(S); // Llamar a funcion.
    int N = T.length(); 
    // Longitud y centro del maximo palindromo encontrado.
    int maxLong = 1, maxCentro = 1; // Hasta ahora posicion I.
    int L[N]; //int L[N]; 
    int C = 1; 
    int Li = 0, Ri = 0; 
    bool expansion = false; // true si requiera expansion.
    L[0] = 0; L[1] = 1; 
    for (Ri = 2; Ri < N; Ri++) { 
        expansion = false; 
        Li = C - (Ri - C); 
        if ((C + L[C]) - Ri >= 0) { 
            if (L[Li] < (C + L[C]) - Ri) // Caso 1 
                L[Ri] = L[Li]; 
            else if (L[Li] == (C + L[C]) - Ri && (C + L[C]) == N - 1) // Caso 2 
                L[Ri] = L[Li]; 
            else if (L[Li] == (C + L[C]) - Ri && (C + L[C]) < N - 1) { // Caso 3 
                L[Ri] = L[Li]; 
                expansion = true; // requiere expansion.
            } 
            else if (L[Li] > (C + L[C]) - Ri) {  // Case 4 
                L[Ri] = (C + L[C]) - Ri; 
                expansion = true; // requiere expansion.
            } 
        } 
        else { 
            L[Ri] = 0; 
            expansion = true; // Requiere expansion.
        } 
        if (expansion) // Hacer la expansion hasta donde se pueda.
            while ((Ri + L[Ri]) < N && (Ri - L[Ri]) > 0 && T[Ri + L[Ri] + 1] == T[Ri - L[Ri] - 1] ) 
                L[Ri]++; 
        if (Ri + L[Ri] > (C + L[C])) 
            // Si el nuevo palindromo se expande mas alla de C.
            C = Ri; 
        if (L[Ri] > maxLong) { 
            // Guardar longitud y centro del palindromo mas grande hasta ahora.
            maxLong = L[Ri]; 
            maxCentro = Ri; 
        } 
    } 
    // Obtener inicio y longitud del maximo palindromo encontrado recordando que la longitud de T es el doble de la de S.
    res.first = (maxCentro - maxLong) / 2; // Inicio en S 
    res.second = res.first + maxLong - 1; // Final en S
    cout << res.first+1 << " " << res.second+1 << " | ";

    return res;
} 

/* 
 * Método LCS:
 * Descripción: Obtiene la subcadena comun mas larga entre dos strings 'S1' y 'S2', luego imprime el inicio y fin de la misma en 'S1'. En caso de no existir, imprime que no encontro coincidencia.
 * Entrada: string 'S1' y string 'S2' que son los string en los que se buscara la subcadena comun mas larga (LCS).
 * Salida: Se imprime el inicio y fin del LCS con respecto a 'S1'. En caso de no existir, imprime que no encontro coincidencia.
 * Precondición: Se reciben dos strings 'S1' y 'S2'.
 * Postcondición: Se obtiene el LCS y se imprime el inicio y fin del LCS con respecto a 'S1'. En caso de no existir, imprime que no encontro coincidencia.
 * Complejidad: O(n*m) ; n = longitud del string 'S1' ; m = longitud del string 'S2'
 * Rerencia: https://www.geeksforgeeks.org/print-longest-common-substring/
*/
void LCS(string S1, string S2){
    // int 'n' que es la longitud del string 'S1'.
    int n = S1.length();
    // int 'n' que es la longitud del string 'S2'.
    int m = S2.length();
    // Arreglo 'dp' para almacenar el resultado de dos filas consecutivas.
    int dp[2][m+1];
    // int 'len' para almacenar la longitud de la subcadena comun mas larga.
    int len = 0;
    // int 'end' para almacenar la posicion del final de la subcadena comun mas larga.
    int end = 0;
    // string 'lcs' para almacenar la subcadena comun mas larga (LCS).
    string lcs;
    // par 'pos' que almacena la posicion inicial y final del LCS en 'S1'.
    pair<int,int> pos;

    // Se recorren los strings y llena la tabla 'dp'.
    for (int i=0; i <=n; i++){
        for (int j=0; j<=m; j++){
            // Si el caracter coincide en 'S1' y en 'S2'.
            if (S1[i-1] == S2[j-1]){
                // 
                dp[i%2][j] = dp[1-(i%2)][j-1]+1;
                // Si la longitud de la nueva subcadena comun es mayor a la actual subcadena comun.
                if (dp[i%2][j] > len){
                    // Se obtiene la longitud de la cadena y almacena en 'len'.
                    len = dp[i%2][j];
                    // Se obtiene el final de la subcadena con respecto a 'S1'.
                    end = i-1;
                    // Se obtiene el inicio de la subcadena con respecto a 'S1' y se almacena en el primer valor del par 'pos'.
                    pos.first = end-len+1;
                    // Se obtiene el final de la subcadena con respecto a 'S1' y se almacena en el segundo valor del par 'pos'.
                    pos.second = end;
                }
            }
            // En caso de que no coincida 'S1' con 'S2'.
            else {
                dp[i%2][j] = 0;
            }
        }
    }

    // Si hay LCS, se obtiene LCS, pero unicamente se imprime la posicion inicial y final del LCS con respecto a 'S1' iniciando en '1'.
    if (len > 0){
        // Se obtiene el LCS (Longest Common Substring).
        lcs = S1.substr(pos.first, len);

        // Se imprime la posicion inicial y final del LCS con respecto a 'S1'. Se le suma un 1 para iniciar en '1'.
        cout << pos.first+1 << " " << pos.second+1 << endl;
    }
    // Si no hay LCS, se le notifica al usuario.
    else {
        cout << "No hay coincidencias entre ambos archivos." << endl;
    }
}


// Inicio del main()
int main(){

    // Se guarda en el string 'ArchivoTransmission1' el nombre del primer archivo de transmision con nombre 'transmission1.txt'.
    string ArchivoTransmission1 = "transmission1.txt";
    // Se obtiene y guarda en el string 'ArchivoTrans1' el contenido del archivo con nombre de la variable 'ArchivoTransmission1'.
    string ArchivoTrans1 = getFileText(ArchivoTransmission1);

    // Se guarda en el string 'ArchivoTransmission2' el nombre del segundo archivo de transmision con nombre 'transmission2.txt'.
    string ArchivoTransmission2 = "transmission2.txt";
    // Se obtiene y guarda en el string 'ArchivoTrans2' el contenido del archivo con nombre de la variable 'ArchivoTransmission2'.
    string ArchivoTrans2 = getFileText(ArchivoTransmission2);

    // Se guarda en el string 'ArchivoVirus1' el nombre del primer archivo de codigo malicioso con nombre 'mcode1.txt'.
    string ArchivoVirus1 = "mcode1.txt";
    // Se obtiene y guarda en el string 'ArchivoVir1' el contenido del archivo con nombre de la variable 'ArchivoVirus1'.
    string ArchivoVir1 = getFileText(ArchivoVirus1);

    // Se guarda en el string 'ArchivoVirus2' el nombre del primer archivo de codigo malicioso con nombre 'mcode2.txt'.
    string ArchivoVirus2 = "mcode2.txt";
    // Se obtiene y guarda en el string 'ArchivoVir2' el contenido del archivo con nombre de la variable 'ArchivoVirus2'.
    string ArchivoVir2 = getFileText(ArchivoVirus2);

    // Se guarda en el string 'ArchivoVirus3' el nombre del primer archivo de codigo malicioso con nombre 'mcode3.txt'.
    string ArchivoVirus3 = "mcode3.txt";
    // Se obtiene y guarda en el string 'ArchivoVir3' el contenido del archivo con nombre de la variable 'ArchivoVirus3'.
    string ArchivoVir3 = getFileText(ArchivoVirus3);

    // Inicio de la primera parte ; donde se analiza si cada codigo malicioso se encuentra en cada uno de los archivos de transmision.
    cout << "parte 1" << endl;
    
    // Indica si el codigo malicioso del primer archivo malicioso se encuentra en el primer archivo de transmision.
    KMP(ArchivoVir1, ArchivoTrans1);
    cout << ArchivoVirus1 << " en " << ArchivoTransmission1 << endl;
    // Indica si el codigo malicioso del segundo archivo malicioso se encuentra en el primer archivo de transmision.
    KMP(ArchivoVir2, ArchivoTrans1);
    cout << ArchivoVirus2 << " en " << ArchivoTransmission1 << endl;
    // Indica si el codigo malicioso del tercer archivo malicioso se encuentra en el primer archivo de transmision.
    KMP(ArchivoVir3, ArchivoTrans1);
    cout << ArchivoVirus3 << " en " << ArchivoTransmission1 << endl;

    // Indica si el codigo malicioso del primer archivo malicioso se encuentra en el segundo archivo de transmision.
    KMP(ArchivoVir1, ArchivoTrans2);
    cout << ArchivoVirus1 << " en " << ArchivoTransmission2 << endl;
    // Indica si el codigo malicioso del segundo archivo malicioso se encuentra en el segundo archivo de transmision.
    KMP(ArchivoVir2, ArchivoTrans2);
    cout << ArchivoVirus2 << " en " << ArchivoTransmission2 << endl;
    // Indica si el codigo malicioso del tercer archivo malicioso se encuentra en el segundo archivo de transmision.
    KMP(ArchivoVir3, ArchivoTrans2);
    cout << ArchivoVirus3 << " en " << ArchivoTransmission2 << endl;


    // Inicio de la segunda parte ; donde se muestra donde inicia y termina el codigo "espejeado" (palindromo de chars) mas largo para cada archivo de transmision.
    cout << "parte 2" << endl;

    // Se obtiene la posicion inicial y final del palindromo de chars mas largo del primero archivo de transmision.
    manacher(ArchivoTrans1);
    cout << "transmission1.txt" << endl;

    // Se obtiene la posicion inicial y final del palindromo de chars mas largo del segundo archivo de transmision.
    manacher(ArchivoTrans2);
    cout << "transmission2.txt" << endl;


    // Inicio de la tercera parte ; donde se muestra la similitud entre ambos archivos de transmision.
    // Se muesta la posicion inicial y final del primer archivo donde se encuentra el substring mas largo comun entre ambos archivos.
    cout << "parte 3" << endl;

    // Muestra la posicion inicial y final del substring mas largo comun entre los ambos archivos de transmision.
    LCS(ArchivoTrans1, ArchivoTrans2);

    return 0;
}