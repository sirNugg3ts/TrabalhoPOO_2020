#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "Territorio.h"


using namespace std;

class Mundo{
private:
    vector<Territorio*> lT;


public:
    Mundo();
    string lista();
    ~Mundo();
    //void criaTerritorioInicial();
    //void criaTerritorio(const string& tipo,int n);
    void carrega(string ficheiro);
};
#endif