#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using namespace std;




void floyd(int D[10][10], int n) {
    for(int k = 0; k<n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j<n; j++){
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][k]+D[k][j] < D[i][j]){
                    D[i][j] = D[i][k]+D[k][j];
                }
            }
        }
    }

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            cout << i << "-" << j << ":" << D[i][j] << "\t";
        }
        cout << endl;
    }
}


/*
0 769 954 952 945 104 934 347 164 365
769 0 718 832 162 723 228 758 424 606
954 718 0 488 834 197 913 196 585 895
952 832 488 0 475 100 658 842 229 646
945 162 834 475 0 119 185 193 313 175
104 723 197 100 119 0 537 647 916 401
934 228 913 658 185 537 0 429 112 207
347 758 196 842 193 647 429 0 249 259
164 424 585 229 313 916 112 249 0 694
365 606 895 646 175 401 207 259 694 0
*/


//g++ -o a.out main.cpp; ./a.out < test01.txt

int main(){

    int grid[10][10];

    std::istream& in = cin;

    // Se inicializan las variables 'int' 'M' y 'N' para almacenar las dimensiones del arreglo.
    int M = 0;
    int N = 0;

    // Se obtienen las dimensiones (MxN) y se almacenan.
    cin >> M;
    cin >> N;

    // Se inicializa un vector de vectores de tamaño M con valores tipo 'int'.
    vector<vector<int> > vect;


    string S;
    getline(cin, S);

    // Se inicializa variable string 'myText' que sera utilizada para obtener las M lineas y sus N valores. 
    string myText;

    for (int i = 0; i < 10; i++){
        // Se obtiene la linea y guarda en 'myText'.
        getline(cin, myText);
        // Variable auxiliar para obtener fragmentos de la linea.
        string text = myText;
        // Variable para saber la posicion de cada ' ' entre los N valores.
        int pos = 0;
        // Se genera un vector auxiliar para llenar la matriz.
        vector<int> temp_vect;
        // Se separan y obtienen los N valores de cada linea.
        for (int j=0; j < 10; j++){
            pos = text.find(" ");
            string val = text.substr(0,pos);
            text = text.substr(pos+1);
            // Se almacena cada valor.
            grid[i][j] = stoi(val);
        }

        // Se hace un push al vector 'vect' (tamaño MxN) del vector temporal 'temp_vect' (tamaño N)
        vect.push_back(temp_vect);
        temp_vect.clear();
    }


      int D[10][10]={{0, 769, 954, 952, 945, 104, 934, 347, 164, 365},
  {769, 0 ,718, 832, 162, 723, 228, 758, 424, 606},{954 ,718, 0, 488, 834, 197, 913, 196, 585, 895},
  {952, 832, 488, 0, 475, 100, 658, 842 ,229, 646},{945, 162, 834, 475, 0, 119, 185, 193, 313, 175},
  {104, 723, 197, 100, 119, 0, 537, 647, 916, 401},{934, 228, 913, 658, 185, 537, 0 ,429, 112, 207},{347, 758, 196, 842, 193, 647, 429, 0 ,249 ,259},{164, 424, 585, 229, 313, 916, 112, 249, 0 ,694},{365, 606, 895, 646, 175, 401, 207, 259, 694, 0}};

    floyd(D,10);

  return 0;
}