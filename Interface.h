#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Mundo.h"

/*
 * int stage: 0 - Configuração
 *            1 - In-Game
 *            2 - Endgame
 * */


using namespace std;

class Interface{
private:
    int stage;


public:
    Interface(Mundo&);
    ~Interface();
    int run(Mundo &mundo);

private:
    static void processaFicheiro(const string& nomeFicheiro,Mundo& mundo);
    void apresentaListaComandos();

    static void processaComando(Mundo &mundo);

    static void processaComando(istringstream &iss, Mundo &mundo);


};



#endif 