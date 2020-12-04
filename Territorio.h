#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <iostream> //contains string stuff
#include <string>
#include <vector>

using namespace std;

class Territorio
{
    string nome;
    string tipo;
    vector<Territorio*> lT;
    int n;
    
public:
    Territorio(vector<Territorio*> lT, string tipo, string nome, int n);
    string getNome();
    int getN();
    ~Territorio();
};
#endif