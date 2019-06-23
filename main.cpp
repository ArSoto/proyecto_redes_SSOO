
#include "Jugador.cpp"
#include "Maquina.cpp"

int *disparos; /**Vector disparos cliente**/


int main() {

    Maquina maquina = Maquina();

    maquina.modificarMatrizEmbarcaciones();

    return 0;
}