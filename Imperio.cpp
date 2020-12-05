#include "Imperio.h"
#include <cstdlib>
#include <time.h>
#include <sstream>

using namespace std;

Imperio::Imperio(Mundo& mundo) {
    ConquistaImperio(mundo,"TerritorioInicial");
    this->armazemProdutos=0;
    this->cofreOuro=0;
    this->tamArmazem = this->tamCofre = 3;
    forcaMilitar = 0;
    maxForcaMilitar=3;
}

int Imperio::getOuroImperio() const{
    return this->cofreOuro;
}

int Imperio::getProdutosImperio() const {
    return this->armazemProdutos;
}

void Imperio::ConquistaImperio(Mundo& mundo,const string& nomeTerritorio){
    Territorio* territorioConquistar = mundo.devolvePonteiroTerritorio(nomeTerritorio);
    srand(time(0));

    int sorte = rand() % 6 + 1;
    int forcatotal = sorte + forcaMilitar;
    if(forcatotal>=(territorioConquistar->getResistencia())) {
        if (!territorioConquistar->getConquistado()) {
            this->territoriosConquistados.push_back(territorioConquistar);
            territorioConquistar->setConquistado(true);
        } else {
            cerr << "Este territorio ja se encontra conquistado!" << endl;
        }
    }else{
            cerr << "Força insuficiente para conquistar" << endl;
    }
}

void Imperio::processaOuroProdutos(){
    int ouroObtido;
    int produtosObtidos;
    for(Territorio* p : territoriosConquistados){
        for (int i = 0; i < p->getOuro(); ++i) {
            if(cofreOuro<tamCofre){
                cofreOuro++;
                ouroObtido++;
            }else{
                cout << "Cofre de ouro cheio!" << endl;
                break;
            }
        }
        for (int i = 0; i < p->getProdutos(); ++i) {
            if (armazemProdutos<tamArmazem){
                armazemProdutos++;
                produtosObtidos++;
            }else{
                cout << "Armazem de produtos cheio!" << endl;
                break;
            }
        }
    }
    cout << "Ouro obtido dos territorios: " << ouroObtido << endl << "Produtos obtidos dos territorios: " << produtosObtidos << endl;
}

void Imperio::compraUnidadeMilitar(){
    if(cofreOuro>0 && armazemProdutos>0 && forcaMilitar<maxForcaMilitar){
        cofreOuro--;
        armazemProdutos--;
        forcaMilitar++;
    }else{
        if (cofreOuro<1){
            cerr << "Ouro insuficiente" << endl;
        }else if(armazemProdutos<1){
            cerr << "Produto insuficiente" << endl;
        }else if(forcaMilitar==maxForcaMilitar){
            cerr << "Forca militar maxima alcancada!" << endl;
        }
    }
}

string Imperio::listai(){
    int contador = 1;
    ostringstream buff;
    buff << endl << endl << "Territorios:" << endl;
    for (Territorio *p : this->territoriosConquistados) {
            buff << contador++ << " Nome: " << p->getNome() << " | Resistencia: " << p->getResistencia() << " | Produtos por turno: " << p->getProdutos() << " | Ouro por turno: " << p->getOuro() << " | Pontos de vitoria: " << p->getPontos() << endl << " Ouro disponivel: "<< this->getOuroImperio() << " | Produtos disponivel: " << this->getProdutosImperio() << endl;
            //todo: acrescentar informação

    }
    return buff.str();
}


