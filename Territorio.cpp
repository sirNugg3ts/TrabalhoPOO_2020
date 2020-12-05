#include "Territorio.h"

Territorio::Territorio(const string &tipo) {

    if (tipo == "Territorio Inicial") {
        nome = "TerritorioInicial";
        this->tipo = "Territorio Inicial";
        resistencia = 9;
        produtosPorTurno = 1;
        ouroPorTurno = 1;
        pontos = 0;
        conquistado = false;
    } else if (tipo == "TerritorioGenerico") {
        nome = "TerritorioGenerico" + std::to_string(nTerritorioGenerico);
        this->tipo = "Territorio Generico";
        resistencia = 3;
        produtosPorTurno = 1;
        ouroPorTurno = 1;
        pontos = 1;
        conquistado = false;

        nTerritorioGenerico++;
        cout << "Territorio '" << nome << "' criado" << endl;
    }
}

Territorio::~Territorio() = default;

string Territorio::getNome() {
    return this->nome;
}

int Territorio::getResistencia() const {
    return this->resistencia;
}

int Territorio::getProdutos() const {
    return this->produtosPorTurno;
}

int Territorio::getOuro() const {
    return this->ouroPorTurno;
}

int Territorio::getPontos() const {
    return this->pontos;
}

bool Territorio::getConquistado() const {
    return this->conquistado;
}

void Territorio::setConquistado(bool newState) {
    this->conquistado = newState;
}
