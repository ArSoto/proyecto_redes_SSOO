#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

class Maquina{

private:

    char **matrizDisparos;
    char **matrizEmbarcaciones;
    int *posicionPortaaviones;
    int *posicionBuques;
    int *posicionSubmarinos;
    int *posicionLanchas;



public:

    void mostrarMatriz(char **matriz){

        cout << endl;

        for(int i = 0; i<15; i++){
            for(int j = 0; j<15; j++){
                cout << matriz[i][j];
            }
            cout << "\n" ;
        }
    }

    Maquina(){
        /**Inicialización Matrices -> Relleno con ceros**/
        this->matrizDisparos = new char*[15];
        this->matrizEmbarcaciones = new char*[15];

        for(int i=0; i<15; i++){
            matrizDisparos[i] = new char[15];
            matrizEmbarcaciones[i] = new char[15];
        }

        for(int i = 0; i<15; i++){
            for(int j = 0; j<15; j++){
                matrizDisparos[i][j] = '0';
                matrizEmbarcaciones[i][j] = '0';
            }
        }
    }

    void modificarMatrizEmbarcaciones(){ /**Utiliza direccion <- COLUMNA+FILA+TIPO**/

        cout << "\t\tEMBARCACIONES\n"
                "----------------------------\n"
                "PORTAAVIONES (1): 5 Casillas\n"
                "LANCHAS (3): 1 Casilla\n"
                "BUQUES (2): 4 Casillas\n"
                "SUBMARINOS (2): 3 Casillas\n"
                "----------------------------\n";

        direccionPortaaviones();
        direccionBuques();
        direccionSubmarinos();
        direccionLanchas();
    }

    void direccionPortaaviones(){

        int columna;
        int fila;
        char orientacion;


        cout << "DIRECCIONES: \n"
                "----------------------------\n"
                "\t\tPortaaviones: "
                "\nHorizontal(H) o Vertical(V): ";
        cin >> orientacion;

        if(orientacion == 'H' || orientacion == 'h'){ /**Misma fila**/

            cout << "Indique fila: ";
            cin >> fila;

            cout << "Ingrese primera columna: ";
            cin >> columna;

            /**IDEA...FALTA COMPROBAR QUE NO SE OCUPE POSICION CON OTRO BARCO Y QUE CAIGA EN EL ESPACIO A OCUPAR**/
            int cont = -1;
            int largo = 0;
            int pColumna = columna + cont;

            while(largo < 5) {
                if (enRango(pColumna, fila - 1) && matrizEmbarcaciones[fila-1][pColumna] == '0') {
                    matrizEmbarcaciones[fila - 1][pColumna] = 'P';
                    largo++;
                    cont++;
                    pColumna = columna + cont;

                    while (pColumna > 15 || (matrizEmbarcaciones[fila-1][pColumna] != '0')) {
                        cont--;
                        pColumna = columna + cont;
                    }
                }
            }

        }else if(orientacion == 'v' || orientacion == 'V'){ /**Misma columna**/
            cout << "Indique fila: ";
            cin >> fila;

            cout << "Ingrese primera columna: ";
            cin >> columna;

            int cont = -1;
            int largo = 0;
            int pfila = fila + cont;


            while(largo < 5){

                if(enRango(columna-1, pfila) && matrizEmbarcaciones[pfila][columna-1] == '0') {

                    matrizEmbarcaciones[pfila][columna - 1] = 'P';
                    largo++;
                    cont++;
                    pfila = fila + cont;

                    while (pfila == 15 || (matrizEmbarcaciones[pfila][columna-1] != '0')) {
                        cont--;
                        pfila = fila + cont;

                    }
                }
            }
        }
        mostrarMatriz(matrizEmbarcaciones);
    }

    void direccionBuques(){ /**2 buques de 4 casillas**/
        int contBuques = 0;
        int fila;
        int columna;

        char orientacion = ' ';

        while(contBuques!= 2){
            cout << "DIRECCIONES: \n"
                    "----------------------------\n"
                    "\t\tBuques: "
                    "\nHorizontal(H) o Vertical(V): ";
            cin >> orientacion;

            if (orientacion == 'H' || orientacion == 'h') {

                cout << "Indique fila: ";
                cin >> fila;

                cout << "Ingrese primera columna: ";
                cin >> columna;

                int largo = 0;
                int cont = -1;
                int bColumna = columna + cont;


                while (largo < 4) {

                    if (enRango(bColumna, fila - 1) && matrizEmbarcaciones[fila - 1][bColumna] == '0') {
                        matrizEmbarcaciones[fila - 1][bColumna] = 'B';
                        largo++;
                        cont++;
                        bColumna = columna + cont;

                        while (bColumna > 15 || (matrizEmbarcaciones[fila - 1][bColumna] != '0')) {
                            cont--;
                            bColumna = columna + cont;
                        }
                    }
                }
            }

            if(orientacion == 'v' || orientacion == 'V') {

                int largo = 0;
                int cont = -1;

                cout << "Indique fila: ";
                cin >> fila;

                int bFila = fila + cont;

                cout << "Ingrese primera columna: ";
                cin >> columna;

                while (largo < 4) {

                    if (enRango(columna - 1, bFila) && matrizEmbarcaciones[bFila][columna - 1] == '0') {

                        matrizEmbarcaciones[bFila][columna - 1] = 'B';
                        largo++;
                        cont++;
                        bFila = fila + cont;

                        while (bFila == 15 || (matrizEmbarcaciones[bFila][columna - 1] != '0')) {
                            cont--;
                            bFila = fila + cont;

                        }
                    }
                }
            }

            contBuques++;
            mostrarMatriz(matrizEmbarcaciones);
        }
    }

    void direccionSubmarinos(){
        int contSubmarinos = 0;
        int fila;
        int columna;

        char orientacion = ' ';

        while(contSubmarinos!= 2){
            cout << "DIRECCIONES: \n"
                    "----------------------------\n"
                    "\t\tSubmarinos: "
                    "\nHorizontal(H) o Vertical(V): ";
            cin >> orientacion;

            if (orientacion == 'h' || orientacion == 'H') {

                cout << "Indique fila: ";
                cin >> fila;

                cout << "Ingrese primera columna: ";
                cin >> columna;

                int largo = 0;
                int cont = -1;
                int sColumna = columna + cont;


                while (largo < 3) {

                    if (enRango(sColumna, fila - 1) && matrizEmbarcaciones[fila - 1][sColumna] == '0') {
                        matrizEmbarcaciones[fila - 1][sColumna] = 'S';
                        largo++;
                        cont++;
                        sColumna = columna + cont;

                        while (sColumna > 15 || (matrizEmbarcaciones[fila - 1][sColumna] != '0')) {
                            cont--;
                            sColumna = columna + cont;
                        }
                    }
                }
            }

            if(orientacion == 'V' || orientacion == 'v') {

                int largo = 0;
                int cont = -1;

                cout << "Indique fila: ";
                cin >> fila;

                int sFila = fila + cont;

                cout << "Ingrese primera columna: ";
                cin >> columna;

                while (largo < 3) {

                    if (enRango(columna - 1, sFila) && matrizEmbarcaciones[sFila][columna - 1] == '0') {

                        matrizEmbarcaciones[sFila][columna - 1] = 'S';
                        largo++;
                        cont++;
                        sFila = fila + cont;

                        while (sFila == 15 || (matrizEmbarcaciones[sFila][columna - 1] != '0')) {
                            cont--;
                            sFila = fila + cont;

                        }
                    }
                }
            }

            contSubmarinos++;
            mostrarMatriz(matrizEmbarcaciones);

        }

    }

    void direccionLanchas(){
        int contLanchas = 0;
        int fila;
        int columna;

        char orientacion = ' ';

        while(contLanchas!= 3){
            cout << "DIRECCIONES: \n"
                    "----------------------------\n"
                    "\t\tLanchas: "
                    "\nHorizontal(H) o Vertical(V): ";
            cin >> orientacion;

            if (orientacion == 'h' || orientacion == 'H') {

                cout << "Indique fila: ";
                cin >> fila;

                cout << "Ingrese primera columna: ";
                cin >> columna;

                int largo = 0;
                int cont = -1;
                int lColumna = columna + cont;


                while (largo < 1) {

                    if (enRango(lColumna, fila - 1) && matrizEmbarcaciones[fila - 1][lColumna] == '0') {
                        matrizEmbarcaciones[fila - 1][lColumna] = 'S';
                        largo++;
                        cont++;
                        lColumna = columna + cont;

                        while (lColumna > 15 || (matrizEmbarcaciones[fila - 1][lColumna] != '0')) {
                            cont--;
                            lColumna = columna + cont;
                        }
                    }
                }
            }

            if(orientacion == 'V' || orientacion == 'v') {

                int largo = 0;
                int cont = -1;

                cout << "Indique fila: ";
                cin >> fila;

                int lFila = fila + cont;

                cout << "Ingrese primera columna: ";
                cin >> columna;

                while (largo < 3) {

                    if (enRango(columna - 1, lFila) && matrizEmbarcaciones[lFila][columna - 1] == '0') {

                        matrizEmbarcaciones[lFila][columna - 1] = 'S';
                        largo++;
                        cont++;
                        lFila = fila + cont;

                        while (lFila == 15 || (matrizEmbarcaciones[lFila][columna - 1] != '0')) {
                            cont--;
                            lFila = fila + cont;

                        }
                    }
                }
            }

            contLanchas++;
            mostrarMatriz(matrizEmbarcaciones);

        }



    }
    bool enRango(int columna, int fila){
        bool excede = false;
        if((columna >= 0 && columna < 15) && (fila >= 0 && fila < 15)){
            excede = true;
        }
        return excede;
    }

    /**REVISAR**/
    bool interrupcion(int columna, int fila, char **matriz, int largo, char identificador){
        bool interrumpe = false;

        if(matriz[fila][columna] != '0' && matriz[fila][columna] != identificador){
            interrumpe = true;
        }

        return interrumpe;
    }





};