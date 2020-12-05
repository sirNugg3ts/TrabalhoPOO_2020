#include "Territorio.h"
#include "Interface.h"
#include "Imperio.h"
#include "mundo.h"
using namespace std;

int Territorio::nTerritorioGenerico = 0;

int main(){
    Mundo mundo;

    //territorio inicial
    mundo.criaTerritorioInicial();

    Imperio* imperio = new Imperio(mundo);

    //cria interface
    Interface* interface = new Interface(mundo);

    interface->run(mundo,*imperio);

    delete interface;

    exit(EXIT_SUCCESS);
    }