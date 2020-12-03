#include <iostream>
#include "Interface.h"
#include <string>
#include <fstream>
#include <sstream>
void Interface::apresentaListaComandos() {

}
Interface::Interface(Mundo& mundo){

    //apresentar lista de comandos
    apresentaListaComandos();

    //espera por comando e processa em args
    recebeComando();

    //processa a string em argumentos




}

string* stringTokenizer(const string& comando){
    string argumentos[3];
    stringstream ssin(comando);

    for (int i = 0;ssin.good(); ++i) {
        if(i > 2){
            cerr << "Foram inseridos argumentos a mais no comando que serão ignorados" << endl;
            break;
        }
        ssin >> argumentos[i];
    }
    return argumentos; //isto nao deve funcionar, ou dá memory leak
}

void Interface::processaComando(const string& comando, string *argumentos, Mundo &mundo) {
    if (comando == "cria")
    {
        string tipo = argumentos[1];
        int n = stoi(argumentos[2]);

        mundo.criaTerritorio(tipo,n);
        return;
    }
}

void Interface::processaFicheiro(const string &nomeFicheiro, Mundo &mundo) {
    //abrir o ficheiro
    ifstream ficheiro;
    ficheiro.open(nomeFicheiro);

    cout << "A ler ficheiro " << nomeFicheiro << "..." << endl;

    if(ficheiro.is_open()){
        //abriu com sucesso
        cout << "A processar o ficheiro..." << endl;
        string comandoLidoDoFile;
        istringstream ssin;
        while (getline(ficheiro,comandoLidoDoFile))
        {
            string argumentos[4];
            stringstream ssin(comandoLidoDoFile);

            for (int i = 0; ssin.good(); i++)
                ssin >> argumentos[i];
            Interface::processaComando(argumentos[0],argumentos,mundo);
        }

        ficheiro.close();
    }else{
        //não foi possível abrir o ficheiro
        cerr << "Erro ao abrir " << nomeFicheiro << endl;
    }
}

string Interface::recebeComando() {
    string comando;
    cout << "Comando: ";
    cin >> comando;
    return comando;
}


