#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include <string>
#include "Territorio.h"

using namespace std;

class Mundo {
private:

public:
    vector<Territorio *> territorios;

    Mundo();

    ~Mundo();

    void criaTerritorioInicial();

    void criaTerritorio(const string &tipo, int n);

    string lista(const string &nomeTerritorio);

    string lista();

    Territorio *devolvePonteiroTerritorio(const string &nomeTerritorio);
    Territorio *territorioAtacado(const string & ultimoConquistado);
};

#endif