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
        Group(const vector<Element> &arr);                  //Constrói o grupo a partir de um vetor de elementos.
        Group(const vector<char> &arr, Table * t);          //Constrói o grupo a partir de um vetor de caracteres e a tabela.
        virtual ~Group();                                   //Destrutor da classe.
        bool isValidGroup();                                //Verifica se o é um grupo válido.
        Element neutralElement();                           //Retorna o elemento neutro.
        list<Group> generateSubgroups();                    //Gera os subgrupos.
        vector<Element> & getElements() { return elements; }//Retorna o vetor de elementos.
        bool operator <(const Group& other) const {         //Operador de comparação baseado no número de elementos.
            return elements.size() < other.elements.size();
        }
        bool belongsTo(Group & other);                      //Verifica se o grupo pertence a outro.
        bool isValidIndex(int n);                           //Verifica se um índice é válido no vetor de elementos.
        int findIndexOf(char c);                            //Acha o índice de um elemento.
        string toString();                                  //Escreve os elementos do grupo como uma string.
    protected:
    private:
        bool clearStack(stack<int> & stck);                 //Esvazia uma pilha.
        void backTrack(list<Group> & ans, int n);           //Testa todas as possibilidades de subgrupo.
        bool verifyAssociativity();                         //Verifica a propriedade de associatividade.
        bool isNeutralElement(int n);                       //Verifica se o elemento de indíce n é o elemento neutro.
        bool isNeutralElement(Element element);             //Verifica se o elemento é o elemento neutro.
        bool inverse();                                     //Verifica se o grupo satisfaz a propriedade de elemento inverso.
        bool isClosed();                                    //Verifica se o grupo satisfaz a propriedade de fechamento.
        int findNeutralElementIndex();                      //Retorna indíce do elemento neutro.
        int inverseElementOf(int n);                        //Retorna o indíce do inverso de um dado elemento de
                                                            //indíce n; ou -1 caso inexistente.
        int neutralElementIndex;                            //Índice do elemento neutro,
        int *isPresent;                                     //Vetor auxiliar para testar todas as possibilidades de subgrupo.
        stack<int> * toRemoveVec;                           //Pilha auxiliar na iteração por todos os subgrupos.
        stack<int> * dfsVec;                                //Pilha auxiliar na iteração por todos os subgrupos.
        vector<Element> newElements;                        //Vetor auxiliar para gerar um subgrupo.
        vector<Element> elements;                           //Vetor com os elementos.
        Table * table;                                      //Ponteiro para a tabela.
};

#endif // GROUP_H
