#ifndef TRABALHOPOO_IMPERIO_H
#define TRABALHOPOO_IMPERIO_H

#include "Territorio.h"
#include "mundo.h"

class Imperio{
private:
    vector<Territorio*> territoriosConquistados;
    int armazemProdutos;
    int cofreOuro;
    int tamArmazem,tamCofre;
    int forcaMilitar,maxForcaMilitar;
public:
    Imperio(Mundo& mundo);
    int ConquistaImperio(Mundo& mundo,const string& nomeTerritorio);
    void processaOuroProdutos();
    void compraUnidadeMilitar();
    int getOuroImperio() const;
    int getProdutosImperio() const;

    string listai();

};
#endif //TRABALHOPOO_IMPERIO_H
