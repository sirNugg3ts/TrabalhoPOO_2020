#include "Mundo.h"
#include <sstream>
#include "Imperio.h"

Mundo::Mundo(){}
Mundo::~Mundo(){}

void Mundo::criaTerritorioInicial(){
    this->territorios.push_back(new Territorio("Territorio Inicial"));
}

void Mundo::criaTerritorio(const string& tipo,int n){
    for (int i = 0; i < n; i++)
        this->territorios.push_back(new Territorio(tipo));
}

string Mundo::lista() {
    int contador = 1;
    ostringstream buff;
    buff << endl << endl << "Territorios:" <<endl;
    for (Territorio *p : territorios) {
        buff << contador++ << " Nome: " << p->getNome() << " | Resistencia: " << p->getResistencia() << " | Produtos por turno: " << p->getProdutos() << " | Ouro por turno: " << p->getOuro() << " | Pontos de vitoria: " << p->getPontos() << endl;
        //todo: acrescentar informação
    }
    return buff.str();
}

string Mundo::lista(const string& nomeTerritorio) {
    int contador = 1;
    int found = 0;
    ostringstream buff;
    buff << endl << endl << "Territorios:" << endl;
    for (Territorio *p : territorios) {
        if (p->getNome() == nomeTerritorio){
            found = 1;
            buff << contador++ << " Nome: " << p->getNome() << " | Resistencia: " << p->getResistencia() << " | Produtos por turno: " << p->getProdutos() << " | Ouro por turno: " << p->getOuro() << " | Pontos de vitoria: " << p->getPontos() << endl;
            //todo: acrescentar informação
        }
    }
    if (!found){
        cerr << "Territorio nao encontrado" << endl;
    }
    return buff.str();
}


Territorio* Mundo::devolvePonteiroTerritorio(const string& nomeTerritorio){
    for(Territorio *p : territorios){
        if(p->getNome() == nomeTerritorio)
            return p;
    }
    return nullptr;
}