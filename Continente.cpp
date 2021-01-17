#include "Continente.h"
#include "Interface.h"

int Planicie::nPlanicie = 0;
int Montanha::nMontanha = 0;
int Fortaleza::nFortaleza = 0;
int Mina::nMina = 0;
int Duna::nDuna = 0;
int Castelo::nCastelo = 0;

//Planicie
Planicie::Planicie(){
    nome="Planicie" + std::to_string(Planicie::nPlanicie);
    resistencia = 5;
    conquistado = false;
    Planicie::nPlanicie++;
    cout << "Territorio '" << nome << "' criado" << endl;
};

Planicie::Planicie(const Planicie& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

int Planicie::getProdutos(){
    
    if(Interface::ano == 1)
        return 1;
    else
        return 2;
};

int Planicie::getOuro(){
    return 1;
};

int Planicie::getPontos()
{
    return 1;
}

Planicie* Planicie::clone() const
{
    return new Planicie(*this);
}
;

//Montanha
Montanha::Montanha(){
    nome="Montanha" + std::to_string(Montanha::nMontanha);
    resistencia=6;
    conquistado= false;
    nRondasConquistado = 0;
    Montanha::nMontanha++;
    cout << "Territorio '" << nome << "' criado" << endl;
}

Montanha::Montanha(const Montanha& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    nRondasConquistado = other.nRondasConquistado;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

Montanha* Montanha::clone() const {
    return new Montanha(*this);
}

int Montanha::getOuro(){
    return 0;
}

int Montanha::getProdutos(){
    if (this->nRondasConquistado >= 2)
        return 1;
    else
        return 0;
}

int Montanha::getPontos() {
    return 1;
}

void Montanha::atualizaRondasConquistado(){

    if (this->conquistado == true)
        this->nRondasConquistado++;
    
};

//Fortaleza

Fortaleza::Fortaleza(){
    nome = "Fortaleza" + std::to_string(Fortaleza::nFortaleza);
    resistencia = 8;
    conquistado = false;
    Fortaleza::nFortaleza++;
    cout << "Territorio '" << nome << "' criado" << endl;
};
Fortaleza* Fortaleza::clone() const {
    return new Fortaleza(*this);
}

Fortaleza::Fortaleza(const Fortaleza& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

int Fortaleza::getProdutos(){return 0;};
int Fortaleza::getOuro(){return 0;};
int Fortaleza::getPontos() {
    return 1;
}

//Mina

Mina::Mina(){
    nome = "Mina" + std::to_string(Mina::nMina);
    resistencia = 5;
    conquistado = false;

    Mina::nMina++;
    cout << "Territorio '" << nome << "' criado" << endl;
};

Mina::Mina(const Mina& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

Mina* Mina::clone() const {
    return new Mina(*this);
}

int Mina::getProdutos(){return 0;};
int Mina::getOuro(){
    if(Interface::turno < 4){
        return 1;
    }else
        return 2;
};
int Mina::getPontos() {
    return 1;
}
//Duna

Duna::Duna(){
    nome = "Duna" + std::to_string(Duna::nDuna);
    resistencia = 4;
    conquistado = false;

    Duna::nDuna++;
    cout << "Territorio '" << nome << "' criado" << endl;
};

Duna::Duna(const Duna& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

Duna* Duna::clone() const {
    return new Duna(*this);
}

int Duna::getProdutos(){
    return 1;
}
int Duna::getOuro(){return 1;};
int Duna::getPontos() {
    return 1;
}
//Castelo

Castelo::Castelo(){
    nome = "Castelo" + std::to_string(Castelo::nCastelo);
    resistencia = 7;
    conquistado = false;

    Castelo::nCastelo++;
    cout << "Territorio '" << nome << "' criado" << endl;
};

Castelo::Castelo(const Castelo& other) {
    nome = other.nome;
    resistencia = other.resistencia;
    conquistado = other.conquistado;
    cout << "Territorio '" << nome << "' copiado" << endl;
}

Castelo* Castelo::clone() const {
    return new Castelo(*this);
}

int Castelo::getProdutos(){
    if (Interface::turno < 3)
        return 3;
    else
        return 0;
}

int Castelo::getOuro(){
    return 1;
}

int Castelo::getPontos() {
    return 1;
}
