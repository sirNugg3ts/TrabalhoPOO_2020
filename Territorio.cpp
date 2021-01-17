#include "Territorio.h"
#include "Interface.h"

TerritorioInicial::TerritorioInicial(){
    this->nome = "TerritorioInicial";
    this->resistencia = 9;
    this->conquistado = true;
}


TerritorioInicial* TerritorioInicial::clone() const {
    return new TerritorioInicial();
}


string Territorio::getNome() {
    return this->nome;
}

int Territorio::getResistencia() const {
    return this->resistencia;
}


bool Territorio::getConquistado() const {
    return this->conquistado;
}

void Territorio::setConquistado(bool newState) {
    this->conquistado = newState;
}

Territorio::~Territorio(){
    cout << "Apagado territorio" << this->getNome() << endl;
}



