#include <iostream>
#include "Interface.h"
#include <string>
#include <fstream>
#include <sstream>

/*
 * int stage: 0 - Configuração
 *            1 - In-Game
 *            2 - Endgame
 *
 * int fase: 0 - Conquistar/Passar
 *           1 - Recolher produtos/ouro
 *           2 - Comprar unidade militar / Obter tecnologia
 *           3 - Eventos
 * */

const int MAXTURNOS = 12;

Interface::Interface(Mundo& mundo){
    stage=0;
    turno=0;
    fase=1;
}
Interface::~Interface() {
    cout << "A terminar..." << endl;
}

void Interface::apresentaListaComandos() const {
    switch(stage){
        case 0:
            cout << "Comandos disponiveis:" << endl;
            cout << " - cria <tipo de territorio> <numero de territorios>" <<endl;
            cout << " - carrega <nomeFicheiro>" << endl;
            cout << " - lista " << endl; // mostra todos os detalhes
            cout << " - lista <nomeTerritorio> " << endl; // mostra os detalhes de 1 território
            cout << " - listai " << endl;
            cout << " - comecajogo" << endl;
            cout << " - sair" << endl;
            cout << "Comando: ";
            break;
        case 1:
            cout << "Comandos disponiveis:" << endl;
            cout << " - conquista <nomeTerritorio>" << endl;
            cout << " - lista <nomeTerritorio>" << endl;
            cout << " - listai " << endl;
            cout << " - sair" << endl;
            cout << "Comando: ";
            break;
    }
}


void Interface::run(Mundo& mundo,Imperio& imperio){
    while(true){
        switch (stage) {
            case 0: { // configuracao

                apresentaListaComandos();

                //receber o comando e processar o mesmo
                int status = processaComando(mundo, imperio); //if status = 1 -> Sair
                if (status)
                    return;
                break;
            }
            case 1: // in-game
                if (fase==1)
                    apresentaListaComandos();
                if(processaComandoJogo(mundo,imperio))
                    return;
                checkIfEndgame(); //se chegar ao maxturnos vai para stage 2
                break;
            case 2:  //end game
                break;
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

int Interface::processaComando(Mundo& mundo,Imperio& imperio){

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
    }else if(comando == "lista"){
        if(ss.good()){
            string nomeTerritorio;
            ss >> nomeTerritorio;
            cout << mundo.lista(nomeTerritorio);
        }else{
            cout << mundo.lista();
        }
    }else if(comando == "listai"){
        cout << imperio.listai();
    }
    else if(comando == "sair"){
        return 1;
    }else{
        cerr << "Comando invalido!" << endl;
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
    }else if(comando == "lista"){
        if(ss.good()){
            string nomeTerritorio;
            ss >> nomeTerritorio;
            cout << mundo.lista(nomeTerritorio);
        }else{
            cout << mundo.lista();
        }
    }else if(comando == "comecajogo"){
        stage = 1;
    }else{
        cerr << "Comando " << comando << " invalido em ficheiro!" << endl;
    }
}

// Comandos de stage 1 -> Execução do jogo (in-game)

void Interface::passaTurno(){
    cout.flush();
    cout << "*******************" <<endl
         << "FIM DO TURNO " << turno << endl
         << "*******************" << endl;
    turno++;
}

void Interface::checkIfEndgame(){
    if (turno == MAXTURNOS){
        stage = 2;
    }
}

int Interface::processaComandoJogo(Mundo& mundo,Imperio& imperio){

    switch (fase) {
        case 1:{
            //ler o comando
            string comando;
            getline(cin,comando);
            stringstream ss(comando);
            ss >> comando;

            if(comando == "conquista") {
                if (ss.good()) {
                    string nomeTerritorio;
                    ss >> nomeTerritorio;
                    if(imperio.ConquistaImperio(mundo, nomeTerritorio)==1)
                        fase = 2;
                }else{
                    cerr << "Argumentos em falta no conquista! Sintaxe: conquista <nomeTerritorio>" << endl;
                }
            }else
            if(comando == "lista") {
                if (ss.good()) {
                    string nomeTerritorio;
                    ss >> nomeTerritorio;
                    cout << mundo.lista(nomeTerritorio) <<endl;
                } else {
                    cout << mundo.lista() <<endl;
                }
            }else if(comando == "listai"){
                cout << imperio.listai() << endl;
            }else if(comando == "sair"){
                return 1;
            }else if(comando != "passa")
                cerr << "Comando invalido!" << endl;
            else
                fase=2;
                break;
        }
        case 2:
            //Fase de recolha de produtos e ouro
            imperio.processaOuroProdutos();
            fase++;
            break;

        case 3:{


            cout << "Deseja comprar uma unidade militar? (s/n): ";
            //ler o comando
            string comando;
            getline(cin,comando);
            stringstream ss(comando);
            ss >> comando;

            if (comando == "s") {
                imperio.compraUnidadeMilitar();
                fase++;
            }else if(comando == "n"){
                fase++;
            }else{
                cerr << "Comando '" << comando << "' invalido!" << endl;
            }
            break;
        }

        default: //aka fase 4
            fase = 1;
            passaTurno();
            break;
    }
    return 0;
}