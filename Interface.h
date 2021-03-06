#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Mundo.h"
#include "Imperio.h"

/*
 * int stage: 0 - Configuração
 *            1 - In-Game
 *            2 - Endgame
 *
 * int fase: 0 - Conquistar/Passar
 *           1 - Recolher produtos/ouro
 *           2 - Comprar unidade militar / Obter tecnologia
 *           3 - Eventos
 * */

using namespace std;

class Interface {
private:


    
public:

    int static ano, turno;
    int stage;
    int menu;
    int fase;
    explicit Interface(Mundo &);

    ~Interface();

    void run(Mundo &mundo, Imperio &imperio);

private:
    void processaFicheiro(const string &nomeFicheiro, Mundo &mundo);

    void apresentaListaComandos(int menu);

    int processaComando(Mundo &mundo, Imperio &imperio);

    void processaComandoDoFicheiro(istringstream &iss, Mundo &mundo);

    int processaComandoJogo(Mundo &mundo, Imperio &imperio);
    void forcaEventos(int evento, Mundo& mundo, Imperio& imperio);
    void checkIfEndgame(Mundo&,Imperio&);
    void passaTurno(Imperio& imperio);
};

#endif