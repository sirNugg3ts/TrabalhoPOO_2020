#ifndef ILHAS_H
#define ILHAS_H

#include "Territorio.h"
#include "Mundo.h"

using namespace std;

class Refugio : public Territorio {

public:
    int static nRefugio;
    string tipo;
    Refugio();
    Refugio(const Refugio& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Refugio* clone() const override;
};

class Pescaria : public Territorio {

public:
    int static nPescaria;
    string tipo;
    Pescaria();
    Pescaria(const Pescaria& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Pescaria* clone() const override;
};

#endif