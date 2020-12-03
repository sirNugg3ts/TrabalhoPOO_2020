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

    int static nTerritorioGenerico;
    
public:
    
    
    Territorio(string);
    ~Territorio();
};

#endif