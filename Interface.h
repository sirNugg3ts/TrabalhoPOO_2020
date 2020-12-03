#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Mundo.h"

using namespace std;

class Interface{

public:
    Interface(Mundo&);
    ~Interface();

private:
    static void processaComando(const string& comando,string argumentos[],Mundo& mundo);
    static void processaFicheiro(const string& nomeFicheiro,Mundo& mundo);
    void apresentaListaComandos();
    static string recebeComando();


};



#endif