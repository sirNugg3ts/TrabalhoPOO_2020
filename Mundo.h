#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "Territorio.h"


using namespace std;

class Mundo{
private:
    vector<Territorio*> territorios;


public:
    Mundo();
    string lista();
    ~Mundo();
    //void criaTerritorioInicial();
    //void criaTerritorio(const string& tipo,int n);
    void carrega(string ficheiro);

    void criaTerritorioInicial();

    void criaTerritorio(const string& tipo,int n);

};
#endif