#include "Imperio.h"
#include "Ilhas.h"
#include "Interface.h"

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

int Imperio::contaPontos(){
	int soma = 0;
	for(auto& e : territoriosConquistados){
		soma += e->getPontos();
	}
	return soma;
}


Imperio::Imperio(Mundo &mundo) {
	ConquistaTerritorio(mundo, "TerritorioInicial");
	this->armazemProdutos = 0;
	this->cofreOuro = 0;
	this->tamArmazem = this->tamCofre = 3;
	this->pesquisabolsa = 0;
	this->pesquisadrones = 0;
	this->pesquisamisseis = 0;
	this->pesquisadefesa = 0;
	this->pesquisabanco = 0;
	this->ultimoConquistado;
	forcaMilitar = 0;
	maxForcaMilitar = 3;
}

void Imperio::clearImperioSearch(){
	this->pesquisabolsa = 0;
	this->pesquisadrones = 0;
	this->pesquisamisseis = 0;
	this->pesquisadefesa = 0;
	this->pesquisabanco = 0;
}

Imperio::Imperio() {
	this->armazemProdutos = 0;
	this->cofreOuro = 0;
	this->tamArmazem = this->tamCofre = 3;
	this->pesquisabolsa = 0;
	this->pesquisadrones = 0;
	this->pesquisamisseis = 0;
	this->pesquisadefesa = 0;
	this->pesquisabanco = 0;
	this->ultimoConquistado;
	forcaMilitar = 0;
	maxForcaMilitar = 3;
}

int Imperio::getMaxCofre() const {
	return tamCofre;
}

int Imperio::getOuroImperio() const {
	return this->cofreOuro;
}

int Imperio::getProdutosImperio() const {
	return this->armazemProdutos;
}

void Imperio::setProdutosImperio(int i) {
	this->armazemProdutos = i;
}

void Imperio::setOuroImperio(int i) {
	this->cofreOuro = i;
}

void Imperio::setTamCofre(int i)
{
	this->tamCofre = i;
}

void Imperio::setTamArmazem(int i)
{
	this->tamArmazem = i;
}

void Imperio::setForcaMilitar(int i)
{
	this->forcaMilitar = i;
}

void Imperio::setMaxForcaMilitar(int i)
{
	this->maxForcaMilitar = i;
}

void Imperio::setUltimeConquistado(string i)
{
	this->ultimoConquistado = i;
}

string Imperio::getUltimoConquistado()
{
	return this->ultimoConquistado;
}



vector<Territorio*> Imperio::getVectorTerritorios()
{
	return this->territoriosConquistados;
}

int Imperio::ConquistaTerritorio(Mundo &mundo, const string &nomeTerritorio) {
	//returns: -1 - o territorio nao existe
	//          0 - tentou conquistar um territorio que ja existe
	//          1 - tentativa efetuada com sucesso, siga para a proxima fase



	Territorio *territorioConquistar = mundo.devolvePonteiroTerritorio(nomeTerritorio);

	if (territorioConquistar == nullptr)
		return -1;
	if (territorioConquistar->getNome() == "TerritorioInicial") {
		this->territoriosConquistados.push_back(territorioConquistar);
		return 1;
	}
	srand(time(0));

	int sorte = rand() % 6 + 1;
	int forcatotal = sorte + forcaMilitar;
	
	if (territorioConquistar->getConquistado()) {
		cout << "Este territorio ja se encontra conquistado!" << endl;
		ultimoConquistado = "TerritorioInicial";
		return 0;
	}else if(territorioConquistar->getNome().find("Refugio") != std::string::npos && this->pesquisamisseis == 0){
		cout << "Necessita da tecnologia Misseis para conquistar este territorio!" << endl;
		return 0;
	}else if(territorioConquistar->getNome().find("Pescaria") != std::string::npos && this->pesquisamisseis == 0){
		cout << "Necessita da tecnologia Misseis para conquistar este territorio!" << endl;
		return 0;
	}
	else {
		if (forcatotal >= (territorioConquistar->getResistencia())) {
			cout << "Resistencia do Territorio: " << territorioConquistar->getResistencia() << endl;
			cout << "Forca total: Sorte->" << sorte << " + Forca Militar: " << forcaMilitar << " = " << forcatotal << endl;
			this->territoriosConquistados.push_back(territorioConquistar);
			territorioConquistar->setConquistado(true);
			ultimoConquistado = territorioConquistar->getNome();
			cout << "Territorio conquistado com sucesso!" << endl;
		}
		else {
			cout << "Resistencia do Territorio: " << territorioConquistar->getResistencia() << endl;
			cout << "Forca total: Sorte->" << sorte << " + Forca Militar: " << forcaMilitar << " = " << forcatotal << endl;
			cout << "Forca insuficiente para conquistar" << endl;
			return 1;
		}
	}

	return 1;
}

void Imperio::processaOuroProdutos() {
	int ouroObtido = 0;
	int produtosObtidos = 0;
	for (Territorio *p : territoriosConquistados) {
		for (int i = 0; i < p->getOuro(); ++i) {
			if (cofreOuro < tamCofre) {
				cofreOuro++;
				ouroObtido++;
			} else {
				cout << "Cofre de ouro cheio!" << endl;
				break;
			}
		}
		for (int i = 0; i < p->getProdutos(); ++i) {
			if (armazemProdutos < tamArmazem) {
				armazemProdutos++;
				produtosObtidos++;
			} else {
				cout << "Armazem de produtos cheio!" << endl;
				break;
			}
		}
	}
	cout << "Ouro obtido dos territorios: " << ouroObtido << endl << "Produtos obtidos dos territorios: "
		 << produtosObtidos << endl;
}

void Imperio::ouropproduto() {
		cofreOuro = cofreOuro - 2;
		armazemProdutos++;
}

void Imperio::produtopouro() {
		armazemProdutos = armazemProdutos - 2;
		cofreOuro++;
}

int Imperio::compraUnidadeMilitar() {
	if (cofreOuro > 0 && armazemProdutos > 0 && forcaMilitar < maxForcaMilitar) {
		cofreOuro--;
		armazemProdutos--;
		forcaMilitar++;
		cout << "Forca militar obtida !!" << endl;
		return 1;
	} else {
		if (cofreOuro < 1) {
			cerr << "Ouro insuficiente" << endl;
		} else if (armazemProdutos < 1) {
			cerr << "Produto insuficiente" << endl;
		} else if (forcaMilitar == maxForcaMilitar) {
			cerr << "Forca militar maxima alcancada!" << endl;
		}
		return 0;
	}
}

void Imperio::pesquisarBolsa() {
	this->pesquisabolsa = 1;
}

int Imperio::getBolsa() {
	return this->pesquisabolsa; // 0 quando n�o est� pesquisado 1 se for pesquisado
}

void Imperio::pesquisarDrones() {
	this->pesquisadrones = 1;
}

int Imperio::getDrones() {
	return this->pesquisadrones;
}

void Imperio::pesquisarMisseis() {
	this->pesquisamisseis = 1;
}

int Imperio::getMisseis() {
	return this->pesquisamisseis;
}

void Imperio::pesquisarDefesa() {
	this->pesquisadefesa = 1;
}

int Imperio::getDefesa() {
	return this->pesquisadefesa;
}

void Imperio::pesquisarBanco() {
	this->pesquisabanco = 1;
}

int Imperio::getBanco() {
	return this->pesquisabanco;
}



int Imperio::adquireTech(string nomeTech) {

	//return 1 if success
	//return 0 if failure

	if(nomeTech == "misseis"){
		if(pesquisamisseis > 0){
			cout << "A pesquisa Misseis ja se encontra obtida !!" << endl;
			return 0;
		}else if(pesquisamisseis == 0 && cofreOuro >=4){
			cofreOuro = cofreOuro - 4;
			pesquisarMisseis();
			cout << "-> Adquiriu a pesquisa Misseis !! Agora consegue atacar Ilhas !!" << endl;
			return 1;
		}else if(pesquisamisseis == 0 && cofreOuro <=4){
			cout << "Ouro insuficiente para a pesquisa Misseis !!" << endl;
			return 0;
		}
	}
	else if (nomeTech == "drones") {
		if (pesquisadrones > 0) {
			cout << "A pesquisa Drones ja se encontra obtida !!" << endl;
			return 0;
		}
		else if (pesquisadrones == 0 && cofreOuro >=3) {
			maxForcaMilitar = 5;
			cofreOuro = cofreOuro - 3;
			pesquisarDrones();
			cout << "-> Adquiriu a pesquisa Drones!! Forca militar m�xima aumentada para de 3 para 5 !!" << endl;
			return 1;
		}
		else if(pesquisadrones == 0 && cofreOuro<=3){
			cout << "Ouro insuficiente para a pesquisa Drones !!" << endl;
			return 0;
		}
	}
	else if (nomeTech == "defesas") {
		if (pesquisadefesa > 0) {
			cout << "A pesquisa Defesa Territorial j� se encontra obtida !!" << endl;
			return 0;
		}
		else if (pesquisadefesa==0 && cofreOuro >= 4) {
			cofreOuro = cofreOuro - 4;
			pesquisarDefesa();
			cout << "-> Adquiriu a pesquisa Defesa Territorial!! Na proxima invasao o territorio invadido tera +" << pesquisadefesa << " de resistencia !!" << endl;
			return 1;
		}
		else {
			cout << "Ouro insuficiente para a pesquisa Defesas Territoriais !!" << endl;
			return 0;
		}
	}
	else if (nomeTech == "bolsa") {
		if (pesquisabolsa > 0) {
			cout << "A pesquisa Bolsa de valores j� se encontra obtida !!" << endl;
			return 0;
		}
		else if (pesquisabolsa == 0 && cofreOuro >= 2) {
			cofreOuro = cofreOuro - 2;
			pesquisarBolsa();
			cout << "-> Adquiriu a pesquisa Bolsa!! Agora sao possiveis trocas !!" << endl;
			return 1;
		}
		else {
			cout << "Ouro insuficiente para a pesquisa Bolsa !!" << endl;
			return 0;
		}
	}
	else if (nomeTech == "banco") {
		if (pesquisabanco > 0) {
			cout << "A pesquisa Banco Central j� se encontra obtida !!" << endl;
			return 0;
		}
		else if (pesquisabanco == 0 && cofreOuro >= 3) {
			cofreOuro = cofreOuro - 3;
			tamCofre = 5;
			tamArmazem = 5;
			pesquisarBanco();
			cout << "-> Adquiriu a pesquisa Banco!! Agora o seu cofre e armazem foram aumentador para 5" << endl;
			return 1;
		}
		else {
			cout << "Ouro insuficiente para a pesquisa Banco !!" << endl;
			return 0;
		}
	}

	return 0;
}

ostringstream Imperio::listaTecnologiasObtidas() {
	ostringstream buff;
	buff << "***********" << endl;
	buff << "Tecnologias Obtidas:" << endl;
	
	if (pesquisadrones == 1)
		buff << "- Drones Militares" << endl;
	if (pesquisamisseis == 1)
		buff << "- Misseis Teleguiados" << endl;
	if (pesquisadefesa == 1)
		buff << "- Defesas Territoriais" << endl;
	if (pesquisabolsa == 1)
		buff << "- Bolsa de Valores" << endl;
	if (pesquisabanco == 1)
		buff << "- Banco" << endl;

	buff << "***********" << endl;

	return buff;
}

void Imperio::listaTecnologiaDisponiveis() {

	cout << "***********" << endl;
	cout << "Tecnologias disponiveis:" << endl;

	if (pesquisadrones != 1)
		cout << "- Drones Militares" << endl;
	if (pesquisamisseis != 1)
		cout << "- Misseis Teleguiados" << endl;
	if (pesquisadefesa != 1)
		cout << "- Defesas Territoriais" << endl;
	if (pesquisabolsa != 1)
		cout << "- Bolsa de Valores" << endl;
	if (pesquisabanco != 1)
		cout << "- Banco" << endl;

	cout << "***********" << endl;
}


void Imperio::apanharRecurso(int ano) {
	if (ano == 1) {
		cout << "-> O recurso abandonado encontrado e um produto !!" << endl;
		if (armazemProdutos<tamArmazem) {
			armazemProdutos++;
			cout << "-> O produto foi apanhado com sucesso !!" << endl;
		}
		else {
			cout << "-> O armazem de Produtos encontra-se no maximo logo o recurso nao foi apanhado !!" << endl;
		}
	}
	else {
		cout << "-> O recurso abandonado encontrado e um ouro !!" << endl;
		if (cofreOuro>tamCofre) {
			cofreOuro++;
			cout << "-> O ouro foi apanhado com sucesso !!" << endl;

		}
		else {
			cout << "-> O armazem de Ouro encontra-se no maximo logo o recurso nao foi apanhado !!" << endl;

		}
	}
}

int Imperio::invasao(Mundo& mundo, int ano) {

	Territorio* territorioAtacado = this->territoriosConquistados.back();
	/*if (territorioAtacado == nullptr) {
		string nomeTerritorio = "TerritorioInicial";
		territorioAtacado = mundo.devolvePonteiroTerritorio(nomeTerritorio);
	}*/
	int forcaoponente = 0;

	int resistenciadefensora;


	if (ano == 1) {
		forcaoponente = 2;
	}
	else if (ano == 2) {
		forcaoponente = 3;
	}
	srand(time(0));
	int sorte = rand() % 6 + 1;
	if (getDefesa() == 1) {
		resistenciadefensora = territorioAtacado->getResistencia() + 1;
	}
	else {
		resistenciadefensora = territorioAtacado->getResistencia();
	}

	int forcatotal = sorte + forcaoponente;

	if (forcatotal >= resistenciadefensora) {
			cout << "Resistencia do Territorio atacado: " << resistenciadefensora << endl;
			cout << "Forca total do inimigo: Sorte->" << sorte << " + Forca Militar: " << forcaoponente << " = " << forcatotal << endl;
			territorioAtacado->setConquistado(false);
			cout << "-> Territorio " << territorioAtacado->getNome() << " foi perdido !!" << endl;
			removeTerritorio(territorioAtacado);
	}else {
		cout << "Resistencia do Territorio atacado: " << territorioAtacado->getResistencia() << endl;
		cout << "Forca total do inimigo: Sorte->" << sorte << " + Forca Militar: " << forcaoponente << " = " << forcatotal << endl;
		cout << "Forca insuficiente para conquistar" << endl;
	}

	if (territorioAtacado->getNome() == "TerritorioInicial"){
		if(territorioAtacado->getConquistado()==false){
			Interface::turno = 13;
			
		}
	}

	return 1;
}

bool Imperio::removeTerritorio(Territorio* apaga)
{
	vector<Territorio*>::iterator it;
	it = territoriosConquistados.begin();
	while (it != territoriosConquistados.end()) {
		if ((*it)->getNome() == apaga->getNome()) {
			territoriosConquistados.erase(it);
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

void Imperio::alianca() {
	cout << "Foi realizada uma alianca com um imperio antigamente desconhecido !! A forca militar for aumentada +1 !!" << endl;
	if (forcaMilitar < maxForcaMilitar) {
		forcaMilitar++;
	}
	else {
		cout << "A forca militar ja se encontrava no maximo !!" << endl;
	}
}

string Imperio::listai() {
	int contador = 1;
	ostringstream buff;
	buff << endl << endl << "Imperio:" << endl;
	for (Territorio *p : this->territoriosConquistados) {

		buff << contador++ << " Nome: " << p->getNome() <<
			 " | Resistencia: " << p->getResistencia() <<
			 " | Produtos por turno: " << p->getProdutos() <<
			 " | Ouro por turno: " << p->getOuro() <<
			 " | Pontos de vitoria: " << p->getPontos() << endl;
	}

	buff << listaTecnologiasObtidas().str();
	buff << " Ouro total: " << this->getOuroImperio() << endl;
	buff << " Produtos total: " << this->getProdutosImperio() << endl;
	return buff.str();
}

Imperio& Imperio::operator=(const Imperio& other)
{

	if (this != &other) {
		for (auto e : territoriosConquistados)
			delete e;
		territoriosConquistados.clear();

		for (auto e : other.territoriosConquistados)
			territoriosConquistados.push_back(e);

		 armazemProdutos = other.armazemProdutos;
		 cofreOuro = other.cofreOuro;
		 tamArmazem = other.tamArmazem;
			 tamCofre = other.tamCofre;
			 forcaMilitar = other.forcaMilitar;
		maxForcaMilitar = other.maxForcaMilitar;
		 pesquisabolsa = other.pesquisabolsa;
		 pesquisadrones = other.pesquisadrones;
		 pesquisadefesa = other.pesquisadefesa;
		 pesquisamisseis = other.pesquisamisseis;
		 pesquisabanco = other.pesquisabanco;
		 ultimoConquistado = other.ultimoConquistado;

	}
	return *this;
}

int Imperio::getMaxArmazem() const {
	return tamArmazem;
}

void Imperio::modificaOuro(int valor) {
	cofreOuro = valor;
	cout << "-> O Ouro foi alterado para " << valor << " !!" << endl;
}

void Imperio::modificaProdutos(int valor) {
	armazemProdutos = valor;
	cout << "-> Os Produtos foram alterados para " << valor << " !!" << endl;
}

void Imperio::tomaTerr(Mundo& mundo, string nome) {
	
		Territorio* territorioConquistar = mundo.devolvePonteiroTerritorio(nome);
	if(territorioConquistar != nullptr){
		if (territorioConquistar->getConquistado()) {
			cout << "Este territorio ja se encontra conquistado!" << endl;
		}
		else {
			this->territoriosConquistados.push_back(territorioConquistar);
			ultimoConquistado = territorioConquistar->getNome();
			territorioConquistar->setConquistado(true);
			cout << "Tomou o territorio " << territorioConquistar->getNome() << " !!" << endl;
		}
	}
	else {
		cout << "O territorio que tentou tomar nao existe !!" << endl;
	}
}

void Imperio::tomaTec(string nome) {
	if (nome == "misseis") {
		if (pesquisamisseis > 0) {
			cout << "A pesquisa Misseis já se encontra obtida !!" << endl;
		}
		else {
			pesquisarMisseis();
			cout << "A tecnologia Misseis foi pesquisada !!" << endl;
		}
	}
	else if (nome == "drones") {
		if (pesquisadrones > 0) {
			cout << "A pesquisa Drones já se encontra obtida !!" << endl;
		}
		else {
			pesquisarDrones();
			cout << "A tecnologia Drones foi pesquisada !!" << endl;
		}
	}
	else if (nome == "defesas") {
		if (pesquisadefesa > 0) {
			cout << "A pesquisa Defesa Territorial já se encontra obtida !!" << endl;
		}
		else {
			pesquisarDefesa();
			cout << "A tecnologia Defesas foi pesquisada !!" << endl;
		}
	}
	else if (nome == "bolsa") {
		if (pesquisabolsa > 0) {
			cout << "A pesquisa Bolsa ja se encontra obtida !!" << endl;
		}
		else {
			pesquisarBolsa();
			cout << "A tecnologia Bolsa foi pesquisada !!" << endl;
		}

	}
	else if (nome == "banco") {
		if (pesquisabanco > 0) {
			cout << "A pesquisa Banco já se encontra obtida !!" << endl;
		}
		else {
			pesquisarBanco();
			cout << "A tecnologia Banco foi pesquisada !!" << endl;
		}
	}
	else {
		cout << "Nenhuma pesquisa com esse nome encontrada !!" << endl;
	}
}
