#ifndef CONTINENTE_H
#define CONTINENTE_H

#include "Territorio.h"

using namespace std;

class Planicie : public Territorio{

public:
    int static nPlanicie;
    Planicie();
    Planicie(const Planicie& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Planicie* clone() const override;

};

class Montanha : public Territorio{
public:
    int static nMontanha;
    int nRondasConquistado;
    Montanha();
    Montanha(const Montanha& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    void atualizaRondasConquistado();
    Montanha* clone() const override;
};

class Fortaleza : public Territorio{
public:
    int static nFortaleza;
    Fortaleza();
    Fortaleza(const Fortaleza& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Fortaleza* clone() const override;
};

class Mina : public Territorio{
public:
    int static nMina;
    Mina();
    Mina(const Mina& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Mina* clone() const override;
};

class Duna : public Territorio{
public:
    int static nDuna;
    Duna();
    Duna(const Duna& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Duna* clone() const override;
};

class Castelo : public Territorio{
public:
    int static nCastelo;
    Castelo();
    Castelo(const Castelo& other);
    int getProdutos() override;
    int getOuro() override;
    int getPontos() override;
    Castelo* clone() const override;
};

#endif