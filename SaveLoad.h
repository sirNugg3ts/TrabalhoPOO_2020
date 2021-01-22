#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Imperio.h"
#include "Territorio.h"
#include "Continente.h"
#include "Ilhas.h"
#include "Interface.h"


class Save {
private:
	string nomeSave;
	Imperio imperioSave;
	Mundo backupMundo;

	int ano=0;
	int turno=0;
	int stage=0, menu=0,fase=0;
	
public:
    vector<Territorio*> getBackupMundo();
	string getNomeSave();
	void saveMundo(Imperio& oldImperio,Mundo& mundo,int ano,int turno,int stage,int menu,int fase);
	void setNomeSave(string);
	void load(Imperio& IGimperio, Mundo& IGmundo, Interface& interface);
	void removeSave();
};
#endif