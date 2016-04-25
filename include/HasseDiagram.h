#ifndef HASSEDIAGRAM_H
#define HASSEDIAGRAM_H

#include <list>
#include <vector>
#include "Group.h"
using namespace std;

class HasseDiagram
{
    public:
        HasseDiagram(list<Group> & g);  //Construtor da classe.
        virtual ~HasseDiagram();        //Destrutor da classe.
        bool buildDiagram();            //Constrói o diagrama de hasse montando o grafo.
        bool writeFile(char * name);    //Escreve o grafo em um arquivo no formato para ser lido pelo GraphViz.
    protected:
    private:
        vector<Group> groups;           //Guarda os grupos do diagrama.
        vector<int> levels;             //Camadas dos grupos do diagrama.
        vector<int> grades;             //Grau de cada nó do grafo.
        vector< vector<int> > edges;    //Arestas de saída
};

#endif // HASSEDIAGRAM_H
