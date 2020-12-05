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
    int turno;
    int fase;

public:
    explicit Interface(Mundo&);
    ~Interface();
    void run(Mundo& mundo,Imperio& imperio);

private:
    void processaFicheiro(const string& nomeFicheiro,Mundo& mundo);
    void apresentaListaComandos() const;

    int processaComando(Mundo& mundo,Imperio& imperio);
    void processaComandoDoFicheiro(istringstream &iss, Mundo &mundo);
    void processaComandoJogo(Mundo& mundo,Imperio& imperio);
    void checkIfEndgame();


    void passaTurno();
};
#endif 