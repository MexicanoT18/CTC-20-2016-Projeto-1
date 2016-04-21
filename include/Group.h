#ifndef GROUP_H
#define GROUP_H
#include <vector>
#include <list>
#include <stack>
#include <string>
#include "Element.h"
#include "Table.h"
using namespace std;

class Group
{
    public:
        Group(const vector<Element> &arr);
        Group(const vector<char> &arr, Table * t);
        virtual ~Group();
        bool isValidGroup();
        Element neutralElement();
        list<Group> generateSubgroups();
        vector<Element> & getElements() { return elements; }
        bool operator <(const Group& other) const {
            return elements.size() < other.elements.size();
        }
        bool belongsTo(Group & other);
        bool isValidIndex(int n);
        int findIndexOf(char c);
        string toString();
    protected:
    private:
        void backTrack(list<Group> & ans, int n);
        bool verifyAssociativity(); //Verifica a propriedade de associatividade
        bool isNeutralElement(int n); // Verifica se o elemento de indíce n é o elemento neutro
        bool isNeutralElement(Element element); // Verifica se o elemento é o elemento neutro
        bool inverse(); // Verifica se o grupo satisfaz a propriedade de elemento inverso
        bool isClosed(); // Verifica se o grupo satisfaz a propriedade de fechamento
        int findNeutralElementIndex(); // Retorna indíce do elemento neutro
        int inverseElementOf(int n);//Retorna o indíce do inverso de um dado elemento de
                                    //indíce n; ou -1 caso inexistente

        int neutralElementIndex;
        int *isPresent;
        vector<Element> newElements;
        vector<Element> elements;
        Table * table;
};

#endif // GROUP_H
