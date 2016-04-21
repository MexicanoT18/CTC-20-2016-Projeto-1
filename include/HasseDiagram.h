#ifndef HASSEDIAGRAM_H
#define HASSEDIAGRAM_H

#include <list>
#include <vector>
#include "Group.h"
using namespace std;

class HasseDiagram
{
    public:
        HasseDiagram(list<Group> & g);
        virtual ~HasseDiagram();
        bool buildDiagram();
        bool writeFile(char * name);
    protected:
    private:
        vector<Group> groups;
        vector<int> levels;
        vector<int> grades;
        vector< vector<int> > edges;
};

#endif // HASSEDIAGRAM_H
