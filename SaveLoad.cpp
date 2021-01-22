#include "SaveLoad.h"

using namespace std;

string Save::getNomeSave()
{
	return this->nomeSave;
};

void Save::saveMundo(Imperio& oldImperio, Mundo& mundo,int ano,int turno,int stage,int menu,int fase)
{
    this->ano = ano;
    this->turno = turno;
    this->stage = stage;
    this->menu = menu;
    this->fase = fase;

	for (auto& e : mundo.territorios)
	{
	    Territorio* newTerritorio = e->clone();
		
		this->backupMundo.territorios.push_back(newTerritorio);
		if (e->getConquistado() == 1){
			this->imperioSave.setUltimeConquistado(newTerritorio->getNome());
			this->imperioSave.territoriosConquistados.push_back(newTerritorio);
	}
		}
			
	

	this->imperioSave.setProdutosImperio(oldImperio.getProdutosImperio());
	this->imperioSave.setOuroImperio(oldImperio.getOuroImperio());
	this->imperioSave.setTamCofre(oldImperio.getMaxCofre());
	this->imperioSave.setTamArmazem(oldImperio.getMaxArmazem());

	if (oldImperio.getBolsa())
		this->imperioSave.pesquisarBolsa();
	if (oldImperio.getDrones())
		this->imperioSave.pesquisarDrones();
	if (oldImperio.getDefesa())
		this->imperioSave.pesquisarDefesa();
	if (oldImperio.getMisseis())
		this->imperioSave.pesquisarMisseis();
	if (oldImperio.getBanco())
		this->imperioSave.pesquisarBanco();
	
	cout << "Gravado com sucesso!" << endl;
		
};

void Save::setNomeSave(string saveName)
{
	this->nomeSave = saveName;
}

void Save::load(Imperio& IGimperio, Mundo& IGmundo,Interface& interface) {

    interface.ano= this->ano;
    interface.turno = this->turno;
    interface.fase = this->fase;
    interface.menu = this->menu;
    interface.stage = this->stage;

	for (int i = 0;i < IGmundo.territorios.size();i++)
		delete IGmundo.territorios[i];
	IGmundo.territorios.clear();
	IGimperio.territoriosConquistados.clear();

	for (Territorio* e : backupMundo.territorios) {
	    Territorio* newT = e->clone();
		IGmundo.territorios.push_back(newT);
		if (newT->getConquistado() == 1)
			IGimperio.territoriosConquistados.push_back(newT);
		
	}
	IGimperio.clearImperioSearch();
	IGimperio.setProdutosImperio(this->imperioSave.getProdutosImperio());
	IGimperio.setOuroImperio(this->imperioSave.getOuroImperio());
	IGimperio.setTamCofre(this->imperioSave.getMaxCofre());
	IGimperio.setTamArmazem(this->imperioSave.getMaxArmazem());

	if (this->imperioSave.getBolsa())
		IGimperio.pesquisarBolsa();
	if (this->imperioSave.getDrones())
		IGimperio.pesquisarDrones();
	if (this->imperioSave.getDefesa())
		IGimperio.pesquisarDefesa();
	if (this->imperioSave.getMisseis())
		IGimperio.pesquisarMisseis();
	if (this->imperioSave.getBanco())
		IGimperio.pesquisarBanco();
	IGimperio.setUltimeConquistado(this->imperioSave.getUltimoConquistado());

}

vector<Territorio *> Save::getBackupMundo() {
    return this->backupMundo.territorios;
}

void Save::removeSave() {
    for (auto& e : this->backupMundo.territorios)
        delete e;
    this->backupMundo.territorios.clear();
    this->imperioSave.territoriosConquistados.clear();
}
