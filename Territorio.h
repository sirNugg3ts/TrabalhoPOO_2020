#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <iostream> //contains string stuff
#include <string>
#include <vector>

using namespace std;

class Territorio
{
private:
    string nome;
    string tipo;
    int resistencia;
    int produtosPorTurno;
    int ouroPorTurno;
    int pontos;
    bool conquistado;

    int static nTerritorioGenerico;
    
public:

    explicit Territorio(const string&);
    ~Territorio();

    string getNome();
    int getResistencia() const;
    int getProdutos() const;
    int getOuro() const;
    int getPontos() const;
    bool getConquistado() const;
    void setConquistado(bool newState);
};

#endif