#include "Mundo.h"
#include "Territorio.h"
#include <iostream> //contains string stuff
#include <string>
#include <sstream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>

Mundo::Mundo(){
    vector<Territorio*> lT;
}
Mundo::~Mundo(){}

void Mundo::carrega(string ficheiro){
    string str, aux, tipo, comandos;
    int n, contador=0;
    ifstream file(ficheiro);

    if(file.is_open()){
        while (getline(file, str)) {
            if (str != "") {
                istringstream bufi(str);
                contador = 0;
                while (getline(bufi, aux, ' ')) {
                    contador++;
                    tipo = "";
                    if (contador == 1) {
                        comandos = aux;
                    }
                    else if (contador == 2) {
                        tipo = aux;
                    }
                    else if (contador == 3) {
                        n = atoi(aux.c_str());
                    }
                }
                Territorio* p = new Territorio(lT, comandos, tipo, n);
                lT.push_back(p);
            }
        }
        cout << "Territorios carregados com sucesso!";
    }
    else {
        cout << "[Warn] Erro a carregar o ficheiro\n";
    }
    file.close();
}

string Mundo::lista() {
    int contador = 1;
    ostringstream buff;
    buff << endl << endl << "Territorios:" << endl << endl;
    for (Territorio* p : lT) {
        buff << contador++ << " Nome: " << p->getNome() << endl;
    }
    return buff.str();
}