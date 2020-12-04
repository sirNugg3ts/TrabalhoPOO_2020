#include "Territorio.h"

Territorio::Territorio(string tipo){



	if(tipo == "Territorio Inicial"){
		nome = "TerritorioInicial";
    	tipo = "Territorio Inicial";
    	resistencia= 9;
    	produtosPorTurno= 1;
    	ouroPorTurno = 1;
    	pontos = 0;
	}else if (tipo == "TerritorioGenerico")
	{
		nome = "TerritorioGenerico"; //+ std::to_string(Territorio::nTerritorioGenerico);
		tipo = "Territorio Generico";
		resistencia = 1;
		produtosPorTurno = 1;
		ouroPorTurno = 1;
		pontos = 1;

		//Territorio::nTerritorioGenerico++;
	}
	
}

Territorio::~Territorio()
{
}