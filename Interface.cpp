#include <iostream>
#include "Interface.h"
#include <string>
#include <fstream>
#include <sstream>

void Interface::apresentaListaComandos() {
    if (stage==0){
        cout << "Comandos disponíveis:" << endl;
        cout << "cria *tipo de territorio* *numero de territorios*" <<endl;
        cout << "carrega *nomeFicheiro*" << endl;
        cout << "lista <nomeTerritorio>" << endl;
        cout << "sair" << endl;
        cout << "Comando: ";
    }
}

int Interface::run(Mundo& mundo){
    //apresentar lista de comandos
    apresentaListaComandos();

    //receber o comando e processar o mesmo
    processaComando(mundo);
}


Interface::Interface(Mundo& mundo){
    stage=0;
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

void Interface::processaComando(Mundo& mundo){

    string comando;
    getline(cin,comando);
    stringstream ss(comando);
    ss >> comando;

    if(comando == "cria"){
        string tipo;
        int n;
        ss >> tipo;
        ss >> n;

        mundo.criaTerritorio(tipo,n);
    }else if(comando == "carrega"){
        string nomeFicheiro;
        ss >> nomeFicheiro;
        Interface::processaFicheiro(nomeFicheiro,mundo);
    }else if(comando == "sair"){

    }
}

void Interface::processaComando(istringstream& iss,Mundo& mundo){

    string comando;
    getline(iss,comando);
    stringstream ss(comando);
    ss >> comando;

    if(comando == "cria"){
        string tipo;
        int n;
        ss >> tipo;
        ss >> n;

        mundo.criaTerritorio(tipo,n);
    }else if(comando == "carrega"){
        string nomeFicheiro;
        ss >> nomeFicheiro;
        Interface::processaFicheiro(nomeFicheiro,mundo);
    }
}

Interface::~Interface() {
    cout << "A terminar..." << endl;
}