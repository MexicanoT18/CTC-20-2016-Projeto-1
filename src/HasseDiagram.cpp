#include "HasseDiagram.h"
#include <algorithm>
#include <cstdio>

using namespace std;

/* Fun��o HasseDiagram
 * Construtor da classe HasseDiagram.
 * Recebe uma lista ligada com todos os grupos e adiciona todos em um vetor.
 */

HasseDiagram::HasseDiagram(list<Group> & g)
{
    list<Group>::iterator it;
    for(it = g.begin(); it != g.end(); it++){
        groups.push_back(*it);
    }
}

/* Fun��o buildDiagram
 * Constr�i o diagrama de Hasse montando o grafo.
 * Executa a ordena��o topol�gica (sort baseado no n�mero de elementos).
 * Define os n�vis do diagrama a partir das rela��es de pertence.
 * Define os graus de cada v�rtice.
 * A partir do grau, dos n�veis e das rela��es, define quais rela��es v�o
 * ser inclu�das como arestas no diagrama de Hasse.
 */

bool HasseDiagram::buildDiagram()
{
    sort(groups.begin(), groups.end());

    levels.resize(groups.size());
    levels.assign(groups.size(), 0);
    for(int i = 0; i < (int)groups.size(); i++){
        for(int j = i+1; j < (int)groups.size(); j++){
            if (groups[i].belongsTo(groups[j])){
                levels[j] = max(levels[j], 1 + levels[i]);
            }
        }
    }

    edges.resize(groups.size());
    grades.resize(groups.size());
    grades.assign(groups.size(), 0);
    int levelDif;
    for(int i = 0; i < (int)groups.size(); i++){
        levelDif = 0;
        while (grades[i]==0 && levelDif <= (int)groups.size()){
            levelDif++;
            for(int j = i+1; j < (int)groups.size(); j++){
                if (groups[i].belongsTo(groups[j]) && levels[i]+levelDif==levels[j]){
                    edges[i].push_back(j);
                    grades[i]++;
                }
            }
        }
    }

    return true;
}

/* Fun��o writeFile
 * Escreve o grafo em um arquivo no formato para ser lido pelo GraphViz.
 * A partir das arestas, esvrece o arquivo.
 */

bool HasseDiagram::writeFile(char * name)
{
    FILE * out = fopen(name, "w");
    fprintf(out, "digraph G{\n");
    vector<int> & current = edges[0];
    for(int i = 0; i < (int)edges.size(); i++){
        current = edges[i];
        for(int j = 0; j < (int)current.size(); j++){
            fprintf(out, "\t\"%s\" -> \"%s\"\n", groups[i].toString().c_str(), groups[current[j]].toString().c_str());
        }
    }
    fprintf(out, "}");
    fclose(out);
    return true;
}

/* Fun��o ~HasseDiagram
 * Destrutor da classe HasseDiagram.
 */

HasseDiagram::~HasseDiagram()
{
    //dtor
}
