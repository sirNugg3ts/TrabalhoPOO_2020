#include "Territorio.h"
#include "Interface.h"
#include "Continente.h"
#include "Mundo.h"

using namespace std;

int main() {

    Mundo mundo;

    //territorio inicial
    mundo.criaTerritorioInicial();

    Imperio *imperio = new Imperio(mundo);

    //cria interface
    Interface *interface = new Interface(mundo);

    interface->run(mundo, *imperio);

    for (int i = 0;i < mundo.territorios.size();i++)
		delete mundo.territorios[i];
    
    delete imperio;
    delete interface;

    return 0;
}