#include "Territorio.h"
#include <iostream> //contains string stuff
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "mundo.h"

Territorio::Territorio(vector<Territorio*> lT, string tipo, string nome, int n){
}

Territorio::~Territorio()
{
}

string Territorio::getNome() {
	return this->tipo;
}

int Territorio::getN() {
	return this->n;
}