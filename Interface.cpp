#include <iostream>
#include "Interface.h"
#include <string>
#include <fstream>
#include <sstream>

void Interface::apresentaListaComandos() {
    //todo
}
void processaComando(istringstream &ssin,Mundo& mundo){
    string comando;
    ssin >> comando;

    if(comando == "cria"){
        string tipo;
        int n;
        ssin >> tipo;
        ssin >> n;

        mundo.criaTerritorio(tipo,n);



    }
}

Interface::Interface(Mundo& mundo){

    //apresentar lista de comandos
    apresentaListaComandos();

    //DEBUG
    processaFicheiro("teste.txt",mundo);

}
void Interface::processaFicheiro(const string &nomeFicheiro, Mundo &mundo) {
    //abrir o ficheiro
    ifstream ficheiro;
    ficheiro.open(nomeFicheiro);

    cout << "Vou tentar abrir o ficheiro " << nomeFicheiro << "..." << endl;

    if(ficheiro.is_open()){
        //abriu com sucesso
        cout << "A processar o ficheiro..." << endl;
        string comandoLidoDoFile;

        while (getline(ficheiro,comandoLidoDoFile))
        {
            istringstream iss(comandoLidoDoFile);
            processaComando(iss,mundo);
        }

        cout << mundo.lista();

        ficheiro.close();
    }else{
        //não foi possível abrir o ficheiro
        cerr << "Erro ao abrir " << nomeFicheiro << endl;
    }
}

Interface::~Interface() {

}




