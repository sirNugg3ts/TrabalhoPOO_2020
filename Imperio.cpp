#include "Imperio.h"

#include <cstdlib>
#include <ctime>
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

int Imperio::ConquistaImperio(Mundo& mundo,const string& nomeTerritorio){
    //returns: -1 - o territorio nao existe
    //          0 - tentou conquistar um territorio que ja existe
    //          1 - tentativa efetuada com sucesso, siga para a proxima fase



    Territorio* territorioConquistar = mundo.devolvePonteiroTerritorio(nomeTerritorio);

    if (territorioConquistar == nullptr)
        return -1;

    if (territorioConquistar->getNome()=="TerritorioInicial"){
        this->territoriosConquistados.push_back(territorioConquistar);
        return 1;
    }
    srand(time(0));

    int sorte = rand() % 6 + 1;
    int forcatotal = sorte + forcaMilitar;
    cout << "Resistencia do Territorio: " << territorioConquistar->getResistencia() << endl;
    cout << "Forca total: Sorte->" << sorte << " + Forca Militar: " << forcaMilitar << " = " << forcatotal << endl;
    if(forcatotal>=(territorioConquistar->getResistencia())) {
        if (!territorioConquistar->getConquistado()) {
            this->territoriosConquistados.push_back(territorioConquistar);
            territorioConquistar->setConquistado(true);
            cout << "Territorio conquistado com sucesso!" << endl;
        } else {
            cout << "Este territorio ja se encontra conquistado!" << endl;
            return 0;
        }
    }else{
            cout << "Forca insuficiente para conquistar" << endl;
            return 1;
    }
    return 1;
}

void Imperio::processaOuroProdutos(){
    int ouroObtido = 0;
    int produtosObtidos = 0;
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

            buff << contador++ << " Nome: " << p->getNome() <<
            " | Resistencia: " << p->getResistencia() <<
            " | Produtos por turno: " << p->getProdutos() <<
            " | Ouro por turno: " << p->getOuro() <<
            " | Pontos de vitoria: " << p->getPontos() << endl <<
            " Ouro disponivel: "<< this->getOuroImperio() <<
            " | Produtos disponivel: " << this->getProdutosImperio() << endl;

    }
    return buff.str();
}


