#include "Mundo.h"
#include <sstream>

Mundo::Mundo(){}
Mundo::~Mundo(){}

void Mundo::criaTerritorioInicial(){
    this->territorios.push_back(new Territorio("Territorio Inicial"));
}

void Mundo::criaTerritorio(const string& tipo,int n){
    for (int i = 0; i < n; i++)
    {
        this->territorios.push_back(new Territorio(tipo));

    }

    
}

string Mundo::lista() {
    int contador = 1;
    ostringstream buff;
    buff << endl << endl << "Territorios:" << endl << endl;
    for (Territorio* p : territorios) {
        buff << contador++ << " Nome: " << p->getNome() << endl;
    }
    return buff.str();}