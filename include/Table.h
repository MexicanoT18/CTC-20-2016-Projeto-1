#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <vector>
using namespace std;

class Table
{
    public:
        Table();
        virtual ~Table();
        char lookUp(char a, char b);
        bool readFile(const char *path);
        vector<char> & getElements() { return elements; }
        bool isInTable(char c);
    protected:
    private:
        bool addElement(char key1, char key2, char t);
        map<char, map<char, char> > table;
        vector<char> elements;
};

#endif // TABLE_H
