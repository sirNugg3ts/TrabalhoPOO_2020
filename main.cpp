#include <iostream> //contains string stuff
#include <string>
#include <sstream>

#include "Territorio.h"
#include "Mundo.h"
#include "Interface.h"

using namespace std;

int Territorio::nTerritorioGenerico = 0;

int main(){
    Mundo mundo;

    //inserir territorio inicial
    mundo.criaTerritorioInicial();

    //cria interface
    Interface interface = Interface(mundo);

    

    }