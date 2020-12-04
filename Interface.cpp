#include <iostream>
#include "Interface.h"
#include <string>
#include <fstream>
#include <sstream>

Interface::Interface(Mundo& mundo){
    stage=0;
}
Interface::~Interface() {
    cout << "A terminar..." << endl;
}

void Interface::apresentaListaComandos() const {
    if (stage==0){
        cout << "Comandos disponiveis:" << endl;
        cout << " - cria <tipo de territorio> <numero de territorios>" <<endl;
        cout << " - carrega <nomeFicheiro>" << endl;
        cout << " - lista <nomeTerritorio>" << endl;
        cout << " - comecajogo" << endl;
        cout << " - sair" << endl;
        cout << "Comando: ";
    }else if(stage==1){
        cout << "Comandos disponiveis:" << endl;
        cout << " - conquista <nomeTerritorio>" << endl;
        cout << " - lista <nomeTerritorio>" << endl;
        cout << " - sair" << endl;
        cout << "Comando: ";
    }
}


void Interface::run(Mundo& mundo){
    while(true){
        if (stage == 0){
            //apresentar lista de comandos
            apresentaListaComandos();

            //receber o comando e processar o mesmo
            int status;
            status = processaComando(mundo);

            if(status){
                return;
            }

        }else if(stage == 1){
            apresentaListaComandos();
        }
    }

}
//Comandos de stage 0 -> Inicialização

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
            processaComandoDoFicheiro(iss,mundo);
        }
        ficheiro.close();
    }else{
        //não foi possível abrir o ficheiro
        cerr << "Erro ao abrir " << nomeFicheiro << endl;
    }
}

int Interface::processaComando(Mundo& mundo){

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
    }else if(comando == "comecajogo"){
        stage = 1;
    }
    else if(comando == "lista"){
        if(ss.good()){
            string nomeTerritorio;
            ss >> nomeTerritorio;
            cout << mundo.lista(nomeTerritorio);
        }else if(comando == "comecajogo"){

        }
        else{
            cout << mundo.lista();
        }
    }
    else if(comando == "sair"){
        return 1;
    }
    return 0;
}

void Interface::processaComandoDoFicheiro(istringstream& iss,Mundo& mundo){

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

// Comandos de stage 1 -> Execução do jogo (in-game)

