#include "Mundo.h"
#include "Continente.h"
#include "Ilhas.h"
#include <sstream>

void Mundo::criaTerritorioInicial() {
    this->territorios.push_back(new TerritorioInicial());
}

void Mundo::criaTerritorio(const string &tipo, int n) {
    for (int i = 0; i < n; i++){
        if (tipo == "Planicie")
        {
            this->territorios.push_back(new Planicie());
        }
        else if (tipo == "Montanha") {
            this->territorios.push_back(new Montanha());
        }
        else if (tipo == "Fortaleza") {
            this->territorios.push_back(new Fortaleza());
        }
        else if (tipo == "Mina") {
            this->territorios.push_back(new Mina());
        }
        else if (tipo == "Duna") {
            this->territorios.push_back(new Duna());
        }
        else if (tipo == "Castelo") {
            this->territorios.push_back(new Castelo());
        }
        else if (tipo == "Refugio") {
            this->territorios.push_back(new Refugio());
        }
        else if (tipo == "Pescaria") {
            this->territorios.push_back(new Pescaria());
        }
    }
        
}

string Mundo::lista() {
    int contador = 1;
    ostringstream buff;
    buff << endl << endl << "Territorios:" << endl;
    for (Territorio *p : territorios) {
        buff << contador++ << " Nome: " << p->getNome() << " | Resistencia: " << p->getResistencia()
             << " | Produtos por turno: " << p->getProdutos() << " | Ouro por turno: " << p->getOuro()
             << " | Pontos de vitoria: " << p->getPontos() << endl;
        //todo: acrescentar informação
    }
    return buff.str();
}

string Mundo::lista(const string &nomeTerritorio) {
    int contador = 1;
    int found = 0;
    ostringstream buff;
    buff << endl << endl << "Territorios:" << endl;
    for (Territorio *p : territorios) {
        if (p->getNome() == nomeTerritorio) {
            found = 1;
            buff << contador++ << " Nome: " << p->getNome() << " | Resistencia: " << p->getResistencia()
                 << " | Produtos por turno: " << p->getProdutos() << " | Ouro por turno: " << p->getOuro()
                 << " | Pontos de vitoria: " << p->getPontos() << endl;
            //todo: acrescentar informação
        }
    }
    if (!found) {
        cerr << "Territorio nao encontrado" << endl;
    }
    return buff.str();
}


Territorio *Mundo::devolvePonteiroTerritorio(const string &nomeTerritorio) {
    for (Territorio *p : territorios) {
        if (p->getNome() == nomeTerritorio)
            return p;
    }
    return nullptr;
}

Territorio *Mundo::territorioAtacado(const string& ultimoConquistado){
    for (Territorio* p : territorios) {
        if (p->getNome() == ultimoConquistado)
            return p;
    }
    return nullptr;
}

Mundo::~Mundo() = default;

Mundo::Mundo() = default;
