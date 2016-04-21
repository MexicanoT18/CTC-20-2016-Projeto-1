#include "HasseDiagram.h"
#include <algorithm>
#include <cstdio>

using namespace std;

HasseDiagram::HasseDiagram(list<Group> & g)
{
    list<Group>::iterator it;
    for(it = g.begin(); it != g.end(); it++){
        groups.push_back(*it);
    }

    sort(groups.begin(), groups.end());
}

bool HasseDiagram::buildDiagram()
{
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

HasseDiagram::~HasseDiagram()
{
    //dtor
}
