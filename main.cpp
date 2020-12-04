#include <iostream> //contains string stuff
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Territorio.h"
#include "mundo.h"

using namespace std;

int main(){
    Mundo mundo;
    vector<Territorio*> lT;
    Mundo* pM = new Mundo();
    string comandoI, aux;
    vector<string> command;
    int i;

    cout << " Comandos:\n\n";
    cout << " carrega <nome_ficheiro.txt>\n cria <tipo_territorio> <quantidade>\n conquista <nome_territorio>\n lista\n";
    do {
        command.clear();
        cout << "Comando: ";
        getline(cin, comandoI);
        stringstream x(comandoI);
        while(getline(x, aux, ' ')){
            command.push_back(aux);
        }

        if (comandoI.length() == 0) {
            cout << "[Warn] Digite um comando ou help\n";
        }
        else if (command[0] == "help" && command.size() == 1) {
            cout << " Comandos:\n";
            cout << " carrega <nome_ficheiro.txt>\n cria <tipo_territorio> <quantidade>\n conquista <nome_territorio>\n lista\n";
        }
        else if (command[0] == "carrega" && command.size() == 2) {
            pM->carrega(command[1]);
            cout<< pM->lista();
        }
        }while(comandoI.length() == 0 || command[0] != "fim");

    return 0;
    }