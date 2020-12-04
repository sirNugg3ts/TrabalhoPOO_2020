#include "Territorio.h"

Territorio::Territorio(const string& tipo){

	if(tipo == "Territorio Inicial"){
		nome = "TerritorioInicial";
    	this->tipo = "Territorio Inicial";
    	resistencia= 9;
    	produtosPorTurno= 1;
    	ouroPorTurno = 1;
    	pontos = 0;
	}else if (tipo == "TerritorioGenerico")
	{
		nome = "TerritorioGenerico" + std::to_string(nTerritorioGenerico);
		this->tipo = "Territorio Generico";
		resistencia = 1;
		produtosPorTurno = 1;
		ouroPorTurno = 1;
		pontos = 1;

		nTerritorioGenerico++;
		cout << "Territorio '" << nome << "' criado" << endl;
	}
	
}

Territorio::~Territorio()
{
}

string Territorio::getNome() {
    return this->nome;
}