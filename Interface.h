#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "mundo.h"
#include "Imperio.h"
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
    void run(Mundo &mundo);

private:
    static void processaFicheiro(const string& nomeFicheiro,Mundo& mundo);
    void apresentaListaComandos() const;

    int processaComando(Mundo &mundo);
    static void processaComandoDoFicheiro(istringstream &iss, Mundo &mundo);
};
#endif 