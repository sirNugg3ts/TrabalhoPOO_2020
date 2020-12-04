#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Mundo.h"

using namespace std;

class Interface{

public:
    explicit Interface(Mundo&);
    ~Interface();

private:
    static void processaFicheiro(const string& nomeFicheiro,Mundo& mundo);
    void apresentaListaComandos();
};



#endif