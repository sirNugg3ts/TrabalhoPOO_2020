#include "Mundo.h"

Mundo::Mundo(){}
Mundo::~Mundo(){}

void Mundo::criaTerritorioInicial(){
    this->territorios.push_back(new Territorio("Territorio Inicial"));
}

void Mundo::criaTerritorio(const string& tipo,int n){
    for (int i = 0; i < n; i++)
    {
        this->territorios.push_back(new Territorio("TerritorioGenerico"));
    }
    cout << "Adicionado TerritorioGenerico " << n << " vezes" << endl;
    
}