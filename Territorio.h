#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <iostream> //contains string stuff
#include <string>
#include <vector>

using namespace std;

class Territorio {
protected: 
    string nome;
    int resistencia=0;
    bool conquistado=0;
    int nRondasConquistado = 0;
public:

    
    string getNome();

    int getResistencia() const;

    virtual int getProdutos() =0;

    virtual Territorio* clone() const = 0;

    virtual int getOuro() =0;

    virtual int getPontos() =0;
    ~Territorio();

    bool getConquistado() const;
    int atualizaRondas();

    void setConquistado(bool newState);

};

class TerritorioInicial : public Territorio {
    
public:
    TerritorioInicial();
    TerritorioInicial* clone() const;
    int getPontos(){ return 0;};
    
    int getProdutos(){return 1;};
    int getOuro(){ return 1;};
};


#endif