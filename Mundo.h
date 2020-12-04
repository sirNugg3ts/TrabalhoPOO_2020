#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "Territorio.h"
#include <string>


using namespace std;

class Mundo{
private:
    vector<Territorio*> territorios;
public:
    Mundo();
    ~Mundo();

    void criaTerritorioInicial();
    void criaTerritorio(const string& tipo,int n);

    string lista(const string& nomeTerritorio);
    string lista();

};
#endif