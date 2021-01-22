#include "Ilhas.h"
#include "Interface.h"

int Refugio::nRefugio = 0;
int Pescaria::nPescaria = 0;

Refugio::Refugio() {
    nome = "Refugio" + std::to_string(Refugio::nRefugio);
    resistencia = 9;
    conquistado = false;
    tipo = "ilha";
    Refugio::nRefugio++;
    cout << "Territorio '" << nome << "' criado" << endl;
};

Refugio::Refugio(const Refugio& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    tipo = other.tipo;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

Refugio* Refugio::clone() const {
    return new Refugio(*this);
}

int Refugio::getProdutos() {
    return 0;
};

int Refugio::getOuro() {
    return 1;
};

int Refugio::getPontos()
{
    return 2;
};

Pescaria::Pescaria() {
    nome = "Pescaria" + std::to_string(Pescaria::nPescaria);
    resistencia = 9;
    conquistado = false;
    tipo = "ilha";
    Pescaria::nPescaria++;
    cout << "Territorio '" << nome << "' criado" << endl;
};


Pescaria::Pescaria(const Pescaria& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    tipo = other.tipo;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

Pescaria* Pescaria::clone() const {
    return new Pescaria(*this);
}

int Pescaria::getProdutos() {

    if (Interface::ano == 1)
        return 2;
    else
        return 4;
};

int Pescaria::getOuro() {
    return 0;
};

int Pescaria::getPontos()
{
    return 2;
};
