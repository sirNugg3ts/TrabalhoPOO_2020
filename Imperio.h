#ifndef TRABALHOPOO_IMPERIO_H
#define TRABALHOPOO_IMPERIO_H

#include "Territorio.h"
#include "Mundo.h"

class Imperio {
private:
    
    int armazemProdutos;
    int cofreOuro;
    int tamArmazem, tamCofre;
    int forcaMilitar, maxForcaMilitar;
    int pesquisabolsa = 0;
    int pesquisadrones;
    int pesquisadefesa;
    int pesquisamisseis;
    int pesquisabanco;
    string ultimoConquistado;

public:
    vector<Territorio*> territoriosConquistados;
    Imperio(Mundo &mundo);
    Imperio();
    void clearImperioSearch();
    int contaPontos();

    vector<Territorio*> getVectorTerritorios();
    int ConquistaTerritorio(Mundo &mundo, const string &nomeTerritorio);

    void processaOuroProdutos();

    void ouropproduto();
    void produtopouro();
    void listaTecnologiaDisponiveis();
    int compraUnidadeMilitar();
    int adquireTech(string nomeTech);
    ostringstream listaTecnologiasObtidas();
    int getOuroImperio() const;

    int getProdutosImperio() const;

    int getMaxCofre() const;
    int getMaxArmazem() const;
    int getBolsa();
    int getDrones();
    int getMisseis();
    int getDefesa();
    int getBanco();
    void pesquisarBolsa();
    void pesquisarDefesa();
    void pesquisarDrones();
    void pesquisarMisseis();
    void pesquisarBanco();
    void apanharRecurso(int ano);
    int invasao(Mundo &mundo, int ano);
    void alianca();
    bool removeTerritorio(Territorio* apaga);
    string listai();
    Imperio& operator=(const Imperio& other);

    void setProdutosImperio(int i);
    void setOuroImperio(int i);
    void setTamCofre(int i);
    void setTamArmazem(int i);
    void setForcaMilitar(int i);
    void setMaxForcaMilitar(int i);
    void setUltimeConquistado(string i);
    string getUltimoConquistado();
    void tomaTerr(Mundo& mundo, string nome);
    void tomaTec(string nome);
    void modificaOuro(int valor);
    void modificaProdutos(int valor);


};

#endif //TRABALHOPOO_IMPERIO_H
