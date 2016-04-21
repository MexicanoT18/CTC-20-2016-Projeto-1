#include <iostream>
#include <cstdio>
#include <vector>
#include "Element.h"
#include "Group.h"
#include "HasseDiagram.h"

using namespace std;

int main()
{
    Table table;
    if(!table.readFile("table 6.txt")) return 1;
    vector<char> & elements = table.getElements();
    Group G(elements, &table);
    if (!G.isValidGroup()){
            printf("Grupo não válido.\n");
            return 0;
    }
    list<Group> subGroups = G.generateSubgroups();
    list<Group>::iterator it;
    vector<Element> el;
    /*printf("number os subgroups: %d\n", subGroups.size());
    for(it = subGroups.begin(); it!=subGroups.end(); it++){
        el = it->getElements();
        for(int i=0; i<(int)el.size(); i++){
            printf(" %c", el[i].carac);
        }
        printf("\n");
    }*/
    HasseDiagram hasse(subGroups);
    hasse.buildDiagram();
    hasse.writeFile("hasse.dot");
    /*char a, b;
    while(scanf(" %c %c", &a, &b), (table.isInTable(a) && table.isInTable(a))){
        printf("%c\n", table.lookUp(a,b));
    }*/
    return 0;
}
