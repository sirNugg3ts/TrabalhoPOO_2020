#include <iostream>
#include "Interface.h"
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "SaveLoad.h"

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
int Interface::ano = 1;
int Interface::turno = 1;
int turnoatual = 0;
int evento;
int forcaevento = 0;
int ultimafase;
vector<Save *> saves;

Interface::Interface(Mundo &mundo) {
    stage = 0;
    menu = 0;
    fase = 1;
}

Interface::~Interface() {
    for (auto e : saves)
        delete e;
    cout << "A terminar..." << endl;
}

void Interface::apresentaListaComandos(int menu) {  // apresentaListaComandos(menu);
    switch (menu) {
        case 0:
            cout << "*******************" << endl;
            cout << "Comandos disponiveis:" << endl;
            cout << " - cria <tipo de territorio> <numero de territorios>" << endl;
            cout << " - carrega <nomeFicheiro>" << endl;
            cout << " - lista " << endl; // mostra todos os detalhes
            cout << " - lista <nomeTerritorio> " << endl; // mostra os detalhes de 1 território
            cout << " - listaimperio " << endl;
            cout << " - listatecnologias" << endl;
            cout << " - avanca" << endl;
            cout << " - sair" << endl;
            cout << "*******************" << endl;
            cout << "Comando: ";
            break;
        case 1:
            cout << "*******************" << endl;
            cout << "Comandos disponiveis:" << endl;
            cout << " - conquista <nomeTerritorio>" << endl;
            cout << " - passa" << endl;
            cout << " - lista " << endl;
            cout << " - lista <nomeTerritorio>" << endl;
            cout << " - listaimperio " << endl;
            cout << " - listatecnologias" << endl;
            //new
            cout << " - toma <terr/tec> <nome>" << endl;
            cout << " - modifica <ouro/prod> <quantidade>" << endl;
            cout << " - fevento <nome>" << endl;
            cout << " - grava <nome>" << endl;
            cout << " - ativa <nome>" << endl;
            cout << " - apaga <nome>" << endl;
            //
            cout << " - sair" << endl;
            cout << "*******************" << endl;
            cout << "Comando: ";
            break;
        case 2:
            cout << "*******************" << endl;
            cout << "Comandos disponiveis:" << endl;
            cout << " - maisproduto" << endl; 
            cout << " - maisouro" << endl;
            cout << " - lista " << endl;
            cout << " - lista <nomeTerritorio>" << endl;
            cout << " - listaimperio " << endl;
            cout << " - listatecnologias" << endl;
            cout << " - avanca" << endl;
            //new
            cout << " - toma <terr/tec> <nome>" << endl;
            cout << " - modifica <ouro/prod> <quantidade>" << endl;
            cout << " - fevento <nome>" << endl;
            cout << " - grava <nome>" << endl;
            cout << " - ativa <nome>" << endl;
            cout << " - apaga <nome>" << endl;
            //
            cout << "*******************" << endl;
            cout << "Comando: ";
            break;
        case 3: 
            cout << "*******************" << endl;
            cout << "Comandos disponiveis:" << endl;
            cout << " - maismilitar" << endl;
            cout << " - adquire <tipo>" << endl;
            cout << " - lista " << endl;
            cout << " - lista <nomeTerritorio>" << endl;
            cout << " - listaimperio " << endl;
            cout << " - listatecnologias" << endl;
            cout << " - avanca" << endl;
            //new
            cout << " - toma <terr/tec> <nome>" << endl;
            cout << " - modifica <ouro/prod> <quantidade>" << endl;
            cout << " - fevento <nome>" << endl;
            cout << " - grava <nome>" << endl;
            cout << " - ativa <nome>" << endl;
            cout << " - apaga <nome>" << endl;
            //
            cout << "*******************" << endl;
            cout << "Comando: ";
            break;
        case 4:
            cout << "*******************" << endl;
            cout << "Comandos disponiveis:" << endl;
            cout << " - toma <terr/tec> <nome>" << endl;
            cout << " - modifica <ouro/prod> <quantidade>" << endl;
            cout << " - fevento <nome>" << endl;
            cout << "Para passar de turno digite avanca" << endl;
            cout << "*******************" << endl;
            cout << "Comando: ";
            break;
        case 5:
            cout << "*******************" << endl;
            cout << "Comandos disponiveis:" << endl;
            cout << " - lista " << endl;
            cout << " - lista <nomeTerritorio>" << endl;
            cout << " - listaimperio " << endl;
            cout << " - listatecnologias" << endl;
            cout << " - avanca " << endl;
            cout << " - toma <terr/tec> <nome>" << endl;
            cout << " - modifica <ouro/prod> <quantidade>" << endl;
            cout << " - fevento <nome>" << endl;
            cout << " - grava <nome>" << endl;
            cout << " - ativa <nome>" << endl;
            cout << " - apaga <nome>" << endl;
            cout << " - sair" << endl;
            cout << "*******************" << endl;
            cout << "Comando: ";
            break;
    }
}


void Interface::run(Mundo &mundo, Imperio &imperio) {
    while (true) {
        switch (stage) {
            case 0: { // configuracao

                apresentaListaComandos(menu);

                //receber o comando e processar o mesmo
                int status = processaComando(mundo, imperio); //if status = 1 -> Sair
                if (status)
                    return;
                break;
            }
            case 1: // in-game stage 1  
                if (processaComandoJogo(mundo, imperio))
                    return;
                checkIfEndgame(mundo, imperio);
                break;
            case 2:
                return;
                break;
        }
    }
}

//Comandos de stage 0 -> Inicialização

void Interface::processaFicheiro(const string &nomeFicheiro, Mundo &mundo) {
    //abrir o ficheiro
    ifstream ficheiro;
    ficheiro.open(nomeFicheiro);

    cout << "A abrir o ficheiro " << nomeFicheiro << "..." << endl;

    if (ficheiro.is_open()) {
        //abriu com sucesso
        cout << "A processar o ficheiro..." << endl;
        string comandoLidoDoFile;

        while (getline(ficheiro, comandoLidoDoFile)) {
            istringstream iss(comandoLidoDoFile);
            processaComandoDoFicheiro(iss, mundo);
        }
        ficheiro.close();
    } else {
        //não foi possível abrir o ficheiro
        cout << "Erro ao abrir " << nomeFicheiro << endl;
    }
}

int Interface::processaComando(Mundo &mundo, Imperio &imperio) {

    string comando;
    getline(cin, comando);
    stringstream ss(comando);
    ss >> comando;

    if (comando == "cria") {
        string tipo;
        int n;
        ss >> tipo;
        ss >> n;

        if (tipo == "Territorio Inicial") {
            cout << "Nao e permitido criar territorios do tipo 'territorio inicial' !!! " << endl;
        } else {
            mundo.criaTerritorio(tipo, n);
        }
    } else if (comando == "carrega") {
        string nomeFicheiro;
        ss >> nomeFicheiro;
        Interface::processaFicheiro(nomeFicheiro, mundo);
    } else if (comando == "avanca") {
        menu = 1;
        stage = 1;
    } else if (comando == "lista") {
        if (ss.good()) {
            string nomeTerritorio;
            ss >> nomeTerritorio;
            cout << mundo.lista(nomeTerritorio);
        } else {
            cout << mundo.lista();
        }
    } else if (comando == "listaimperio") {
        cout << imperio.listai();
    }
    else if (comando == "listatecnologias") {
        cout << imperio.listaTecnologiasObtidas().str() << endl;
        imperio.listaTecnologiaDisponiveis();
    }
    else if (comando == "sair") {
        return 1;
    }
   
    else {
        cout << "Comando invalido!" << endl;
    }
    return 0;
}

void Interface::processaComandoDoFicheiro(istringstream &iss, Mundo &mundo) {

    string comando;
    getline(iss, comando);
    stringstream ss(comando);
    ss >> comando;
    if (comando == "cria") {
        string tipo;
        int n;
        ss >> tipo;
        ss >> n;

        mundo.criaTerritorio(tipo, n);
    } else if (comando == "carrega") {
        string nomeFicheiro;
        ss >> nomeFicheiro;
        Interface::processaFicheiro(nomeFicheiro, mundo);
    } else if (comando == "lista") {
        if (ss.good()) {
            string nomeTerritorio;
            ss >> nomeTerritorio;
            cout << mundo.lista(nomeTerritorio);
        } else {
            cout << mundo.lista();
        }
    } else if (comando == "avanca") {
        menu = 1;
        stage = 1;
    } else {
        cout << "Comando " << comando << " invalido em ficheiro!" << endl;
    }
}

// Comandos de stage 1 -> Execução do jogo (in-game)

void Interface::passaTurno() {

    /*
    ANO 1
    T 1
    T 2
    T 3 
    T 4
    T 5
    T 6

    ANO 2 aka T7Ano1
    
    T 1
    T 2
    T 3
    T 4
    T 5
    T 6

    */

    cout.flush();
    cout << "*******************" << endl
         << "--FIM DO TURNO " << turno << " DO ANO " << ano << "--"<< endl
         << "*******************" << endl;
    fase = 1;
    stage = 1;
    menu = 1;
    
    Interface::turno++;
    if (Interface::turno == 7 && Interface::ano == 1) {
        Interface::turno = 1;
        Interface::ano = 2;
    }
    else 
        if (Interface::ano == 2 && Interface::turno == 7) {
            Interface::turno = 13;
        }
    

    if (Interface::turno != 13) {
        cout << "*******************" << endl
            << "--INICIO DO TURNO " << turno << " DO ANO " << ano << "--" << endl
            << "*******************" << endl;
    }
}

int Interface::processaComandoJogo(Mundo &mundo, Imperio &imperio) {
    switch (fase) {
        case 1: { // fase de conquista
            
            string comando;
            do {
                apresentaListaComandos(menu);
                getline(cin, comando);
                stringstream ss(comando);
                ss >> comando;

                if (comando == "conquista") {
                    if (ss.good()) {
                        string nomeTerritorio;
                        ss >> nomeTerritorio;
                        if (imperio.ConquistaTerritorio(mundo, nomeTerritorio) == 1) {
                            fase = 2;
                            break;
                        }
                    }
                    else {
                        cout << "Argumentos em falta no conquista! Sintaxe: conquista <nomeTerritorio>" << endl;
                    }
                }
                else if (comando == "toma") {
                    string tipo;
                    ss >> tipo;

                    if (tipo == "terr") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTerr(mundo, nome);
                    }
                    else if (tipo == "tec") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTec(nome);
                    }
                }
                else if (comando == "modifica") {
                    string recurso;
                    ss >> recurso;
                    if (recurso == "ouro") {
                        int valor;
                        ss >> valor;
                        imperio.modificaOuro(valor);
                    }
                    else if (recurso == "prod") {
                        int valor;
                        ss >> valor;
                        imperio.modificaProdutos(valor);
                    }
                }
                else if (comando == "fevento") {
                    string nomeEvento;
                    ss >> nomeEvento;
                    if (nomeEvento == "recurso") {
                        evento = 1;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "invasao") {
                        evento = 2;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "alianca") {
                        evento = 3;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "nada") {
                        evento = 4;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else {
                        cout << "Evento invalido !!" << endl;
                    }
                }
                else if (comando == "lista") {
                    if (ss.good()) {
                        string nomeTerritorio;
                        ss >> nomeTerritorio;
                        cout << mundo.lista(nomeTerritorio) << endl;
                    }
                    else {
                        cout << mundo.lista() << endl;
                    }
                }
                else if (comando == "listaimperio") {
                    cout << imperio.listai() << endl;
                }
                else if (comando == "listatecnologias") {
                    cout << imperio.listaTecnologiasObtidas().str() << endl;
                    imperio.listaTecnologiaDisponiveis();
                }
                else if (comando == "sair") {
                    return 1;
                }
                else if (comando == "passa") {
                    fase = 6;
                    cout << "Pulou a conquista!" << endl;
                    break;
                }
                else if (comando == "grava") {
                    if (ss.good()) {
                        bool isGood = true;
                        string name;
                        ss >> name;
                        for (auto& element : saves)
                        {
                            if (element->getNomeSave() == name) {
                                cout << "Nome do save repetido" << endl;
                                isGood = false;
                            }

                        }
                        if (isGood){
                            Save* newSave = new Save();

                            newSave->saveMundo(imperio,mundo,this->ano,this->turno,this->stage,this->menu,this->fase);
                            newSave->setNomeSave(name);
                            saves.push_back(newSave);
                        }
                    }
                    else
                        cout << "Nao foi dado nenhum nome para o save" << endl;}
                else if (comando == "ativa") {
                    if (ss.good()) {
                        bool isGood = false;
                        string name;
                        ss >> name;
                        for (auto& e : saves) {
                            if (e->getNomeSave() == name) {
                                isGood = true;
                                cout << "i found the save" << endl;
                                e->load(imperio, mundo,*this);
                                cout << "Save carregado com sucesso!" << endl;
                                break;
                            }
                        }
                        if (!isGood) {
                            cout << "Nao foi encontrado nenhum save com esse nome!" << endl;
                        }else{
                            break;
                        }
                    
                    }else
                        cout << "Indique o nome do save" << endl;
                }
                else if(comando == "apaga"){
                        if(ss.good()){
                            bool found = false;
                            string name;
                            ss >> name;
                            for(int i = 0; i < saves.size();i++){
                                if (saves[i]->getNomeSave() == name){
                                    found = true;
                                    saves[i]->removeSave();
                                    saves.erase(saves.begin()+i);
                                }
                            }
                            if (found == false){
                                cout << "Save nao encontrado" << endl;
                            }

                        }else{
                            cout << "Indique o nome da save a apagar" << endl;
                        }
                    }
                else if (comando != "avanca")
                    cout << "Comando invalido!" << endl;
                else {
                    fase = 2;
                    menu = 2;
                    stage = 1;
                }
            } while (comando != "avanca");
            break;
        }
        case 2: {
            //Fase de recolha de produtos e ouro
            if (imperio.getOuroImperio() < imperio.getMaxCofre() || imperio.getProdutosImperio() < imperio.getMaxArmazem()) {
                imperio.processaOuroProdutos();
            }
            fase = 3;
        }
        case 3: {
            //Fase de recolha de produtos e ouro
            cout << "*******************" << endl;
            cout << "Ouro total: " << imperio.getOuroImperio() << endl;
            cout << "Produtos total: " << imperio.getProdutosImperio() << endl;
            cout << "*******************" << endl;
            menu = 5;
            string comando;
            if (imperio.getBolsa() == 0) {
                do {
                    apresentaListaComandos(menu);
                    getline(cin, comando);
                    stringstream ss(comando);
                    ss >> comando;
                if (comando == "fevento") {
                    string nomeEvento;
                    ss >> nomeEvento;
                    if (nomeEvento == "recurso") {
                        evento = 1;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                    break;
                    }
                    else if (nomeEvento == "invasao") {
                        evento = 2;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                    break;
                    }
                    else if (nomeEvento == "alianca") {
                        evento = 3;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "nada") {
                        evento = 4;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else {
                        cout << "Evento invalido !!" << endl;
                     }
                   }
                    else if (comando == "lista") {
                        if (ss.good()) {
                            string nomeTerritorio;
                            ss >> nomeTerritorio;
                            cout << mundo.lista(nomeTerritorio) << endl;
                        }
                        else {
                            cout << mundo.lista() << endl;
                        }
                    }
                    else if (comando == "toma") {
                        string tipo;
                        ss >> tipo;

                        if (tipo == "terr") {
                            string nome;
                            ss >> nome;
                            imperio.tomaTerr(mundo, nome);
                        }
                        else if (tipo == "tec") {
                            string nome;
                            ss >> nome;
                            imperio.tomaTec(nome);
                        }
                    }
                    else if (comando == "modifica") {
                        string recurso;
                        ss >> recurso;
                        if (recurso == "ouro") {
                            int valor;
                            ss >> valor;
                            imperio.modificaOuro(valor);
                        }
                        else if (recurso == "prod") {
                            int valor;
                            ss >> valor;
                            imperio.modificaProdutos(valor);
                        }
                    }
                    else if (comando == "listaimperio") {
                        cout << imperio.listai() << endl;
                    }
                    else if (comando == "listatecnologias") {
                        cout << imperio.listaTecnologiasObtidas().str() << endl;
                        imperio.listaTecnologiaDisponiveis();
                    }
                    else if (comando == "sair") {
                        return 1;
                    } else if (comando == "grava") {
                        if (ss.good()) {
                            bool isGood = true;
                            string name;
                            ss >> name;
                            for (auto& element : saves)
                            {
                                if (element->getNomeSave() == name) {
                                    cout << "Nome do save repetido" << endl;
                                    isGood = false;
                                }

                            }
                            if (isGood) {
                                Save* newSave = new Save();

                                newSave->saveMundo(imperio, mundo, ano, turno, stage, menu, fase);
                                newSave->setNomeSave(name);
                                saves.push_back(newSave);
                            }
                        }
                        else
                            cout << "Nao foi dado nenhum nome para o save" << endl;

                    }
                    else if (comando == "ativa") {
                        if (ss.good()) {
                            bool isGood = false;
                            string name;
                            ss >> name;
                            for (auto& e : saves) {
                                if (e->getNomeSave() == name) {
                                    isGood = true;
                                    cout << "i found the save" << endl;
                                    e->load(imperio, mundo, *this);
                                    cout << "Save carregado com sucesso!" << endl;
                                    break;
                                }else{
                                    break;
                                }
                            }
                            if (!isGood) {
                                cout << "Nao foi encontrado nenhum save com esse nome!" << endl;
                            }

                        }
                        else
                            cout << "Indique o nome do save" << endl;
                    }
                    else if (comando == "apaga") {
                        if (ss.good()) {
                            bool found = false;
                            string name;
                            ss >> name;
                            for (int i = 0; i < saves.size(); i++) {
                                if (saves[i]->getNomeSave() == name) {
                                    found = true;
                                    saves[i]->removeSave();
                                    saves.erase(saves.begin() + i);
                                }
                            }
                            if (found == false) {
                                cout << "Save nao encontrado" << endl;
                            }

                        }
                        else {
                            cout << "Indique o nome da save a apagar" << endl;
                        }
                    }
                    else if (comando != "avanca") {
                        cout << "Comando invalido ! " << endl;
                    }
                    else {
                    fase = 4;
                    menu = 4;
                    }
                   
                } while (comando != "avanca");
            }
            else if (imperio.getBolsa() == 1) {
                menu = 2;
                do {
                    apresentaListaComandos(menu);
                    getline(cin, comando);
                    stringstream ss(comando);
                    ss >> comando;
                if (comando == "maisproduto") {
                    if (imperio.getProdutosImperio() >= 2) {
                        imperio.ouropproduto();
                        cout << "*******************" << endl;
                        cout << "2 de Ouro foram trocados por 1 Produto !!" << endl;
                        cout << " Ouro total: " << imperio.getOuroImperio() << endl;
                        cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
                        cout << "*******************" << endl;
                        fase = 3;
                    }
                    else {
                        cout << "*******************" << endl;
                        cout << "Ouro insuficiente para trocar !!" << endl;
                        cout << "*******************" << endl;
                    }
                }
                else if (comando == "maisouro") {
                    if (imperio.getProdutosImperio() >= 2) {
                        imperio.produtopouro();
                        cout << "*******************" << endl;
                        cout << "2 de Produto trocados por 1 Ouro !!" << endl;
                        cout << " Ouro total: " << imperio.getOuroImperio() << endl;
                        cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
                        cout << "*******************" << endl;
                        fase = 3;
                    }
                    else {
                        cout << "*******************" << endl;
                        cout << "Produtos insuficientes para trocar !!" << endl;
                        cout << "*******************" << endl;
                    }
                }
                else if (comando == "toma") {
                    string tipo;
                    ss >> tipo;

                    if (tipo == "terr") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTerr(mundo, nome);
                    }
                    else if (tipo == "tec") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTec(nome);
                    }
                }
                else if (comando == "modifica") {
                    string recurso;
                    ss >> recurso;
                    if (recurso == "ouro") {
                        int valor;
                        ss >> valor;
                        imperio.modificaOuro(valor);
                    }
                    else if (recurso == "prod") {
                        int valor;
                        ss >> valor;
                        imperio.modificaProdutos(valor);
                    }
                }else if (comando == "fevento") {
                    string nomeEvento;
                    ss >> nomeEvento;
                    if (nomeEvento == "recurso") {
                        evento = 1;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "invasao") {
                        evento = 2;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "alianca") {
                        evento = 3;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "nada") {
                        evento = 4;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else {
                        cout << "Evento invalido !!" << endl;
                    }
                }
                else if (comando == "lista") {
                    if (ss.good()) {
                        string nomeTerritorio;
                        ss >> nomeTerritorio;
                        cout << mundo.lista(nomeTerritorio) << endl;
                    }
                    else {
                        cout << mundo.lista() << endl;
                    }
                }
                else if (comando == "listaimperio") {
                    cout << imperio.listai() << endl;
                }
                else if (comando == "listatecnologias") {
                    cout << imperio.listaTecnologiasObtidas().str() << endl;
                    imperio.listaTecnologiaDisponiveis();
                }else if (comando == "grava") {
                    if (ss.good()) {
                        bool isGood = true;
                        string name;
                        ss >> name;
                        for (auto& element : saves)
                        {
                            if (element->getNomeSave() == name) {
                                cout << "Nome do save repetido" << endl;
                                isGood = false;
                            }

                        }
                        if (isGood){
                            Save* newSave = new Save();

                            newSave->saveMundo(imperio,mundo,ano,turno,stage,menu,fase);
                            newSave->setNomeSave(name);
                            saves.push_back(newSave);
                        }
                    }
                    else
                        cout << "Nao foi dado nenhum nome para o save" << endl;}
                else if (comando == "ativa") {
                    if (ss.good()) {
                        bool isGood = false;
                        string name;
                        ss >> name;
                        for (auto& e : saves) {
                            if (e->getNomeSave() == name) {
                                isGood = true;
                                cout << "i found the save" << endl;
                                e->load(imperio, mundo,*this);
                                cout << "Save carregado com sucesso!" << endl;
                                break;
                            }
                        }
                        if (!isGood) {
                            cout << "Nao foi encontrado nenhum save com esse nome!" << endl;
                        }else
                            break;
                    
                    }else
                        cout << "Indique o nome do save" << endl;
                }
                else if(comando == "apaga"){
                        if(ss.good()){
                            bool found = false;
                            string name;
                            ss >> name;
                            for(int i = 0; i < saves.size();i++){
                                if (saves[i]->getNomeSave() == name){
                                    found = true;
                                    saves[i]->removeSave();
                                    saves.erase(saves.begin()+i);
                                }
                            }
                            if (found == false){
                                cout << "Save nao encontrado" << endl;
                            }

                        }else{
                            cout << "Indique o nome da save a apagar" << endl;
                        }
                    }
                else if (comando != "avanca"){
                    cout << "Comando invalido ! " << endl;
                }
                else {
                    menu = 3;
                fase = 4;
                   }
                
              } while (comando != "avanca");
            } 

            break;
        }
        case 4:{ // militar e tecnologias
            int iteracao = 0;
            int tropaturno = 0;
            int tecturno = 0;

            string comando;
            cout << "*******************" << endl;
            cout << " Ouro total: " << imperio.getOuroImperio() << endl;
            cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
            cout << "*******************" << endl;

            do {
                apresentaListaComandos(menu);
                getline(cin, comando);
                stringstream ss(comando);
                ss >> comando;
                if (comando == "maismilitar") {
                    if (tropaturno < 1) {
                        if(imperio.compraUnidadeMilitar()==1){
                            iteracao++;
                            tropaturno++;
                        }
                        cout << "*******************" << endl;
                        cout << " Ouro total: " << imperio.getOuroImperio() << endl;
                        cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
                        cout << "*******************" << endl;
                    }
                    else {
                        cout << "Ja comprou 1 unidade militar este turno !!" << endl;
                    }
                }
                else if (comando == "adquire") {
                    if (tecturno < 1) {
                    if (ss.good()) {
                            string nomeTech;
                            ss >> nomeTech;
                            if(imperio.adquireTech(nomeTech)==1){
                                iteracao++;
                                tecturno = 1;
                            }
                            cout << "*******************" << endl;
                            cout << " Ouro total: " << imperio.getOuroImperio() << endl;
                            cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
                            cout << "*******************" << endl;    
                        }
         
                    }   else {
                            cout << "Ja comprou 1 tecnologia este turno !!" << endl;
                        }
                }
                else if (comando == "toma") {
                    string tipo;
                    ss >> tipo;

                    if (tipo == "terr") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTerr(mundo, nome);
                    }
                    else if (tipo == "tec") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTec(nome);
                    }
                }
                else if (comando == "modifica") {
                    string recurso;
                    ss >> recurso;
                    if (recurso == "ouro") {
                        int valor;
                        ss >> valor;
                        imperio.modificaOuro(valor);
                    }
                    else if (recurso == "prod") {
                        int valor;
                        ss >> valor;
                        imperio.modificaProdutos(valor);
                    }
                }
                else if (comando == "fevento") {
                    string nomeEvento;
                    ss >> nomeEvento;
                    if (nomeEvento == "recurso") {
                        evento = 1;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "invasao") {
                        evento = 2;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "alianca") {
                        evento = 3;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "nada") {
                        evento = 4;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else {
                        cout << "Evento invalido !!" << endl;
                    }
                }if (comando == "lista") {

                    if (ss.good()) {
                        string nomeTerritorio;
                        ss >> nomeTerritorio;
                        cout << mundo.lista(nomeTerritorio) << endl;
                    }
                    else {
                        cout << mundo.lista() << endl;
                    }
                }
                else if (comando == "listaimperio") {
                    cout << imperio.listai() << endl;
                }
                else if (comando == "listatecnologias") {
                    cout << imperio.listaTecnologiasObtidas().str() << endl;
                    imperio.listaTecnologiaDisponiveis();
                }
                else if (comando == "grava") {
                    if (ss.good()) {
                        bool isGood = true;
                        string name;
                        ss >> name;
                        for (auto& element : saves)
                        {
                            if (element->getNomeSave() == name) {
                                cout << "Nome do save repetido" << endl;
                                isGood = false;
                            }

                        }
                        if (isGood){
                            Save* newSave = new Save();

                            newSave->saveMundo(imperio,mundo,ano,turno,stage,menu,fase);
                            newSave->setNomeSave(name);
                            saves.push_back(newSave);
                        }
                    }
                    else
                        cout << "Nao foi dado nenhum nome para o save" << endl;

                }
                else if (comando == "ativa") {
                    if (ss.good()) {
                        bool isGood = false;
                        string name;
                        ss >> name;
                        for (auto& e : saves) {
                            if (e->getNomeSave() == name) {
                                isGood = true;
                                cout << "i found the save" << endl;
                                e->load(imperio, mundo,*this);
                                cout << "Save carregado com sucesso!" << endl;
                                break;
                            }
                        }
                        if (!isGood) {
                            cout << "Nao foi encontrado nenhum save com esse nome!" << endl;
                        }else
                            break;

                    }else
                        cout << "Indique o nome do save" << endl;
                }
                else if(comando == "apaga"){
                    if(ss.good()){
                        bool found = false;
                        string name;
                        ss >> name;
                        for(int i = 0; i < saves.size();i++){
                            if (saves[i]->getNomeSave() == name){
                                found = true;
                                saves[i]->removeSave();
                                saves.erase(saves.begin()+i);
                            }
                        }
                        if (found == false){
                            cout << "Save nao encontrado" << endl;
                        }

                    }else{
                        cout << "Indique o nome da save a apagar" << endl;
                    }
                }
                else {
                    fase = 5;
                }
            } while (comando != "avanca" && iteracao < 2);
            
            break;
        }
        case 5: { // eventos
            cout << "*******************" << endl;
            cout << "     Eventos " << endl;
            cout << "*******************" << endl;
            srand(time(0));
            int evento = rand() % 4 + 1;
            if (evento == 1){
                cout << "-------Recurso Abandonado-------" << endl;
                imperio.apanharRecurso(ano);
                cout << " Ouro total: " << imperio.getOuroImperio() << endl;
                cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
                cout << "*******************" << endl;
                fase = 6;
            }
            else if (evento == 2) {
                cout << "-------Invasao-------" << endl;
                imperio.invasao(mundo, ano);
                //verificar se tá GG
                fase = 6;
            }
            else if (evento == 3) {
                cout << "-------Alianca diplomatica-------" << endl;
                imperio.alianca();
                fase = 6;
            }
            else {
                cout << "-------Sem Evento-------" << endl;
                fase = 6;
            }
            break;
        }
        case 6:{ //aka pular turno
            menu = 4;
            apresentaListaComandos(menu);
            string comando;
            getline(cin, comando);
            stringstream ss(comando);
            ss >> comando;
            do {
             
                if (comando == "toma") {
                    string tipo;
                    ss >> tipo;

                    if (tipo == "terr") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTerr(mundo, nome);
                    }
                    else if (tipo == "tec") {
                        string nome;
                        ss >> nome;
                        imperio.tomaTec(nome);
                    }
                }
                else if (comando == "modifica") {
                    string recurso;
                    ss >> recurso;
                    if (recurso == "ouro") {
                        int valor;
                        ss >> valor;
                        imperio.modificaOuro(valor);
                    }
                    else if (recurso == "prod") {
                        int valor;
                        ss >> valor;
                        imperio.modificaProdutos(valor);
                    }
                }
                else if (comando == "fevento") {
                    string nomeEvento;
                    ss >> nomeEvento;
                    if (nomeEvento == "recurso") {
                        evento = 1;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "invasao") {
                        evento = 2;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "alianca") {
                        evento = 3;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else if (nomeEvento == "nada") {
                        evento = 4;
                        ultimafase = fase;
                        forcaEventos(evento, mundo, imperio);
                        fase = ultimafase;
                        break;
                    }
                    else {
                        cout << "Evento invalido !!" << endl;
                    }
                }
                else {
                    passaTurno();
                }
            } while (comando != "avanca");
            break;
        }
        case 7: {
            menu = 5;
            apresentaListaComandos(menu);
            string comando;
            getline(cin, comando);
            stringstream ss(comando);
            ss >> comando;
            if (comando == "avanca") {
                fase = 2;
            }
            break;
        }
        default:
            break;
    }
    return 0;
}

//Comandos de stage 2 -> Verificar se o jogo terminou

void Interface::checkIfEndgame(Mundo& mundo, Imperio& imperio) {
    if (turno > MAXTURNOS) {
        cout << "--FIM DO JOGO--" << endl
            << "********************" << endl << imperio.listai() << endl
            << "Pontos de vitoria finais: " << std::to_string(imperio.contaPontos()) << endl << "GG WP" << endl;

        
        stage = 2;
    }
}

void Interface::forcaEventos(int evento, Mundo& mundo, Imperio& imperio) {
    cout << "*******************" << endl;
    cout << "     Eventos " << endl;
    cout << "*******************" << endl;
    if (evento == 1) {
        cout << "-------Recurso Abandonado-------" << endl;
        imperio.apanharRecurso(ano);
        cout << " Ouro total: " << imperio.getOuroImperio() << endl;
        cout << " Produtos total: " << imperio.getProdutosImperio() << endl;
        cout << "*******************" << endl;
    }
    else if (evento == 2) {
        cout << "-------Invasao-------" << endl;
        imperio.invasao(mundo, ano);
        fase = ultimafase;
    }
    else if (evento == 3) {
        cout << "-------Alianca diplomatica-------" << endl;
        imperio.alianca();
        fase = ultimafase;
    }
    else if(evento == 4){
        cout << "-------Sem Evento-------" << endl;
        fase = ultimafase;
    }
}